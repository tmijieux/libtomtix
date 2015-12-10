#include <stdio.h>
#include <stdlib.h>

#include <stack.h>
#include "tree.h"
#include "tree_node.h"
#include "token.h"

#define STACK_SIZE 256

struct tree *expr2tree(unsigned int n, struct token tok[])
{
	struct vstack *S = vstack_create(VSTACK_SIZE);

	for (int i = 0; i < n; i++) {
		struct tree_node* tmp;
		if (token_is_value(&tok[i])) {
			tmp = node_create(LEAF_NODE, &tok[i]);
			vstack_push(S, tmp);
		} else if (token_is_operator(&tok[i])) {
			tmp = node_create(INTERNAL_NODE,  &tok[i]);
			vstack_push(S, tmp);
		} else if (token_is_closing_paren(&tok[i])) {
			struct tree_node *node[3];
			node[0] = vstack_pop(S);
		        node[1] = vstack_pop(S);
			node[2] = vstack_pop(S);
			node_set_right_child(node[1], node[0]);
			node_set_left_child(node[1], node[2]);
			vstack_push(S, node[1]);
		}
	}
	
	struct tree_node *root_node = vstack_pop(S);
        vstack_destroy(S);
	return tree_create_from_node(root_node);
}
