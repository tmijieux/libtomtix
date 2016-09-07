#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

#include "tomtix/tree.h"
#include "tomtix/token.h"

tomtix_tree *tomtix_expr2tree(unsigned n, tomtix_token tok[n]);

static void do_task(tomtix_tree *node)
{
    tomtix_token *tok = node->data;
    if (tomtix_token_is_value(tok))
        printf(" %ld ", tok->l);
    else if (tomtix_token_is_operator(tok))
        printf(" %c ", tok->c);
}

int main()
{
    tomtix_token tok[5] = {
        { .type = TX_TOKEN_OPENING_PAREN },
        { .type = TX_TOKEN_INTEGER, .l = 137 },
        { .type = TX_TOKEN_OPERATOR, .c = '+' },
        { .type = TX_TOKEN_INTEGER, .l = 215 },
        { .type = TX_TOKEN_CLOSING_PAREN }
    };	
    tomtix_tree *T = tomtix_expr2tree(5, tok);
    GQueue *q = g_queue_new();
    
    g_queue_push_tail(q, T);
    while (!g_queue_is_empty(q)) {
        tomtix_tree *tmp = g_queue_pop_head(q);
        if (tmp != NULL) {
            do_task(tmp);
            g_queue_push_tail(q, tmp->left);
            g_queue_push_tail(q, tmp->right);
        }
    }
    puts("");
    g_queue_free(q);
    tomtix_tree_delete(T);
    return EXIT_SUCCESS;
}
