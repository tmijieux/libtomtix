#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "list.h"
#include "treap.h"

struct treap_node {
    struct list *list;
    void *value;
    float priority;
    struct treap_node *parent;
    struct treap_node *right_child;
    struct treap_node *left_child;
};

struct treap {
    struct treap_node *root;
    treap_compare_f compare_fun;
    size_t size;
};

static float random_priority(void)
{
    static double f = 42.;
    return (float) sin(f++); // somewhat '~random' (uniform) distribution
}

struct treap *treap_create(treap_compare_f compare_fun)
{
    struct treap *t = calloc(sizeof*t, 1);
    t->root = NULL;
    t->size = 0;
    t->compare_fun = compare_fun;
    return t;
}

#define create_treap_node(variable_, value_, parent_)   \
    do {                                                \
        variable_ = calloc(sizeof *variable_, 1);       \
        variable_->list = list_new(0);                  \
        variable_->value = value_;                      \
        variable_->priority = random_priority();        \
        variable_->parent = parent_;                    \
        list_append(variable_->list, value_);           \
    } while (0)

#define insert_treap_node(variable_, value_, parent_)           \
    do {                                                        \
        if (variable_ == NULL) {                                \
            create_treap_node(variable_, value_, parent_);      \
            return variable_;                                   \
        }                                                       \
        return treap_bst_insert(t, variable_, value_);          \
    } while (0)

// return the address of the newly created node, or
// NULL, if no new node have been created
static struct treap_node *treap_bst_insert(
    struct treap *t, struct treap_node *node, void *value)
{
    int comp;
    if ((comp = t->compare_fun(node->value, value)) > 0)
        /*macro return*/
        insert_treap_node(node->left_child, value, node);
    else if (comp < 0)
        /*macro return*/
        insert_treap_node(node->right_child, value, node);

    // else, insert here
    list_append(node->list, value);
    return NULL; // no node have been created
}

#define node_is_right_child(node_, parent_)     \
    (((parent_)->right_child == (node_)))

#define do_right_rotation(node_, parent_)               \
    do {                                                \
        struct treap_node tmp_##__COUNTER__ = *parent_; \
        *parent_ = *node_;                              \
        *node_ = tmp_##__COUNTER__;                     \
        parent_->parent = node_->parent;                \
        node_->parent = parent_;                        \
        node_->right_child = parent_->left_child;       \
        parent_->left_child = node_;                    \
    } while (0)

// maybe doesn't work
#define do_left_rotation(node_, parent_)                 \
    do {                                                 \
        struct treap_node tmp_##__COUNTER__ = *parent_;  \
        *parent_ = *node_;                               \
        *node_ = tmp_##__COUNTER__;                      \
        parent_->parent = node_->parent;                 \
        node_->parent = parent_;                         \
        node_->left_child = parent_->right_child;        \
        parent_->right_child = node_;                    \
    } while (0)

static void treap_heap_resolve_up(struct treap_node *n)
{
    while (n->parent != NULL && n->parent->priority > n->priority) {
        // do rotations until heap configuration is restored
        if (node_is_right_child(n, n->parent)) {
            do_right_rotation(n, n->parent);
            n = n->parent;
        } else {
            do_left_rotation(n, n->parent);
            n = n->parent;
        }
    }
}
size_t treap_size(const struct treap *t)
{
    return t->size;
}

int treap_insert(struct treap *t, void *value)
{
    struct treap_node *n;

    ++ t->size;
    
    if (t->root == NULL) {
        // if tree is empty just add a node at the root
        create_treap_node(t->root, value, NULL);
        return 0;
    }

    // else insert under the root node:
    n = treap_bst_insert(t, t->root, value);
    if (NULL != n) { // if a new node was created
        // make rotation to restore a stable heap configuration
        treap_heap_resolve_up(n);
    }
    return -1;
}

static struct list *treap_bst_search(
    struct treap *t, struct treap_node *node, void *value)
{
    int comp;
    if (node == NULL) // if nobody is found
        return NULL;
    if ((comp = t->compare_fun(node->value, value)) > 0)
        return treap_bst_search(t, node->left_child, value);
    else if (comp < 0)
        return treap_bst_search(t, node->right_child, value);
    return node->list;
}

int treap_search(struct treap *t, void *value, struct list **ret)
{
    struct list *l = NULL;
    l = treap_bst_search(t, t->root, value);

    if (l != NULL) {
        *ret = l;
        return 0;
    }
    // else
    *ret = NULL;
    return -1;
}

static void treap_node_free(struct treap_node *n)
{
    if (n == NULL)
        return;
    treap_node_free(n->left_child);
    treap_node_free(n->right_child);
    list_free(n->list);
    free(n);
}

void treap_free(struct treap *t)
{
    if (NULL != t) {
        treap_node_free(t->root);
        free(t);
    }
}
