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

#ifndef t_HEAP_H
#define t_HEAP_H

typedef struct t_heap_ t_heap;

t_heap *t_heap_new(unsigned size, int (*compare)(void*, void*));
void t_heap_delete(t_heap *);

unsigned t_heap_size(t_heap const *);
void t_heap_insert(t_heap *heap, void *k);

void *t_heap_extract_max(t_heap *heap);
void *t_heap_max(t_heap const *heap);


#endif //HEAP_H
