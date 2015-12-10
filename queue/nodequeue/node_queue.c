#include <stdlib.h>
#include <utils/node_queue.h>
#include <utils/list_node.h>

struct queue {
    int size;
    struct node *head; // sentinel
    struct node *tail; // sentinel
};

struct queue* nqueue_create(void)
{
    struct queue *queue = malloc(sizeof(*queue));
    queue->head = node_create(NULL, NODE_SENTINEL);
    queue->tail = node_create(NULL, NODE_SENTINEL);
    node_set_previous(queue->head, NULL);
    node_set_next(queue->head, queue->tail);
    node_set_previous(queue->tail, queue->head);
    node_set_next(queue->tail, NULL);
    queue->size = 0;
    return queue;
}

size_t nqueue_size(struct queue *queue)
{
    return queue->size;
}

void nqueue_destroy(struct queue *queue)
{
    while (nqueue_size(queue) > 0)
	nqueue_pop(queue);
    node_free(queue->head);
    node_free(queue->tail);
    free(queue);
}

void *nqueue_head(struct queue *queue)
{
    return node_get_data(queue->head);
}

void nqueue_push(struct queue *queue, void *data)
{
    struct node *new = node_create(data, NODE_DATA);
    struct node *last = node_get_previous(queue->tail);
    node_set_previous(new, last);
    node_set_next(last, new);
    node_set_previous(queue->tail, new);
    node_set_next(new, queue->tail);
    queue->size ++;
}

void *nqueue_pop(struct queue *queue)
{
    struct node *first = node_get_next(queue->head);
    struct node *second = node_get_next(first);
    node_set_next(queue->head, second);
    node_set_previous(second, queue->head);
    void *data = node_get_data(first);
    node_free(first);
    queue->size --;
    return data;
}
