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

#ifndef t_ULEB128_H
#define t_ULEB128_H

#include <stdint.h>

static inline uint64_t read_ULEB128(FILE *f)
{
    uint64_t value = 0;
    unsigned shift = 0;
    uint8_t p;
    do {
	fread(&p, 1, 1, f);
	value += (uint64_t)(p & 0x7f) << shift;
	shift += 7;
    } while (p >= 0x80);
    return value;
}

#endif // t_ULEB128_H
