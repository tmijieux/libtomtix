#include "graph_matrix.hpp"

Graph::Graph(unsigned int verticesCount_, bool isOriented_):
	verticesCount(verticesCount_), isOriented(isOriented_)
{
	int s = verticesCount * verticesCount;
	this->adjacency = new bool [s];
	for (int i = 0; i < s; i++) {
		this->adjacency[i] = false;
	}
}

Graph::~Graph(void)
{
	delete [] this->adjacency;
}

void Graph::addEdge(int v_src, int v_dst)
{
	this->setEdge(v_src, v_dst, true);
}

void Graph::removeEdge(int v_src, int v_dst)
{
	this->setEdge(v_src, v_dst, false);
}

void Graph::setEdge(int v_src, int v_dst, bool value)
{
	this->adjacency[v_src * this->verticesCount + v_dst] = value;
	if (!this->isOriented)
		this->adjacency[v_dst * this->verticesCount + v_src] = value;
}

bool Graph::hasEdge(int v_src, int v_dst)
{
	return this->adjacency[v_src * this->verticesCount + v_dst];
}

unsigned int Graph::size(void)
{
	return this->verticesCount;
}
