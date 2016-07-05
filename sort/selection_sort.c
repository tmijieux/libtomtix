/* Méthode gloutonne: */

/* on prend le plus petit, et on le met devant, */
/* et on recommence */

#include <stdlib.h>
#include "selection_sort.h"

void selection_sort(int n, int tab[])
{
    for (int i = 0; i < n; ++i) {
        int k = i;
        for (int j = i+1; j < n; j++) {
            if (tab[j] < tab[k])
                k = j;
        }
        int tmp = tab[k];
        tab[k] = tab[i];
        tab[i] = tmp;
    }
}
