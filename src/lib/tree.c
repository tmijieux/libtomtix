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
#include "tomtix/tree.h"

void
t_tree_delete(t_tree *t)
{
    if (t == NULL)
        return;
    t_tree_delete(t->left);
    t_tree_delete(t->right);
    g_free(t);
}

t_tree*
t_tree_new(void *data)
{
    t_tree *t = g_malloc0(sizeof*t);
    t->data = data;
    return t;
}
