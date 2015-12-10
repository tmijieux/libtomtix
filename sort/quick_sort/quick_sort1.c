#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#include <utils/sort/quick_sort.h>

#define MIN_SORT_SIZE 7

/*
 diviser pour règner 

 diviser:  
 choisir un pivot et distribuer de chaque coté de pivot 
 en temps linéaire 

 règner: 
 recollage des tableaux.
*/
static inline void swap(int tab[], int i, int j)
{
        register int tmp = tab[i];
	tab[i] = tab[j];
	tab[j] = tmp;
}

static void dutch_national_flag_sort(int tab[], int *i, int *j, int piv)
{
	int k = (*i);	
	while (k <= (*j)) {
		if (tab[k] < piv) {
			if ((*i) != k)
				swap(tab, *i, k);
			(*i) ++;
			k ++;
		} else if (tab[k] > piv) {
			swap(tab, *j, k);
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

static inline int pivot_index(int d, int f)
{
	return random_int(d, f);
}

static void separate(int tab[], int d, int f, int *s, int *r)
{
	int piv_id = pivot_index(d, f);
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

void quick_sort(int n, int tab[])
{
	quick_sortR(tab, 0, n - 1);
}
