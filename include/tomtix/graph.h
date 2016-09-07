/*
  Copyright (C) 2016 Thomas Mijieux

  This file is part of libtomtix.

  libtomtix is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  libtomtix is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

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
