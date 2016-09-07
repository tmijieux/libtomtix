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

#ifndef t_STACK_H
#define t_STACK_H

typedef struct t_stack_ t_stack;

t_stack *t_stack_new(void);
unsigned t_stack_size(t_stack const *s);
void t_stack_push(t_stack *s, void *data);
void *t_stack_head(t_stack const *s);
void *t_stack_pop(t_stack *s);
int t_stack_is_empty(t_stack const *s);
void t_stack_delete(t_stack *s);

#endif // t_STACK_H
