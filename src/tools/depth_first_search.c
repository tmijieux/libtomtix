#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#include "tomtix/tree.h"
#include "tomtix/stack.h"
#include "tomtix/token.h"

#define STACK_SIZE 256

typedef enum task_element_type_ {
    RECURSION,
    TASK,
} task_element_type;


static void task1(tomtix_tree *node)
{
    tomtix_token *tok = node->data;
    if (tomtix_token_is_operator(tok))
        printf("(");
}

static void task2(tomtix_tree *node)
{
    tomtix_token *tok = node->data;
    if (tomtix_token_is_value(tok))
        printf(" %ld ", tok->l);
    else if (tomtix_token_is_operator(tok))
        printf(" %c ", tok->c);
}

static void task3(tomtix_tree *node)
{
    tomtix_token *tok = node->data;
    if (tomtix_token_is_operator(tok))
        printf(")");
}


tomtix_tree *expr2tree(int n, tomtix_token tok[]);

typedef struct task_element_ {
    int type;
    void (*task)(tomtix_tree*);
    tomtix_tree *node;
} task_element;

task_element *element_new(int type,
                             void (*task)(tomtix_tree*),
                             tomtix_tree *node)
{
    task_element *elem = g_malloc0(sizeof(*elem));
    elem->type = type;
    elem->task = task;
    elem->node = node;
    return elem;
}

void element_delete(task_element *elem)
{
    g_free(elem);
}

int main()
{
    // I didn't have a lexical analyser yet so
    // I have my expression hard written:
    tomtix_token tok[5] = {
        { .type = TX_TOKEN_OPENING_PAREN },
        { .type = TX_TOKEN_INTEGER, .l = 137 },
        { .type = TX_TOKEN_OPERATOR, .c = '+' },
        { .type = TX_TOKEN_INTEGER, .l = 215 },
        { .type = TX_TOKEN_CLOSING_PAREN }
    };
    tomtix_tree *T = expr2tree(5, tok);
    tomtix_stack *S = tomtix_stack_new();
    tomtix_stack_push(S, element_new(RECURSION, NULL, T));

    while (!tomtix_stack_is_empty(S)) {
        task_element *tmp, *elem;
        
        elem = tomtix_stack_pop(S);
        switch (elem->type) {
        case TASK:
            elem->task(elem->node);
            break;

        case RECURSION:
            if (elem->node == NULL)
                break;
            // post order task
            tmp = element_new(TASK, &task3, elem->node);
            tomtix_stack_push(S, tmp);

            tmp = element_new(RECURSION, NULL, elem->node->right);
            tomtix_stack_push(S, tmp);
            tmp = element_new(TASK, &task2, elem->node);
            tomtix_stack_push(S, tmp);
            tmp = element_new(RECURSION, NULL, elem->node->left);
            tomtix_stack_push(S, tmp);

            //  pre order task
            tmp = element_new(TASK, &task1, elem->node);
            tomtix_stack_push(S, tmp);
            break;
        }
        element_delete(elem);
    }
    putchar('\n');
    tomtix_stack_delete(S);
    tomtix_tree_delete(T);
    return EXIT_SUCCESS;
}
