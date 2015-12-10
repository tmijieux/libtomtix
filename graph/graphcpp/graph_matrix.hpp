#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

class Graph {
public:
	Graph(unsigned int verticesCount, bool isOriented=true);
	~Graph(void);
	
	void addEdge(int v_src, int v_dst);
	void removeEdge(int v_src, int v_dst);
	bool hasEdge(int v_src, int v_dst);
	unsigned int size(void);
private:
	void setEdge(int v_src, int v_dst, bool value);
		
	bool isOriented;
	unsigned int verticesCount;
	bool *adjacency;
};

#endif //GRAPH_MATRIX_H
