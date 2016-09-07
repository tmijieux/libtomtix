#include <stdio.h>
#include <stdlib.h>

#include "tomtix/stack.h"
#include "tomtix/tree.h"
#include "tomtix/token.h"

#define STACK_SIZE 256

t_tree *
t_expr2tree(unsigned n, t_token tok[n])
{
    t_stack *S = t_stack_new();

    for (unsigned i = 0; i < n; ++i) {
        t_tree* tmp;
        if (t_token_is_value(&tok[i])) {
            
            tmp = t_tree_new(&tok[i]);
            t_stack_push(S, tmp);
            
        } else if (t_token_is_operator(&tok[i])) {
            
            tmp = t_tree_new(&tok[i]);
            t_stack_push(S, tmp);

        } else if (t_token_is_closing_paren(&tok[i])) {
            
            t_tree *t[3];
            t[0] = t_stack_pop(S);
            t[1] = t_stack_pop(S);
            t[2] = t_stack_pop(S);
            
            t[1]->right = t[0];
            t[1]->left = t[2];
            t_stack_push(S, t[1]);
        }
    }
	
    t_tree *root_node;
    root_node = t_stack_pop(S);
    t_stack_delete(S);
    return root_node;
}
