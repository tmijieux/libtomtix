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

// iterator

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
