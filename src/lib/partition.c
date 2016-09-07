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

#include <glib.h>
#include <stdlib.h>
#include "tomtix/partition.h"

typedef struct t_partition_ {
    unsigned size;
    int *parent;
    int *weight;
} t_partition;

t_partition *
t_partition_new(unsigned n)
{
    t_partition *p = g_malloc0(sizeof(*p));
    p->size = n;
    p->parent = g_malloc(sizeof p->parent * n);
    p->weight = g_malloc0(sizeof p->weight * n); 
    for (unsigned i = 0; i < n; i++)
        p->parent[i] = i;
    return p;
}

void t_partition_delete(t_partition *p)
{
    g_free(p->parent);
    g_free(p->weight);
    g_free(p);
}

int t_partition_rep(t_partition *p, int x)
{
    int y = x;
    while (p->parent[y] != y) {
        y = p->parent[y];
    }
    int z = x;
    do {
        z = p->parent[x];
        p->parent[x] = y;
        x = z;
        // ON ÉCRASE LES ARBRES! BORDEL!
    } while (x != y);
    return y;
}

int t_partition_equal(t_partition *p, int x, int y)
{
    return (t_partition_rep(p, x) == t_partition_rep(p, y));
}

void t_partition_union(t_partition *p, int x, int y)
{
    int a = t_partition_rep(p, x);
    int b = t_partition_rep(p, y);
    
    if (p->weight[a] > p->weight[b]) {
        p->parent[b] = a;
    } else if (p->weight[a] < p->weight[b]) {
        p->parent[a] = b;
    } else {
        p->parent[a] = b;
        p->weight[b] ++;
    }
}
