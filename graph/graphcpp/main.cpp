#include <iostream>
#include <cstdlib>

#include "graph_list.hpp"

using namespace std;

void testEdge(Graph &G, int v_src, int v_dst)
{
	cout << "arête " << v_src  << "->"  << v_dst  <<"? "
	     << (G.hasEdge(v_src, v_dst) ? "oui" : "non") << endl;
}

int main(int argc, char *argv[])
{
	Graph G(10, false);

	G.addEdge(3, 4);
	testEdge(G, 3, 4);
	testEdge(G, 4, 5);
	testEdge(G, 4, 3);
	
	return EXIT_SUCCESS;
}
