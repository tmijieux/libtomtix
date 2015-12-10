#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main(int argc, char *argv[])
{
    struct list *list = list_new(0);

    list_add(list, (void*) 4);
    list_add(list, (void*) 7);
    list_insert(list, 2, (void*) 3);

    for (int i = 1; i <= list_size(list); ++i)
	printf("%ld ", (long) list_get(list, i));
    puts("");
    list_free(list);
    return EXIT_SUCCESS;
}
