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

#ifndef t_TREE_H
#define t_TREE_H

typedef struct t_tree_ t_tree;

struct t_tree_ {
    void *data;
    t_tree *left;
    t_tree *right;
};

t_tree* t_tree_new(void *data);
void t_tree_delete(t_tree *t);

#endif // t_TREE_H
