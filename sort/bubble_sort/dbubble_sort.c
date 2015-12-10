#include "bubble_sort.h"

void dbubble_sort(size_t n, double tab[])
{
	int stop = 0;
	while (!stop) {
		stop = 1;
		for (int i = 0; i < n - 1;  ++i) {
			if (tab[i] > tab[i+1]) {
				double tmp = tab[i];
				tab[i] = tab[i+1];
				tab[i+1] = tmp;
				stop = 0;
			}
		}
	}
}
