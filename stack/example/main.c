#include <stdio.h>
#include <stdlib.h>

#include <utils/stack.h>

#define SIZE 1000

int main(int argc, char *argv[])
{
    struct stack *stack = stack_create(SIZE);
    int a = 4;
    stack_push(stack, a);
    while (!stack_is_empty(stack)) {
	int p = stack_pop(stack);
	printf("%d\n", p);
    }
    stack_destroy(stack);
    return EXIT_SUCCESS;
}
