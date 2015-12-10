#include <stdlib.h>
#include <string.h>
#include <graph.h>

struct graph {
	int is_oriented;
	int vertices;
	char adjacency[];
};

struct graph *graph_create(int vertices_count, int is_oriented,
			   int implementation)
{
	struct graph *gr = malloc(sizeof(*gr) +
				  sizeof(gr->adjacency[0]) *
				  vertices_count * vertices_count);
	gr->vertices = vertices_count;
	gr->is_oriented = is_oriented;
	return gr;
}

size_t graph_size(const struct graph *G)
{
	return G->vertices;
}

int graph_is_oriented(const struct graph *G)
{
	return G->is_oriented;
}

void graph_destroy(struct graph *gr)
{
	free(gr);
}

static void graph_set_edge_value(struct graph *gr,
				 int v_src, int v_dst, char value)
{
	gr->adjacency[v_src * gr->vertices + v_dst] = value;
	if (!gr->is_oriented)
		gr->adjacency[v_dst * gr->vertices + v_src] = value;
}

void graph_add_edge(struct graph *gr , int v_src, int v_dst)
{
	graph_set_edge_value(gr, v_src, v_dst, 1);
}

void graph_remove_edge(struct graph *gr , int v_src, int v_dst)
{
	graph_set_edge_value(gr, v_src, v_dst, 0);
}

int graph_has_edge(const struct graph *gr , int v_src, int v_dst)
{
	return (gr->adjacency[v_src * gr->vertices + v_dst] != 0);
}

struct graph *graph_copy(const struct graph *G)
{
	struct graph *H = graph_create(G->vertices,
				       G->is_oriented, 0);
	memcpy(H->adjacency, G->adjacency, G->vertices);
	return H;
}
