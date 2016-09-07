#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#include "tomtix/sorting.h"

#define MIN_SORT_SIZE 7

#define ARRAY_SWAP(buf, i, j)                           \
    do {                                                \
        register int  tmp_MACRO_IMPL_ = (buf)[(i)];      \
        (buf)[(i)] = (buf)[j];                          \
        (buf)[(j)] = tmp_MACRO_IMPL_;                   \
    } while(0)

static void dutch_national_flag_sort(int tab[], int *i, int *j, int piv)
{
    int k = (*i);	
    while (k <= (*j)) {
        if (tab[k] < piv) {
            if ((*i) != k)
                ARRAY_SWAP(tab, *i, k);
            (*i) ++;
            k ++;
        } else if (tab[k] > piv) {
            ARRAY_SWAP(tab, *j, k);
            (*j) --;
        } else {
            k ++;
        }
    }
    (*i) --;
    (*j) ++;
}

static int random_int(int d, int f)
{
    double r = (double) rand();
    return (int) d + ((r / RAND_MAX) * (f - d - 1)) + 1;
}

static void separate(int tab[], int d, int f, int *s, int *r)
{
    int piv_id = random_int(d, f);
    int piv = tab[piv_id];
    *s = d;
    *r = f;
    dutch_national_flag_sort(tab, s, r, piv);
}


static void quick_sortR(int tab[], int d, int f)
{
    if (f - d > MIN_SORT_SIZE) {
        int s, r;
        separate(tab, d, f, &s, &r);
        quick_sortR(tab, d, s);
        quick_sortR(tab, r, f);
    }
}

void t_quick_sort_i(int n, int tab[])
{
    quick_sortR(tab, 0, n - 1);
}
