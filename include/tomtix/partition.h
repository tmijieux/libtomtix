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

#ifndef t_PARTITION_H
#define t_PARTITION_H

typedef struct t_partition_ t_partition;

/*
 *   this abstract type implement the partition of the set of integers
 *   [ 0 .. n-1 ]
 *
 *   a subset can be designated by any of its member
 *
 *   each subset have a special member called the 'representative'
 *   representative purposes are to identify a partition,
 *   thus, two integers x and y belong to the same subset if and only if
 *   their respective subsets have the same representative.
 */

t_partition *t_partition_new(unsigned n);
void t_partition_delete(t_partition*);
int t_partition_rep(t_partition*, int x); // representative
int t_partition_equal(t_partition*, int x, int y);
void t_partition_union(t_partition*, int x, int y);

#endif // t_PARTITION_H
