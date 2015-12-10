#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include <stack.h>
#include "token.h"

#define STACK_SIZE 256

enum {
	RECURSION,
	TASK
};

void task1(struct tree_node*);
void task2(struct tree_node*);
void task3(struct tree_node*);

struct tree *expr2tree(int n, struct token tok[]);

struct element {
	int type;
	void (*task)(struct tree_node*);
	struct tree_node *node;
};

struct element *element_create(int type,
			       void (*task)(struct tree_node*),
			       struct tree_node *node)
{
	struct element *elem = malloc(sizeof(*elem));
	elem->type = type;
	elem->task = task;
	elem->node = node;
	return elem;
}

void element_destroy(struct element *elem)
{
	free(elem);
}

int main(int argc, char *argv[])
{
	// I didn't have a lexical analyser yet so
	// I have my expression hard written:
	struct token tok[5] = {
		{ .type = OPENING_PAREN },
		{ .type = INTEGER, .u.l = 137 },
		{ .type = OPERATOR, .u.c = '+' },
		{ .type = INTEGER, .u.l = 215 },
		{ .type = CLOSING_PAREN }
	};	
	struct tree *T = expr2tree(5, tok);
	
	struct vstack *S = vstack_create(VSTACK_SIZE);
	vstack_push(S, element_create(RECURSION, NULL, tree_get_root_node(T)));
	while (!vstack_is_empty(S)) {
		struct element *tmp;
		struct element *elem = vstack_pop(S);

		switch (elem->type) {
		case TASK:
			elem->task(elem->node);
			break;

		case RECURSION:
			if (node_is_sentinel(elem->node))
				break;

			// post order task
			tmp = element_create(TASK, &task3, elem->node);
			vstack_push(S, tmp);
			
			// right child
			tmp = element_create(RECURSION, NULL,
					     node_get_right_child(elem->node));
			vstack_push(S, tmp);
			
			// in order task
			tmp = element_create(TASK, &task2, elem->node);
			vstack_push(S, tmp);
			
			// left child
			tmp = element_create(RECURSION, NULL,
					     node_get_left_child(elem->node));
			vstack_push(S, tmp);
			
			//  pre order task
			tmp = element_create(TASK, &task1, elem->node);
			vstack_push(S, tmp);
			break;
		}
		element_destroy(elem);
	}
	putchar('\n');
	vstack_destroy(S);
	tree_destroy(T);
	return EXIT_SUCCESS;
}

// pre order task
void task1(struct tree_node *node)
{
	struct token *tok = node_get_data(node);
	if (token_is_operator(tok))
		printf("(");
//	printf("<");
}

// in order task
void task2(struct tree_node *node)
{
	struct token *tok = node_get_data(node);
	if (token_is_value(tok))
		printf(" %ld ", tok->u.l);
	else if (token_is_operator(tok))
		printf(" %c ", tok->u.c);
}

// post order task
void task3(struct tree_node *node)
{
	struct token *tok = node_get_data(node);
	if (token_is_operator(tok))
		printf(")");
//	printf(">");
}
