#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#include "quick_sort.h"
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

static void dutch_national_flag_sort(int tab[], int *i, int *j, int pivot)
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

void separate(int tab[], int d, int f, int *s, int *r)
{
	int piv_id = pivot_index(d, f);
	int piv = tab[piv_id];
	*s = d;
	*r = f;
	dutch_national_flag_sort(tab, s, r, piv);
}

struct arg_t {
	int *tab;
	int d;
	int f;
};

static void quick_sortR(int tab[], int d, int f);

static void *launch_threaded_quick_sortR(void *a)
{
	struct arg_t *arg = a;
	quick_sortR(arg->tab, arg->d, arg->f);
	pthread_exit(NULL);
}

static void quick_sortR(int tab[], int d, int f)
{
	if (f - d > MIN_SORT_SIZE) {
		pthread_attr_t attr;
		pthread_t threads[2];
		struct arg_t args[2];

		args[0].tab = args[1].tab = tab;
		args[0].d = d;
		args[1].f = f;
		pthread_attr_init(&attr);
		
		separate(tab, d, f, &(args[0].f), &(args[1].d));
		
		pthread_create(&threads[0], &attr,
			       launch_threaded_quick_sortR, &args[0]);
		pthread_create(&threads[1], &attr,
			       launch_threaded_quick_sortR, &args[1]);
		pthread_join(threads[0], NULL);
		pthread_join(threads[1], NULL);
	}
}

void quick_sort(int n, int tab[])
{
	quick_sortR(tab, 0, n - 1);
}
