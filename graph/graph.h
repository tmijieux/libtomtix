#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>

struct graph;

enum graph_impl {
    GRAPH_LIST,
    GRAPH_MATRIX
};

enum graph_orient {
    GRAPH_ORIENTED,
    GRAPH_NOT_ORIENTED
};

struct graph* graph_create(size_t, enum graph_orient, enum graph_impl);
struct graph* graph_copy(const struct graph*);
void graph_transpose(struct graph*);
void graph_destroy(struct graph*);
void graph_add_edge(struct graph*, int src, int dst);
void graph_remove_edge(struct graph*, int src, int dst);
int graph_has_edge(const struct graph*, int src, int dst);
int graph_is_oriented(const struct graph*);
int graph_edge_count(const struct graph*, int vertex);
size_t graph_size(const struct graph*);

/* successor iterator */
struct grsit;

struct grsit *graph_make_iterator(struct graph *g, int vertex);
void grsit_begin(struct grsit *sc);
void grsit_next(struct grsit *sc);
int grsit_end(struct grsit *sc);
int grsit_value(struct grsit *sc);
void grsit_free(struct grsit *sc);

/*
  Incoming, custom vertex properties at runtime
 */

#endif //GRAPH_H
