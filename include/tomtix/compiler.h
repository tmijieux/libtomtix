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

#ifndef t_COMPILER_H
#define t_COMPILER_H

#ifdef __GNUC__

#define UNUSED __attribute__((unused))
#define MUST_CHECK __attribute__((warn_unused_result))
#define likely(x) (__builtin_constant_p(x) ? (x) : __builtin_expect(!!(x), 1))
#define unlikely(x) (__builtin_constant_p(x) ? (x) : __builtin_expect(!!(x), 0))

#else

#define UNUSED
#define MUST_CHECK
#define likely(x) (x)
#define unlikely(x) (x)

#endif // __GNUC__

#define MARK_USED(x) ((void) (x))

#endif // t_COMPILER_H
