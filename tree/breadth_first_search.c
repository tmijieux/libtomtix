#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "tree.h"
#include "token.h"

#define QUEUE_SIZE 256

void do_task(struct tree_node *tn);
struct tree *expr2tree(unsigned int n, struct token tok[]);

int main(int argc, char *argv[])
{
	struct token tok[5] = {
		{ .type = OPENING_PAREN },
		{ .type = INTEGER, .u.l = 137 },
		{ .type = OPERATOR, .u.c = '+' },
		{ .type = INTEGER, .u.l = 215 },
		{ .type = CLOSING_PAREN }
	};	
	struct tree *T = expr2tree(5, tok);
	struct queue *q = queue_create(QUEUE_SIZE);
	queue_push(q, tree_get_root_node(T));
	while (!queue_is_empty(q)) {
		struct tree_node *tmp = queue_pop(q);
		if (!node_is_sentinel(tmp)) {
			do_task(tmp);
			queue_push(q, node_get_left_child(tmp));
			queue_push(q, node_get_right_child(tmp));
		}
	}
	puts("");
	queue_destroy(q);
	tree_destroy(T);
	return EXIT_SUCCESS;
}

void do_task(struct tree_node *node)
{
	struct token *tok = node_get_data(node);
	if (token_is_value(tok))
		printf(" %ld ", tok->u.l);
	else if (token_is_operator(tok))
		printf(" %c ", tok->u.c);
}
