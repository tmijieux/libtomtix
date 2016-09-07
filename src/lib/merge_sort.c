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
#include <string.h>
#include <glib.h>

#include "tomtix/util.h"
#include "tomtix/sorting.h"


static void
do_merge(int i, int j,
         void *tab, void *tmp,
         size_t nmemb, size_t size,
         int (*compare)(void*, void*))
{
    int k = (i + j)/ 2 + 1;
    int c1 = i, c2 = k;
	
    for (int l = i; l <= j; ++l) {
        if (c1 < k && (c2 >= j + 1 || compare(tab+c1*size, tab+c2*size)<=0)) {
            memcpy(tmp+l*size, tab+c1*size, size);
            ++ c1;
        } else {
            memcpy(tmp+l*size, tab+c2*size, size);
            ++ c2;
        }
    }
    memcpy(tab, tmp, nmemb*size);
}

static void merge_sortR(int i, int j,
                        void *tab, void *tmp,
                        size_t nmemb, size_t size,
                        int (*compare)(void*, void*))
{
    if (j > i) {
        int k = (i+j)/2;
        merge_sortR(i, k, tab, tmp, nmemb, size, compare);
        merge_sortR(k+1, j, tab, tmp, nmemb, size, compare);
        do_merge(i, j, tab, tmp, nmemb, size, compare);
    }
}

void t_merge_sort(void *buf,
                  size_t nmemb, size_t size,
                  int (*compare)(void*, void*))
{
    void *tmp = g_memdup(buf, nmemb*size);
    merge_sortR(0, nmemb - 1, buf, tmp, nmemb, size, compare);
    free(tmp);
}
