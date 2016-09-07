#ifndef t_GRAPH_H
#define t_GRAPH_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct t_graph_ t_graph;
typedef struct t_graph_interface_ t_graph_interface;
typedef struct t_graph_iterator_ t_graph_iterator;

struct t_graph_interface_ {
    t_graph* (*copy)(t_graph const*);
    void (*transpose)(t_graph*);
    void (*delete)(t_graph*);
    void (*add_edge)(t_graph*, int, int);
    void (*remove_edge)(t_graph*, int, int);
    bool (*has_edge)(t_graph const*, int, int);
    bool (*is_oriented)(t_graph const*);
    unsigned (*get_size)(t_graph const*);

    // graph iterator
    void (*begin)(t_graph *, t_graph_iterator*, int vertex);
    void (*next)(t_graph *, t_graph_iterator*);
    bool (*end)(t_graph *, t_graph_iterator*);
    int (*value)(t_graph *, t_graph_iterator*);

    void *padding[10];
};

struct t_graph_ {
    t_graph_interface const *iface;
};
struct t_graph_iterator_ {
    int vertex;
    void *impl;
};

t_graph *t_list_graph_new(unsigned size, bool oriented);
t_graph *t_matrix_graph_new(unsigned size, bool oriented);
t_graph *t_graph_copy(t_graph const*);

void t_graph_transpose(t_graph*);
void t_graph_destroy(t_graph*);
void t_graph_add_edge(t_graph*, int src, int dst);
void t_graph_remove_edge(t_graph*, int src, int dst);
bool t_graph_has_edge(t_graph const*, int src, int dst);
bool t_graph_is_oriented(t_graph const*);
unsigned t_graph_size(t_graph const*);

// graph iterator
void t_graph_begin(t_graph *, t_graph_iterator*, int vertex);
void t_graph_next(t_graph *, t_graph_iterator*);
bool t_graph_end(t_graph *, t_graph_iterator*);
int t_graph_value(t_graph *, t_graph_iterator*);

#endif // t_GRAPH_H
