#ifndef QUEUE_H
#define QUEUE_H

struct queue;

struct queue *queue_create(size_t buf_size);
void queue_free(struct queue*);

size_t queue_size(struct queue*);
int queue_is_full(struct queue*);
int queue_is_empty(struct queue*);

void queue_push(struct queue*, void*); // back
void queue_push_front(struct queue*, void*);

void* queue_pop(struct queue*);  // front
void* queue_pop_back(struct queue*);

void* queue_back(struct queue*);
void* queue_front(struct queue*);

#endif //QUEUE_H
