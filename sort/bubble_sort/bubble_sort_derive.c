#include <stdlib.h>
#include "bubble_sort.h"

#include "type_derive.h"

void TYPE_DERIVE_FN(bubble_sort)(size_t n, TYPE_DERIVE tab[])
{
	int stop = 0;
	while (!stop) {
		stop = 1;
		for (int i = 0; i < n - 1;  ++i) {
			if (tab[i] > tab[i+1]) {
				register TYPE_DERIVE tmp = tab[i];
				tab[i] = tab[i+1];
				tab[i+1] = tmp;
				stop = 0;
			}
		}
	}
}
