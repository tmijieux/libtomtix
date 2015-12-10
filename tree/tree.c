#include <stdlib.h>
#include "tree.h"
#include "tree_node.h"

struct tree {
	struct tree_node *root_sentinel;
};

struct tree_node* tree_get_root_node(struct tree *t)
{
	return node_get_left_child(t->root_sentinel);
}

static void tree_destroy_rec(struct tree_node *node)
{
	if (!node_is_sentinel(node)) {
		tree_destroy_rec(node_get_left_child(node));
		tree_destroy_rec(node_get_right_child(node));
	}
	free(node);
}

void tree_destroy(struct tree *tree)
{
	tree_destroy_rec(tree_get_root_node(tree));
	free(tree->root_sentinel);
	free(tree);
}

struct tree *tree_create_from_node(struct tree_node *root_node)
{
	struct tree *tree = malloc(sizeof(*tree));
	tree->root_sentinel = node_create(SENTINEL_NODE, NULL);
	node_set_left_child(tree->root_sentinel, root_node);
	return tree;
}
