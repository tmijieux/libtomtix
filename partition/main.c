#include <stdio.h>
#include <stdlib.h>

#include "partition.h"

#define PARTITION_SIZE 10

void test_equivalence(struct partition *p, int a, int b)
{
	printf("%d ~ %d?: %s\n",
	       a, b,
	       partition_equivalence(p, a, b) ? "VRAI" : "FAUX");
}

int main(int argc, char *argv[])
{
	struct partition *p = partition_create(PARTITION_SIZE);
	
	partition_union(p, 3, 7);
	printf("3->%d, 7->%d\n",
	       partition_representative(p, 3),
	       partition_representative(p, 7));

	test_equivalence(p, 4, 7);
	test_equivalence(p, 3, 7);
	test_equivalence(p, 1, 2);
	
	partition_union(p, 4, 7);
	// check transitivité :)
	test_equivalence(p, 4, 7);
		
	partition_destroy(p);
	return EXIT_SUCCESS;
}
