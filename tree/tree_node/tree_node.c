#include <stdlib.h>
#include <tree_node.h>

struct tree_node {
        void *data;
	struct tree_node *left_child;
	struct tree_node *right_child;
	int is_sentinel;
};

struct tree_node *tnode_create(int type, void *data)
{
	struct tree_node *node = malloc(sizeof(*node));
	switch (type) {
	case SENTINEL_NODE:
		node->is_sentinel = 1;
		break;
	case INTERNAL_NODE:
		node->is_sentinel = 0;
		break;
	case LEAF_NODE:
		node->is_sentinel = 0;
		node->left_child = tnode_create(SENTINEL_NODE, NULL);
		node->right_child = tnode_create(SENTINEL_NODE, NULL);
		break;
	}
	node->data = data;
	return node;
}

int tnode_is_sentinel(const struct tree_node *node)
{
	return node->is_sentinel;
}

struct tree_node *tnode_get_right_child(const struct tree_node *node)
{
	return node->right_child;
}

void tnode_set_right_child(struct tree_node *node,
			   struct tree_node *right_child)
{
	node->right_child = right_child;
}


struct tree_node *tnode_get_left_child(const struct tree_node *node)
{
	return node->left_child;
}

void tnode_set_left_child(struct tree_node *node,
			 struct tree_node *left_child)
{
	node->left_child = left_child;
}

void tnode_set_data(struct tree_node *node, void *data)
{
	node->data = data;
}

void *tnode_get_data(const struct tree_node *node)
{
	return node->data;
}

void tnode_free(struct tree_node *node)
{
	free(node);
}
