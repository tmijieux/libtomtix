#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "tomtix/util.h"
#include "tomtix/merge_sort.h"


static void
do_merge(int i, int j,
         void *tab, void *tmp,
         size_t nmemb, size_t size,
         int (*compare)(void*, void*))
{
    int k = (i + j)/ 2 + 1;
    int c1 = i, c2 = k;
	
    for (int l = i; l <= j; ++l) {
        if (c1 < k && (c2 >= j + 1 || compare(tab+c1*size, tab+c2*size)<=0)) {
            memcpy(tmp+l*size, tab+c1*size, size);
            ++ c1;
        } else {
            memcpy(tmp+l*size, tab+c2*size, size);
            ++ c2;
        }
    }
    memcpy(tab, tmp, nmemb*size);
}

static void merge_sortR(int i, int j,
                        void *tab, void *tmp,
                        size_t nmemb, size_t size,
                        int (*compare)(void*, void*))
{
    if (j > i) {
        int k = (i+j)/2;
        merge_sortR(i, k, tab, tmp, nmemb, size, compare);
        merge_sortR(k+1, j, tab, tmp, nmemb, size, compare);
        do_merge(i, j, tab, tmp, nmemb, size, compare);
    }
}

void
t_merge_sort(void *buf,
                  size_t nmemb, size_t size,
                  int (*compare)(void*, void*))
{
    void *tmp = g_memdup(buf, nmemb*size);
    merge_sortR(0, nmemb - 1, buf, tmp, nmemb, size, compare);
    free(tmp);
}
