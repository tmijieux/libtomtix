#include <heap.h>
#include "heap_sort.h"


union iv {
    int i;
    void *v;
};

static int compar(void *a__, void *b__)
{
    union iv a = {.v=a__}, b = {.v=b__};
    return a.i - b.i;
}

// WARNING :: does not work as it is
void heap_sort(size_t n, int tab[])
{
    struct heap *heap = heap_create(n, tab, &compar, NULL);
    for (int i = 0; i < n; i++) {
	union iv a = {.i=tab[i]}
	heap_insert(heap, a.v);
    }
    for (int i = 0; i < n; i++) {
	union iv a = {.v= heap_extract_max(heap)};
	tab[n - (i+1)] = a.i;
    }
    heap_destroy(heap);
}
