#ifndef HEAP_H
#define HEAP_H

struct heap;

struct heap *heap_new(unsigned int buffer_size, void *buffer,
		      int (*cmp)(void*, void*));
void heap_free(struct heap *heap);
size_t heap_size(struct heap *heap);
void *heap_extract_max(struct heap *heap);
void *heap_max(struct heap *heap);
void heap_insert(struct heap *heap, void *k);


#endif //HEAP_H
