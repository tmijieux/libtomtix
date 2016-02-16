#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "treap.h"

struct insert_me {
    int a;

    int b;
};

static int compare_i(void *a, void *b)
{
    return ((struct insert_me*) a)->a - ((struct insert_me*) b)->a;
}
#define TIME_DIFF(t1, t2)                                               \
    ((t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec))

int main(void)
{
    struct timeval t1, t2, t3;
    struct list *l;
    struct treap *t = treap_create(&compare_i);
//    unsigned long time;
    
    gettimeofday(&t1, NULL);
    gettimeofday(&t1, NULL);
    struct insert_me *im = calloc(sizeof*im, 5000);
    for (int i = 0; i < 5000; ++i) {
        im[i].a = i;
        im[i].b = i-3;
        treap_insert(t, &im[i]);
    }
    
    gettimeofday(&t2, NULL);
    
    struct insert_me key = { .a = 3854, .b = 7 };
    treap_search(t, &key, &l);
    
    gettimeofday(&t3, NULL);
    
    struct insert_me *get;
    printf("list size l = %zu\n" , list_size(l));
    get = list_get(l, 1);
    printf("get.b = %d\n", get->b);
    printf("t1 = %ld, t2 = %ld\n", TIME_DIFF(t1,t2), TIME_DIFF(t2,t3));
    treap_free(t);
    return EXIT_SUCCESS;
}
