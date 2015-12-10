#include <stdio.h>
#include <stdlib.h>

#include <stack.h>

#define SIZE 1024

int main(int argc, char *argv[])
{
	struct stack *stack = stack_create(SIZE);

	long a = 4;
	stack_push(stack, (int)a);

	while (!stack_is_empty(stack)) {
		long p = (long)stack_pop(stack);
		printf("%ld\n", p);
	}
	stack_destroy(stack);
	
	return 0;
}
