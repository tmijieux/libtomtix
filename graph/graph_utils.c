#include <stdlib.h>
#include <string.h>

#include <partition.h>
#include <stack.h>
#include <graph.h>

enum colour {
	WHITE, // never seen
	GREY,  // currently exploring successors
	BLACK,  // finished exploring successors
	GREEN // another state for 
};

static int graph_is_acyclic_aux(struct graph *G, int state[], int i)
{
	int s = graph_size(G);
	for (int j = 0; j < s; j++) {
		if (graph_has_edge(G, i, j)) {
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

int graph_is_acyclic(struct graph *G)
{
	int s = graph_size(G);
	
	int *state = malloc(sizeof(int) * s);
	for (int i = 0; i < s; i ++)
		state[i] = WHITE;

	for (int i = 0; i < s; i++) {
		if (state[i] == WHITE) {
			state[i] = GREY;
			if (!graph_is_acyclic_aux(G, state, i))
				return 0;
			state[i] = BLACK;
		}	
	}
	return 1;
}

struct graph *transposed_graph(struct graph *G)
{
	struct graph *H = graph_copy(G);
	graph_transpose(H);
	return H;
}

void get_black_vertex_stack(size_t n, int colour[], struct stack *bvs)
{
	for (int i = 0; i < n; i++) {
		if (colour[i] == BLACK) {
		        stack_push(bvs, i);
		}
	}
}

static void partition_stack_union(struct partition *part,
				  struct stack *st)
{
	int i = stack_pop(st);
	while (stack_size(st) > 0) {
		int j = stack_pop(st);
		partition_union(part, i, j);
	}
}

static void switch_black_green(size_t n, int colour[])
{
	for (int i = 0; i < n; i++) {
		if (colour[i] == BLACK)
			colour[i] = GREEN;
	}
}

static void set_tab_value(size_t n, void *tab_, char value)
{
	char *tab = tab_;
	for (int i = 0; i < n; i++) {
		tab[i] = value;
	}
}

static void graph_dfs_aux(struct graph *G, int i, int colour[])
{
	if (colour[i] != WHITE)
		return;
	colour[i] = GREY;
	struct vertex_successor_iterator vsi;
	for (vsi_start(&vsi, G, i); !vsi_end(&vsi); vsi_next(&vsi)) {
		int j = vsi_value(&vsi);
	        graph_dfs_aux(G, j, colour);
	}
	colour[i] = BLACK;
}

// Kosaraju (vu en cours) --> remplace date de coloration
// en noire par empilage sur une pile
struct partition *graph_compute_strongly_connected_component(struct graph *G)
{
	size_t n = graph_size(G);
	struct stack *st = stack_create(n);
	int *colour = malloc(sizeof(*colour) * n);
	set_tab_value(n, colour, WHITE);
	for (int i = 0; i < n; i++) {
		if (colour[i] == WHITE) {
			graph_dfs_aux(G, i, colour);
			stack_push(st, i);
		}
	}
	graph_transpose(G);
	struct partition *part = partition_create(n);
	struct stack *bvs = stack_create(n);
	set_tab_value(n, colour, WHITE);
	while (stack_size(st) > 0) {
		int i = stack_pop(st);
		graph_dfs_aux(G, i, colour);
	        get_black_vertex_stack(n, colour, bvs);
		partition_stack_union(part, bvs);
		switch_black_green(n, colour);
	}
	graph_transpose(G);
	stack_destroy(bvs);
	stack_destroy(st);
	return part;
}

// Although Kosaraju's algorithm is conceptually simple,
// Tarjan's and the path-based algorithm are favoured in practice
// since they require only one depth-first search rather than two.
// http://en.wikipedia.org/wiki/Strongly_connected_component
