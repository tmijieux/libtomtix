#include <stdlib.h>

#include <utils/sort/insertion_sort.h>
#include <utils/type_derive.h>

void TYPE_DERIVE_FN(insertion_sort)(size_t n, TYPE_DERIVE tab[])
{
	for (int i = 0; i < n; i++) {
		int j = i;
		while (j > 0 && tab[j] < tab[j-1]) {
			register TYPE_DERIVE tmp = tab[j-1];
			tab[j-1] = tab[j];
			tab[j] = tmp;
			j --;
		}
	}
}
