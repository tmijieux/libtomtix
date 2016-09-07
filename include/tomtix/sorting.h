#ifndef t_SORTING_H
#define t_SORTING_H

void t_insertion_sort(void *buf,
                           size_t nmemb, size_t size,
                           int (*compare)(void*,void*));

void quick_sort(int n, int tab[]);

#endif // t_SORTING_H
