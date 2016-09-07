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
#include "tomtix/heap.h"

struct t_heap_ {
    int (*compare)(void*, void*);
    unsigned size;
    void **buf;
};

t_heap *
t_heap_new(unsigned size, int (*compare)(void*, void*))
{
    t_heap *h = g_malloc0(sizeof*h);
    h->compare = compare;
    h->size = 0;
    h->buf = g_malloc0(sizeof*h->buf * (size + 1));

    return h;
}

void t_heap_delete(t_heap *h)
{
    g_free(h->buf);
    g_free(h);
}

#define GREATER_CHILD(h, i)                             \
    ((2*(i) == (h)->size) ?                             \
     (2*(i)) :                                          \
     ((h->compare(h->buf[2*i], h->buf[2*i+1]) > 0) ?    \
      (2*(i)) :                                         \
      (2*(i)+1)))

#define HEAP_SWAP(h, i, k)                      \
    do {                                        \
        void *tmp_M;                            \
        tmp_M = (h)->buf[(i)];                  \
        (h)->buf[(i)] = (h)->buf[(k)];          \
        (h)->buf[(k)] = tmp_M;                  \
    } while(0)

#define EXTRACT_PROBLEM(h, i)                                   \
    ((2*(i) == (h)->size &&                                     \
      (h)->compare((h)->buf[2*(i)], (h)->buf[(i)]) > 0) ||      \
     (2*(i)+1 <= (h)->size &&                                   \
      ((h)->compare((h)->buf[2*(i)], (h)->buf[(i)]) > 0 ||      \
       (h)->compare((h)->buf[2*(i)+1], (h)->buf[(i)]) > 0)))


static inline unsigned extract_resolve(t_heap *h, unsigned i)
{
    unsigned k = GREATER_CHILD(h, i);
    HEAP_SWAP(h, i, k);
    return k;
}

void *t_heap_extract_max(t_heap *heap)
{
    void *max = heap->buf[0];
    heap->buf[0] = heap->buf[--heap->size];
    for( unsigned i = 0;
         EXTRACT_PROBLEM(heap, i);
         i = extract_resolve(heap, i))
    { }
    return max;
}

void *t_heap_max(t_heap const *heap)
{
    return heap->buf[0];
}

#define INSERT_PROBLEM(h, i) ((h)->compare((h)->buf[(i)], (h)->buf[(i)/2]) > 0)

void t_heap_insert(t_heap *h, void *k)
{
    unsigned i = h->size ++;
    h->buf[i] = k;

    while (INSERT_PROBLEM(h, i)) {
	HEAP_SWAP(h, i, i/2);
        i /= 2;
    }
}

unsigned heap_size(t_heap const *heap)
{
    return heap->size;
}
