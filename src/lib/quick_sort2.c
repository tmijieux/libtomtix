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

#include <stdio.h>
#include <stdlib.h>

#include "tomtix/sorting.h"

struct limits {
    int f1;
    int d2;
};

// 'dutch national flag' sort
static void separate(int tab[], int d, int f, int k, struct limits *l)
{
    int p = tab[k];
    int i = d, c1 = d, c2 = f;
    int tmp;

    while (tab[i] < p && i <= f) {
        ++i;
        ++c1;
    }

    while (i <= c2) {
        if (tab[i] < p) {
            if (i != c1) {
                tmp = tab[c1];
                tab[c1] = tab[i];
                tab[i] = tmp;
            } else {
                ++i;
            }
            ++c1;
        } else if (tab[i] > p) {
            tmp = tab[c2];
            tab[c2] = tab[i];
            tab[i] = tmp;
            --c2;
        } else {
            ++i;
        }
    }

    l->f1 = c1 - 1;
    l->d2 = c2 + 1;
}

static int random_int(int d, int f)
{
    double r;
    r = (double) rand();
    return (int) d + ((r / RAND_MAX) * (f - d - 1)) + 1;
}

static inline int pivot_index(int d, int f)
{
    return random_int(d, f);
}

static void quick_sortR(int tab[], int d, int f)
{
    int k;
    struct limits l;

    if (f - d > 0) {
        k = pivot_index(d, f);
        separate(tab, d, f, k, &l);
        quick_sortR(tab, d, l.f1);
        quick_sortR(tab, l.d2, f);
    }
}

void t_quick_sort(int n, int tab[])
{
    quick_sortR(tab, 0, n - 1);
}
