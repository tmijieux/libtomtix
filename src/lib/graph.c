#include <dlfcn.h>
#include <assert.h>
#include <stdio.h>

#include "tomtix/graph.h"

t_graph *t_graph_copy(t_graph const *g)
{
    return g->iface->copy(g);
}

void t_graph_transpose(t_graph *g)
{
    g->iface->transpose(g);
}

void t_graph_delete(t_graph *g)
{
    g->iface->delete(g);
}

void t_graph_add_edge(t_graph *g, int v_src, int v_dst)
{
    g->iface->add_edge(g, v_src, v_dst);
}

void t_graph_remove_edge(t_graph *g, int v_src, int v_dst)
{
    g->iface->remove_edge(g, v_src, v_dst);
}

bool t_graph_has_edge(t_graph const *g, int v_src, int v_dst)
{
    return g->iface->has_edge(g, v_src, v_dst);
}

bool t_graph_is_oriented(t_graph const *g)
{
    return g->iface->is_oriented(g);
}

unsigned t_graph_size(t_graph const *g)
{
    return g->iface->get_size(g);
}

void t_graph_begin(t_graph *g, t_graph_iterator *it, int vertex)
{
    g->iface->begin(g, it, vertex);
}

void t_graph_next(t_graph *g, t_graph_iterator *it)
{
    g->iface->next(g, it);
}

bool t_graph_end(t_graph *g, t_graph_iterator *it)
{
    return g->iface->end(g, it);
}

int t_graph_value(t_graph *g, t_graph_iterator *it)
{
    return g->iface->value(g, it);
}
