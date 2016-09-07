#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "tomtix/partition.h"
#include "tomtix/stack.h"
#include "tomtix/graph.h"

typedef enum graph_colour_ {
    WHITE, // never seen
    GREY,  // currently exploring successors
    BLACK,  // finished exploring successors
    GREEN // another state for 
} graph_colour;

static int graph_is_acyclic_aux(t_graph *G, int state[], int i)
{
    unsigned s = t_graph_size(G);
    for (unsigned j = 0; j < s; j++) {
        if (t_graph_has_edge(G, i, j)) {
            if (state[j] == WHITE) {
                state[j] = GREY;
                if (!graph_is_acyclic_aux(G, state, j))
                    return 0;
            }
            if (state[j] == GREY)
                return 0;
        }
    }
    state[i] = BLACK;
    return 1;
}

int t_graph_is_acyclic(t_graph *G)
{
    unsigned s = t_graph_size(G);
	
    int *state = malloc(sizeof(int) * s);
    for (unsigned i = 0; i < s; i ++)
        state[i] = WHITE;

    for (unsigned i = 0; i < s; i++) {
        if (state[i] == WHITE) {
            state[i] = GREY;
            if (!graph_is_acyclic_aux(G, state, i))
                return 0;
            state[i] = BLACK;
        }	
    }
    return 1;
}

t_graph *transposed_graph(t_graph *G)
{
    t_graph *H = t_graph_copy(G);
    t_graph_transpose(H);
    return H;
}

void get_black_vertex_stack(size_t n, int colour[], t_stack *bvs)
{
    for (unsigned i = 0; i < n; i++) {
        if (colour[i] == BLACK) {
            t_stack_push(bvs, (void*)(intptr_t)i);
        }
    }
}

static void partition_stack_union(t_partition *part,
				  t_stack *st)
{
    int i = (intptr_t) t_stack_pop(st);
    while (t_stack_size(st) > 0) {
        int j = (intptr_t) t_stack_pop(st);
        t_partition_union(part, i, j);
    }
}

static void switch_black_green(size_t n, int colour[])
{
    for (unsigned i = 0; i < n; i++) {
        if (colour[i] == BLACK)
            colour[i] = GREEN;
    }
}

static void set_tab_value(size_t n, void *tab_, char value)
{
    char *tab = tab_;
    for (unsigned i = 0; i < n; i++) {
        tab[i] = value;
    }
}

static void graph_dfs_aux(t_graph *G, int i, int colour[])
{
    if (colour[i] != WHITE)
        return;
    colour[i] = GREY;
    t_graph_iterator it;
    for ( t_graph_begin(G, &it, i);
          !t_graph_end(G, &it);
          t_graph_next(G, &it)    )
    {
        int j = t_graph_value(G, &it);
        graph_dfs_aux(G, j, colour);
    }
    colour[i] = BLACK;
}

// Kosaraju (vu en cours) --> remplace date de coloration
// en noire par empilage sur une pile
t_partition *graph_compute_strongly_connected_component(t_graph *G)
{
    size_t n = t_graph_size(G);
    t_stack *st = t_stack_new();
    int *colour = malloc(sizeof(*colour) * n);
    set_tab_value(n, colour, WHITE);
    for (unsigned i = 0; i < n; i++) {
        if (colour[i] == WHITE) {
            graph_dfs_aux(G, i, colour);
            t_stack_push(st, (void*)(intptr_t)i);
        }
    }
    t_graph_transpose(G);
    t_partition *part = t_partition_new(n);
    t_stack *bvs = t_stack_new();
    set_tab_value(n, colour, WHITE);
    while (t_stack_size(st) > 0) {
        int i = (intptr_t)t_stack_pop(st);
        graph_dfs_aux(G, i, colour);
        get_black_vertex_stack(n, colour, bvs);
        partition_stack_union(part, bvs);
        switch_black_green(n, colour);
    }
    t_graph_transpose(G);
    t_stack_delete(bvs);
    t_stack_delete(st);
    return part;
}

// Although Kosaraju's algorithm is conceptually simple,
// Tarjan's and the path-based algorithm are favoured in practice
// since they require only one depth-first search rather than two.
// http://en.wikipedia.org/wiki/Strongly_connected_component
