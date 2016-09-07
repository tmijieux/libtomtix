#ifndef t_STACK_H
#define t_STACK_H

#include <stdlib.h>
typedef struct t_stack_ t_stack;

t_stack *t_stack_new(void);
unsigned t_stack_size(t_stack const *s);
void t_stack_push(t_stack *s, void *data);
void *t_stack_head(t_stack const *s);
void *t_stack_pop(t_stack *s);
int t_stack_is_empty(t_stack const *s);
void t_stack_delete(t_stack *s);

#endif // t_STACK_H
