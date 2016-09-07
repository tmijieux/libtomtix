#include <glib.h>
#include <stdlib.h>
#include "tomtix/tree.h"

void
t_tree_delete(t_tree *t)
{
    if (t == NULL)
        return;
    t_tree_delete(t->left);
    t_tree_delete(t->right);
    g_free(t);
}

t_tree*
t_tree_new(void *data)
{
    t_tree *t = g_malloc0(sizeof*t);
    t->data = data;
    return t;
}
