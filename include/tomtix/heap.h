#ifndef t_HEAP_H
#define t_HEAP_H

typedef struct t_heap_ t_heap;

t_heap *
t_heap_new(unsigned size, int (*compare)(void*, void*));
void t_heap_delete(t_heap *);

unsigned t_heap_size(t_heap const *);
void t_heap_insert(t_heap *heap, void *k);

void *t_heap_extract_max(t_heap *heap);
void *t_heap_max(t_heap const *heap);


#endif //HEAP_H
