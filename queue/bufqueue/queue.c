#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "queue.h"

struct queue {
    unsigned int head; // front
    unsigned int tail; // back
    size_t size;
    size_t buffer_size;
    void *buf[];
};

struct queue *queue_create(size_t buffer_size)
{
    struct queue *q = malloc(sizeof(*q) +
			     sizeof(q->buf[0]) * buffer_size);
    q->head = 0;
    q->tail = 0;
    q->size = 0;
    q->buffer_size = buffer_size;
    return q;
}

void queue_free(struct queue *q)
{
    free(q);
}

size_t queue_size(struct queue *q)
{
    return q->size;
}

int queue_is_full(struct queue *q)
{
    return (q->size == q->buffer_size);
}

int queue_is_empty(struct queue *q)
{
    return (q->size == 0);
}

void queue_push(struct queue *q, void *element)
{
    q->buf[q->tail] = element;
    q->tail = (q->tail+1) % q->buffer_size;
    q->size ++;
}

void queue_push_front(struct queue *q, void *element)
{
    q->buf[q->head] = element;
    q->head--;
    if (q->head < 0)
	q->head = q->buffer_size;
    q->size ++;
}

void *queue_pop(struct queue *q)
{
    void *tmp = q->buf[q->head];
    q->head = (q->head+1) % q->buffer_size;
    q->size --;
    return tmp;
}

void *queue_pop_back(struct queue *q)
{
    void *tmp = q->buf[q->tail];
    q->tail--;
    if (q->tail < 0)
	q->tail = q->buffer_size - 1;
    q->size --;
    return tmp;
}

void *queue_front(struct queue *q)
{
    return q->buf[q->head];
}

void *queue_back(struct queue *q)
{
    return q->buf[q->tail];
}
