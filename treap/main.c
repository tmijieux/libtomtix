#include <stdio.h>
#include <stdlib.h>
#include "treap.h"

struct insert_me {
    int a;
};

static int compare_i(void *a, void *b)
{
    return ((struct insert_me*) a)->a - ((struct insert_me*) b)->a;
}

int main(void)
{
    struct treap *t = treap_create(&compare_i);

    struct insert_me im[10] = {
        { .a = 10 },
        { .a = 9 },
        { .a = 8 },
        { .a = 7 },
        { .a = 6 },
        { .a = 5 },
        { .a = 4 },
        { .a = 3 },
        { .a = 2 },
        { .a = 1 }
    };

    for (int i = 0; i < 10; i++)
        treap_insert(t, &im[i]);
    struct list *l;
    treap_search(t, &im[0], &l);
    printf("list size l = %zu\n", list_size(l));
    printf("&im[3] = %p | &list_elem(1) = %p\n", &im[0], list_get(l, 1));
    treap_free(t);
    return EXIT_SUCCESS;
}
