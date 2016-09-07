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

#ifndef TREAP_H
#define TREAP_H

typedef struct t_treap_ t_treap;
typedef int (*t_compare_function)(void *, void*);

t_treap *t_treap_new(t_compare_function compare_fun);
size_t t_treap_size(t_treap const*);
int t_treap_insert(t_treap *t, void *value);
int t_treap_search(t_treap *t, void *value, GList **ret);
void t_treap_free(t_treap *t);

#endif //TREAP_H
