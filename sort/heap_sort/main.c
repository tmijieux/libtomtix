#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heap_sort.h"

#define SIZE 100

union iv {
    int i;
    void *v;
};

static int cmp(void *a__, void *b__)
{
    union iv a = {.v = a__}, b = {.v = b__};
    return a.i - b.i;
}

void randomize_tab(int n, int tab[])
{
    for (int i = 0; i < n; i++)
	tab[i] = rand() % 1000;
}

void print_tab(int n, int tab[])
{
    for (int i = 0; i < n; i++) 
	printf("%d\n", tab[i]);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int *tab = malloc(sizeof(*tab) * SIZE);

    randomize_tab(SIZE, tab);
    heap_sort(SIZE, sizeof(int), tab, &cmp);
    print_tab(SIZE, tab);

    free(tab);
    return 0;
}



