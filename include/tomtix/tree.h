#ifndef t_TREE_H
#define t_TREE_H

typedef struct t_tree_ t_tree;

struct t_tree_ {
    void *data;
    t_tree *left;
    t_tree *right;
};

void t_tree_delete(t_tree *t);
t_tree* t_tree_new(void *data);

#endif // t_TREE_H
