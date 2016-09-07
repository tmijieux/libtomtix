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

void quick_sort(int n, int tab[])
{
    quick_sortR(tab, 0, n - 1);
}
