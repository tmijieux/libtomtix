#include <graph.h>
#include <dlfcn.h>
#include <assert.h>
#include <stdio.h>

// definitions --------------------------------------------------------

#define IMPL_COUNT 2
    
#define GRAPH_MATRIX_LIBNAME "libgraph_matrix.so"
#define GRAPH_LIST_LIBNAME   "libgraph_list.so"

struct impl_handler {
	void *dl_handler; // dlopen handler, see: man dlopen
	struct graph* (*graph_create)(int, int, enum graph_impl);
	struct graph* (*graph_copy)(const struct graph*);
	void (*graph_transpose)(struct graph*);
	void (*graph_destroy)(struct graph*);
	void (*graph_add_edge)(struct graph*, int, int);
	void (*graph_remove_edge)(struct graph*, int, int);
	int (*graph_has_edge)(const struct graph*, int, int);
	int (*graph_is_oriented)(const struct graph*);
	size_t (*graph_size)(const struct graph*);
};

struct graph {
	struct impl_handler *imphandle;
	struct graph *graph;
};

// end of definitions ---------------------------------------------------
// start global  --------------------------------------------------------

static struct impl_handler graph_handle[IMPL_COUNT];
static unsigned int use_count[IMPL_COUNT] =  { 0 };
static char *graph_libname[IMPL_COUNT] = {
	GRAPH_MATRIX_LIBNAME,
	GRAPH_LIST_LIBNAME
};

// end of globals -----------------------------------------------------
// --------------------------------------------------------------------

static void load_handler(const char *lib_name,
			 struct impl_handler *iph)
{
	void *ha = dlopen(lib_name, RTLD_NOW);
	char *tmp;
	if ((tmp = dlerror()) != NULL) {
		puts(tmp);
		exit(EXIT_FAILURE);
	}
	iph->dl_handler = ha;
	iph->graph_create = dlsym(ha, "graph_create");
	if ((tmp = dlerror()) != NULL) {
		puts(tmp);
		exit(EXIT_FAILURE);
	}
	assert(iph->graph_create != NULL);
	iph->graph_copy = dlsym(ha, "graph_copy");
	iph->graph_transpose = dlsym(ha, "graph_transpose");
	iph->graph_destroy = dlsym(ha, "graph_destroy");
	iph->graph_add_edge = dlsym(ha, "graph_add_edge");
	iph->graph_remove_edge = dlsym(ha, "graph_remove_edge");
	iph->graph_has_edge = dlsym(ha, "graph_has_edge");
	iph->graph_is_oriented = dlsym(ha, "graph_is_oriented");
	iph->graph_size = dlsym(ha, "graph_size");
}

//--------------------------------------------------------------
// Wrappers ----------------------------------------------------

struct graph *graph_create(int vertices_count, int is_oriented, int impl)
{
	if ((use_count[impl])++ == 0) {
		load_handler(graph_libname[impl],
			     &graph_handle[impl]);
	}
	struct graph *g = malloc(sizeof(*g));
	g->imphandle = &graph_handle[impl];
	g->graph = g->imphandle->graph_create(vertices_count, is_oriented,
					      impl);
	return g;
}

struct graph *graph_copy(const struct graph *g){
	
	struct graph *h = malloc(sizeof(*h));
	h->imphandle = g->imphandle;
	h->graph = h->imphandle->graph_copy(g->graph);
	return h;
}

void graph_transpose(struct graph *g)
{
	g->imphandle->graph_transpose(g->graph);
}

void graph_destroy(struct graph *g)
{
	g->imphandle->graph_destroy(g->graph);
	int impl = g->imphandle - graph_handle;
	assert(use_count[impl] > 0);
	if (--use_count[impl] == 0)
		dlclose(g->imphandle->dl_handler);
	free(g);
}

void graph_add_edge(struct graph *g, int v_src, int v_dst)
{
	g->imphandle->graph_add_edge(g->graph, v_src, v_dst);
}

void graph_remove_edge(struct graph *g, int v_src, int v_dst)
{
	g->imphandle->graph_remove_edge(g->graph, v_src, v_dst);
}

int graph_has_edge(const struct graph *g, int v_src, int v_dst)
{
	return g->imphandle->graph_has_edge(g->graph, v_src, v_dst);
}

int graph_is_oriented(const struct graph *g)
{
	return g->imphandle->graph_is_oriented(g->graph);
}

size_t graph_size(const struct graph *g)
{
	return g->imphandle->graph_size(g->graph);
}
