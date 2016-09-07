#include <stdlib.h>
#include <stdint.h>
#include <glib.h>

#include "tomtix/graph.h"

typedef struct list_graph_ list_graph;
static t_graph_interface list_graph_interface;

struct list_graph_ {
    t_graph parent;
    bool oriented;
    unsigned vertex_count;
    GList **edges;
};

/******************** iterator ***********************************/

static void
siterator_begin(t_graph *g, t_graph_iterator *it, int vertex)
{
    list_graph *G = (list_graph*)g;
    it->impl = G->edges[vertex];
}

static void
siterator_next(t_graph *g, t_graph_iterator *it)
{
    (void) g;
    it->impl = ((GList*)it->impl)->next;
}

static bool
siterator_end(t_graph *g, t_graph_iterator *it)
{
    (void) g;
    return it->impl == NULL;
}

static int
siterator_value(t_graph *g, t_graph_iterator *it)
{
    (void) g;
    return (int)(intptr_t) ((GList*)it->impl)->data;
}

/***************************************************************/

static int compare_int(void const *a_, void const *b_)
{
    return (int)(intptr_t) a_ - (int)(intptr_t) b_;
}

t_graph *
t_list_graph_new(unsigned vertex_count, bool oriented)
{
    list_graph *G;
    G = g_malloc0(sizeof*G);
    G->edges = g_malloc0(sizeof G->edges[0] * vertex_count);
    G->oriented = oriented;
    G->vertex_count = vertex_count;
    G->parent.iface = &list_graph_interface;
    return (t_graph*) G;
}

static unsigned
list_graph_size(t_graph const *G)
{
    return ((list_graph*)G)->vertex_count;
}

static bool
list_graph_is_oriented(t_graph const *G)
{
    return ((list_graph*)G)->oriented;
}

static void
list_graph_delete(t_graph *G_)
{
    list_graph *G = (list_graph*) G_;
    
    for (unsigned i = 0; i < G->vertex_count; ++i)
        g_list_free(G->edges[i]);
    g_free(G);
}

static bool
list_graph_has_edge(t_graph const *G_, int v_src, int v_dst)
{
    list_graph *G = (list_graph*) G_;
    return g_list_find(G->edges[v_src], (void*)(intptr_t) v_dst) != NULL;
}

static void
list_graph_add_edge(t_graph *G_ , int v_src, int v_dst)
{
    list_graph *G = (list_graph*) G_;
    
    if (!list_graph_has_edge(G_, v_src, v_dst)) {
        G->edges[v_src] = g_list_insert_sorted(
            G->edges[v_src], (void*)(intptr_t)v_dst, compare_int);
        if (!G->oriented) {
            G->edges[v_dst] = g_list_insert_sorted(
                G->edges[v_dst], (void*)(intptr_t)v_src, compare_int);
        }
    }
}

static void
list_graph_remove_edge(t_graph *G_ , int v_src, int v_dst)
{
    list_graph *G = (list_graph*) G_;
    G->edges[v_src] = g_list_remove(G->edges[v_src], (void*)(intptr_t)v_dst);
    if (!G->oriented)
        G->edges[v_dst] = g_list_remove(G->edges[v_dst], (void*)(intptr_t)v_src);
}


static void
do_copy(list_graph const *dest, list_graph const *src)
{
    for (unsigned i = 0; i < src->vertex_count; i++)
        dest->edges[i] = g_list_copy(src->edges[i]);
}



static t_graph *
list_graph_copy(t_graph const *G_)
{
    list_graph *G = (list_graph*) G_;
    t_graph *H;
    
    H = t_list_graph_new(G->vertex_count, G->oriented);
    do_copy((list_graph*) H, G);
    return H;
}

static void
list_graph_transpose(t_graph *G_)
{
    list_graph *G = (list_graph*) G_;
    
    if (!list_graph_is_oriented(G_))
        return;

    GList **edges;
    edges = g_malloc0(sizeof(*edges) * G->vertex_count);

    for (unsigned i = 0; i < G->vertex_count; ++i) {
        GList *l = G->edges[i];
        while (l != NULL) {
            intptr_t v = (intptr_t) l->data;
            edges[v] = g_list_insert_sorted(edges[v], (void*) v, compare_int);
            l = l->next;
        }
    }
    for (unsigned i = 0; i < G->vertex_count; ++i) {
        g_list_free(G->edges[i]);
        G->edges[i] = edges[i];
    }
    g_free(edges);
}


static t_graph_interface list_graph_interface = {
    
    .copy = list_graph_copy,
    .transpose = list_graph_transpose,
    .delete = list_graph_delete,
    .add_edge = list_graph_add_edge,
    .remove_edge = list_graph_remove_edge,
    .has_edge = list_graph_has_edge,
    .is_oriented = list_graph_is_oriented,
    .get_size = list_graph_size,

    .begin = siterator_begin,
    .next = siterator_next,
    .end = siterator_end,
    .value = siterator_value,
};

