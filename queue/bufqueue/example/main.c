#include <stdio.h>
#include <stdlib.h>

#include <utils/queue.h>

#define SIZE 1024

int main(int argc, char *argv[])
{
	struct queue *queue = queue_create(SIZE);

	queue_push(queue, 7);
	queue_push(queue, 333);
	queue_push(queue, 4);
	queue_push(queue, 2);

	while (queue_size(queue) > 0) {
		printf("%ld\n", (long) queue_pop(queue));
	}
	
	queue_destroy(queue);
	return 0;
}
