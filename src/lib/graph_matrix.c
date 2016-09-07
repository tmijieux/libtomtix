#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "tomtix/graph.h"
#include "tomtix/util.h"

#define SET_VALUE(G, v_src, v_dst, value)                               \
    do {                                                                \
        (G)->adjacency[(v_src) * (G)->vertex_count + (v_dst)] = (value); \
        if (!(G)->oriented)                                             \
            (G)->adjacency[(v_dst) * (G)->vertex_count + (v_src)] = value; \
    } while (0)

#define GET_VALUE(G, v_src, v_dst)                              \
    ((G)->adjacency[(v_src) * (G)->vertex_count + (v_dst)])


typedef struct t_matrix_graph_ t_matrix_graph;
static t_graph_interface matrix_graph_interface;

struct t_matrix_graph_ {
    t_graph parent;
    bool oriented;
    unsigned vertex_count;
    bool *adjacency;
};

static void
siterator_next(t_graph *g, t_graph_iterator *it)
{
    intptr_t v = (intptr_t) it->impl;
    do {
        ++ v;
    } while (v < ((t_matrix_graph*)g)->vertex_count &&
             !GET_VALUE((t_matrix_graph*)g, it->vertex, v));
    it->impl = (void*) v;
}

static void
siterator_begin(t_graph *g, t_graph_iterator *it, int vertex)
{
    (void) g;
    it->impl = (void*) (intptr_t) -1;
    it->vertex = vertex;
    siterator_next(g, it);
}

static bool
siterator_end(t_graph *g, t_graph_iterator *it)
{
    return ((intptr_t)it->impl) >= ((t_matrix_graph*)g)->vertex_count;
}

static int
siterator_value(t_graph *g, t_graph_iterator *it)
{
    (void) g;
    return (int)(intptr_t) it->impl;
}

t_graph *
t_matrix_graph_new(unsigned vertex_count, bool oriented)
{
    t_matrix_graph *G;
    G = g_malloc0(sizeof*G);
    G->adjacency = g_malloc0(sizeof G->adjacency[0] * SQUARE(vertex_count));
    G->vertex_count = vertex_count;
    G->oriented = oriented;
    G->parent.iface = &matrix_graph_interface;
    return (t_graph*) G;
}

static unsigned
matrix_graph_size(const t_graph *G)
{
    return ((t_matrix_graph*)G)->vertex_count;
}

static bool
matrix_graph_is_oriented(t_graph const *G)
{
    return ((t_matrix_graph*)G)->oriented;
}

static void
matrix_graph_delete(t_graph *g)
{
    t_matrix_graph *G = (t_matrix_graph*) g;
    g_free(G->adjacency);
    g_free(G);
}

static void
matrix_graph_add_edge(t_graph *G , int v_src, int v_dst)
{
    SET_VALUE((t_matrix_graph*)G, v_src, v_dst, true);
}

static void
matrix_graph_remove_edge(t_graph *G , int v_src, int v_dst)
{
    SET_VALUE((t_matrix_graph*)G, v_src, v_dst, false);
}

static bool
matrix_graph_has_edge(t_graph const *G , int v_src, int v_dst)
{
    return GET_VALUE((t_matrix_graph*)G, v_src, v_dst);
}

static t_graph *
matrix_graph_copy(const t_graph *g_)
{
    t_matrix_graph *G = (t_matrix_graph*)g_;
    t_graph *H;
    H = t_matrix_graph_new(G->vertex_count, G->oriented);
    
    memcpy(((t_matrix_graph*)H)->adjacency,
           G->adjacency,
           G->vertex_count*sizeof(bool));
    return (t_graph*) H;
}

#define MATRIX_SWAP(mat, s, i, j)                       \
    do {                                                \
        char tmp_M = (mat)[(i)*(s)+(j)];                \
        (mat)[(i)*(s)+(j)] = (mat)[(j)*(s)+(i)];        \
        (mat)[(j)*(s)+(i)] = tmp_M;                     \
    } while(0)

static void
matrix_graph_transpose(t_graph *g_)
{
    t_matrix_graph *G = (t_matrix_graph*)g_;
    if (!G->oriented)
        return;
    for (unsigned i = 0; i < G->vertex_count; ++i)
        for (unsigned j = 0; j < i; ++j)
            MATRIX_SWAP(G->adjacency, G->vertex_count, i, j);
}

static t_graph_interface matrix_graph_interface = {
    .copy = matrix_graph_copy,
    .transpose = matrix_graph_transpose,
    .delete = matrix_graph_delete,
    .add_edge = matrix_graph_add_edge,
    .remove_edge = matrix_graph_remove_edge,
    .has_edge = matrix_graph_has_edge,
    .is_oriented = matrix_graph_is_oriented,
    .get_size = matrix_graph_size,

    .begin = siterator_begin,
    .next = siterator_next,
    .end = siterator_end,
    .value = siterator_value,
};
