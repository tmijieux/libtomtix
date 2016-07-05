#include <stdlib.h>
#include "insertion_sort.h"

void insertion_sort(int n, int tab[])
{
    for (int i = 0; i < n; i++) {
        int j = i;
        while (j > 0 && tab[j] < tab[j-1]) {
            register int tmp = tab[j-1];
            tab[j-1] = tab[j];
            tab[j] = tmp;
            j --;
        }
    }
}
