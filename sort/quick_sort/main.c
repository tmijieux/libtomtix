#include <stdio.h>
#include <stdlib.h>
#include "quick_sort.h"
#include "insertion_sort.h"

#define TAB_SIZE 1000


void randomize_tab(int n, int tab[])
{
	for (int i = 0; i < TAB_SIZE; i++) {
		tab[i] = rand() % TAB_SIZE;
	}
}

void print_tab(int n, int tab[])
{
	for (int i = 0 ;i < TAB_SIZE; i++) {
		printf("%d\n", tab[i]);
	}	
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	int *tab = malloc(sizeof(*tab) * TAB_SIZE);

	randomize_tab(TAB_SIZE, tab);
	puts("_sort_");
	
	quick_sort(TAB_SIZE, tab);
	insertion_sort(TAB_SIZE, tab);

	print_tab(TAB_SIZE, tab);

	free(tab);
	return EXIT_SUCCESS;
}
