#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "merge_sort.h"
#define MAX_TAB_SIZE 10000000

int main(int argc, char *argv[])
{
	int i;
	int *tab = malloc(sizeof(*tab) * MAX_TAB_SIZE);

	srand(time(NULL));
	for (i = 0; i < MAX_TAB_SIZE; ++i) {
		tab[i] = rand() % MAX_TAB_SIZE;
		//printf("%d\n", tab[i]);
	}

	puts("_sort_");
	
	merge_sort(MAX_TAB_SIZE, tab);
	
	
	/*for (i=0; i< MAX_TAB_SIZE; ++i) {
	  printf("%d\n", tab[i]);
	  }*/
	free(tab);
	return EXIT_SUCCESS;
	// Mon dieu ça marche !
}
