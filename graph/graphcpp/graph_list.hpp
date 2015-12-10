#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include <vector>
#include <list>

class Graph {
public:
	Graph(unsigned int verticesCount, bool isOriented=true);
	~Graph(void);
	
	void addEdge(int v_src, int v_dst);
	void removeEdge(int v_src, int v_dst);
	bool hasEdge(int v_src, int v_dst);
	unsigned int size(void);
	
private:
	bool isOriented;
	unsigned int verticesCount;
	std::vector<std::list<int> > adjacency;
};

#endif //GRAPH_LIST_H
