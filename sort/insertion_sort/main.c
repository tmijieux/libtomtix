#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "insertion_sort.h"

#define TAB_SIZE 1000

void randomize_tab(size_t n, int tab[])
{
	for (int i = 0; i < n; i++) {
		tab[i] = rand() % TAB_SIZE;
	}
}

void print_tab(size_t n, int tab[])
{
	for (int i = 0; i < n; i++) {
		printf("%d\n", tab[i]);
	}	
}


int main(int argc, char *argv[])
{
	int tab[TAB_SIZE];

	srand(time(NULL));
	
	randomize_tab(TAB_SIZE, tab);
	iinsertion_sort(TAB_SIZE, tab);
	print_tab(TAB_SIZE, tab);
	
	return EXIT_SUCCESS;
}
