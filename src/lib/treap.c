/*
  Copyright (C) 2016 Thomas Mijieux

  This file is part of libtomtix.

  libtomtix is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  libtomtix is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "tomtix/treap.h"

typedef struct treap_node_ treap_node;

typedef struct treap_node_ {
    void *value; // value for compare purpose
    float priority;
    GList *list; // value list
    treap_node *parent;
    treap_node *right_child;
    treap_node *left_child;
} treap_node;

struct t_treap_ {
    treap_node *root;
    t_compare_function compare;
    size_t size;
};

static float make_priority(void)
{
    static double f = 42.;
    return (float) sin(f++);
    // somewhat '~random' (uniform) distribution
}

t_treap *t_treap_new(t_compare_function compare)
{
    t_treap *t = calloc(sizeof*t, 1);
    t->compare = compare;
    return t;
}

#define CREATE_TREAP_NODE(var_, value_, parent_)                \
    do {                                                        \
        (var_) = g_malloc0(sizeof *(var_));                     \
        (var_)->value = value_;                                 \
        (var_)->priority = make_priority();                     \
        (var_)->parent = parent_;                               \
        (var_)->list = g_list_append((var_)->list, value_);     \
    } while (0)

#define INSERT_TREAP_NODE(var_, value_, parent_)                \
    do {                                                        \
        if ((var_) == NULL) {                                   \
            CREATE_TREAP_NODE((var_), (value_), (parent_));     \
            return var_;                                        \
        }                                                       \
        return treap_bst_insert(t, var_, value_);               \
    } while (0)

// return the address of the newly created node, or
// NULL, if no new node have been created
static treap_node *
treap_bst_insert(t_treap *t, treap_node *n, void *value)
{
    int comp;
    if ((comp = t->compare(n->value, value)) > 0)
        /*macro return*/
        INSERT_TREAP_NODE(n->left_child, value, n);
    else if (comp < 0)
        /*macro return*/
        INSERT_TREAP_NODE(n->right_child, value, n);

// else, insert here
    n->list = g_list_prepend(n->list, value);
    return NULL; // no node have been created
}

#define NODE_IS_RIGHT_CHILD(node_, parent_)     \
    (((parent_)->right_child == (node_)))

#define DO_RIGHT_ROTATION(node_, parent_)               \
    do {                                                \
        treap_node tmp_##__COUNTER__ = *parent_;        \
        *parent_ = *node_;                              \
        *node_ = tmp_##__COUNTER__;                     \
        parent_->parent = node_->parent;                \
        node_->parent = parent_;                        \
        node_->right_child = parent_->left_child;       \
        parent_->left_child = node_;                    \
    } while (0)

// maybe doesn't work
#define DO_LEFT_ROTATION(node_, parent_)                \
    do {                                                \
        treap_node tmp_##__COUNTER__ = *parent_;        \
        *parent_ = *node_;                              \
        *node_ = tmp_##__COUNTER__;                     \
        parent_->parent = node_->parent;                \
        node_->parent = parent_;                        \
        node_->left_child = parent_->right_child;       \
        parent_->right_child = node_;                   \
    } while (0)

static void
treap_heap_resolve_up(treap_node *n)
{
    while (n->parent != NULL && n->parent->priority > n->priority) {
        // do rotations until heap configuration is restored
        if (NODE_IS_RIGHT_CHILD(n, n->parent)) {
            DO_RIGHT_ROTATION(n, n->parent);
            n = n->parent;
        } else {
            DO_LEFT_ROTATION(n, n->parent);
            n = n->parent;
        }
    }
}

size_t
t_treap_size(t_treap const *t)
{
    return t->size;
}

int
t_treap_insert(t_treap *t, void *value)
{
    treap_node *n;

    ++ t->size;

    if (t->root == NULL) {
        // if tree is empty just add a node at the root
        CREATE_TREAP_NODE(t->root, value, NULL);
        return 0;
    }

    // else insert under the root node:
    n = treap_bst_insert(t, t->root, value);
    if (NULL != n) { // if a new node was created
        // make rotation to restore a stable heap configuration
        treap_heap_resolve_up(n);
        return 0;
    }
    return -1;
}

static GList *
treap_bst_search(t_treap *t, treap_node *node, void *value)
{
    int comp;
    if (node == NULL) // if nobody is found
        return NULL;
    if ((comp = t->compare(node->value, value)) > 0)
        return treap_bst_search(t, node->left_child, value);
    else if (comp < 0)
        return treap_bst_search(t, node->right_child, value);
    return node->list;
}

int
t_treap_search(t_treap *t, void *value, GList **ret)
{
    GList *l;
    l = treap_bst_search(t, t->root, value);

    if (l != NULL) {
        *ret = l;
        return 0;
    }
// else
    *ret = NULL;
    return -1;
}

static void treap_node_free(treap_node *n)
{
    if (n == NULL)
        return;
    treap_node_free(n->left_child);
    treap_node_free(n->right_child);
    g_list_free(n->list);
    free(n);
}

void
t_treap_free(t_treap *t)
{
    if (NULL != t) {
        treap_node_free(t->root);
        free(t);
    }
}
