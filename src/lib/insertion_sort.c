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

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "tomtix/sorting.h"

void t_insertion_sort(void *buf,
                      size_t nmemb, size_t size,
                      int (*compare)(void*,void*))
{
    for (unsigned i = 0; i < nmemb; ++i) {
        unsigned j = i;
        
        while (j > 0 && compare(buf+j*size,buf+(j-1)*size) < 0) {
            uint8_t tmp[size];
            memcpy(tmp, buf+(j-1)*size, size);
            memcpy(buf+(j-1)*size, buf+j*size, size);
            memcpy(buf+j*size, tmp, size);
            -- j;
        }
    }
}
