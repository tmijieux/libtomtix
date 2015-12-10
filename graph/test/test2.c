#include <stdio.h>
#include <stdlib.h>

#include <graph.h>

void do_test(struct graph *gr, int a, int b)
{
	graph_add_edge(gr, a, b);
	
	printf("%d-->%d?: %s\n", a, b,
	       graph_has_edge(gr, a, b)? "oui":"non");


}

void do_test2(struct graph *gr, int a, int b)
{
	graph_remove_edge(gr, a, b);
	
	printf("%d-->%d?: %s\n", a, b,
	       graph_has_edge(gr, a, b)? "oui":"non");
}

int main(int argc, char *argv[])
{
	struct graph *gr = graph_create(10, 1, GRAPH_LIST);

	do_test(gr, 7, 3);
	do_test(gr, 2, 5);
	do_test(gr, 7, 4);

	do_test2(gr, 7, 4);
	do_test2(gr, 7, 5);
	do_test2(gr, 7, 3);

	graph_destroy(gr);
	return EXIT_SUCCESS;
}
