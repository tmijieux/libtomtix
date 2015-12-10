#include <stdio.h>
#include <stdlib.h>

#include "c_libs/c_queue.h"

int
main(int argc, char *argv[])
{
	struct Queue *q = queue_create();


	enqueue(q, (void*) 3);
	enqueue(q, (void*) 1);
	enqueue(q, (void*) 7);

	while (queue_size(q) > 0) {
		printf("%d\n", (long) dequeue(q));
	}

	queue_destroy(q);
	return 0;
}

