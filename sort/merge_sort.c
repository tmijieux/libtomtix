/* diviser pour règner: */

/* diviser: trivial */

/* reconstituer: */

/* fusion en temps linéaire */
/* necessite une mémoire annexe. */

#include <stdlib.h>
#include <utils/sort/merge_sort.h>

static void merge(int i, int j, int tab[], int tmp[])
{
    int k = (i + j)/ 2 + 1;
    int c1 = i, c2 = k;
	
    for (int l = i; l <= j; ++l) {
        if (c1 < k && (c2 >= j + 1 || tab[c1] <= tab[c2])) {
            tmp[l] = tab[c1];
            ++c1;
        } else {
            tmp[l] = tab[c2];
            ++c2;
        }
    }
		
    for (int l = i; l <= j; ++l) {
        tab[l] = tmp[l];
    }
}

static void merge_sortR(int i, int j, int tab[], int tmp[])
{
    if (j > i) {
        int k = (i+j)/2;
        merge_sortR(i, k, tab, tmp);
        merge_sortR(k+1, j, tab, tmp);
        merge(i, j, tab, tmp);
    }
}

void merge_sort(size_t n, int tab[])
{
    int *tmp = malloc(sizeof(int) * n);
    merge_sortR(0, n - 1, tab, tmp);
    free(tmp);
}
