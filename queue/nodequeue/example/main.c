#include <stdio.h>
#include <stdlib.h>

#include <utils/node_queue.h>


static void lnqueue_push(struct queue *q, long l)
{
    nqueue_push(q, (void*) l);
}

static int lnqueue_pop(struct queue *q)
{
    return (long) nqueue_pop(q);
}

int main(int argc, char *argv[])
{
	struct queue *queue = nqueue_create();

	lnqueue_push(queue, 7);
	lnqueue_push(queue, 333);
	lnqueue_push(queue, 4);
	lnqueue_push(queue, 2);

	while (nqueue_size(queue) > 0) {
		printf("%ld\n", (long) lnqueue_pop(queue));
	}
	
	nqueue_destroy(queue);
	return 0;
}
