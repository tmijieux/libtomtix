#define MAX_TAB_SIZE 1000
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "selection_sort.h"

int main(int argc, char *argv[])
{
	int tab[MAX_TAB_SIZE];
	srand(time(NULL));
	for (int i = 0; i < MAX_TAB_SIZE; ++i) {
		tab[i] = rand() % MAX_TAB_SIZE;
		printf("%d\n", tab[i]);
	}
	selection_sort(MAX_TAB_SIZE, tab);
	puts("");
	for (int i = 0; i < MAX_TAB_SIZE; ++i) {
		printf("%d\n", tab[i]);
	}
	return EXIT_SUCCESS;
}
