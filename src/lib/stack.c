#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <glib.h>

#include "tomtix/stack.h"

struct t_stack_ {
    GList *l;
    unsigned size;
};

unsigned
t_stack_size(t_stack const *s)
{
    return s->size;
}

t_stack *t_stack_new(void)
{
    t_stack *s = malloc(sizeof*s);
    memset(s, 0, sizeof*s);
    return s;
}

void
t_stack_push(t_stack *s, void *data)
{
    ++ s->size;
    s->l = g_list_prepend(s->l, data);
}

void *
t_stack_head(t_stack const *s)
{
    assert(s->l != NULL);
    return s->l->data;
}

void *
t_stack_pop(t_stack *s)
{
    -- s->size;
    void *data = s->l->data;
    s->l = g_list_delete_link(s->l, s->l);
    return data;
}

int
t_stack_is_empty(t_stack const *s)
{
    return s->size == 0;
}

void
t_stack_delete(t_stack *s)
{
    g_list_free(s->l);
    memset(s, 0, sizeof *s);
    free(s);
}
