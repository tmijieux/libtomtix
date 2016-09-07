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

#ifndef t_GRAPH_UTILS_H
#define t_GRAPH_UTILS_H

#include <stdbool.h>
#include "tomtix/partition.h"

bool t_graph_is_acyclic(t_graph*);
t_graph *t_transposed_graph(t_graph* );
t_partition *graph_compute_strongly_connected_component(t_graph *G);

/*
  INCOMING !
  arbre couvrant minimal

  plus court chemin:
  Bellman-Ford
  Dijkstra

  Flot maximal
*/

#endif // t_GRAPH_UTILS_H
