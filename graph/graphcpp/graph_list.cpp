#include "graph_list.hpp"

#include <vector>
#include <list>
#include <iterator>

static
std::list<int>::iterator
find_pos(std::list<int> &list, int el)
{
	std::list<int>::iterator it;
	for (it = list.begin(); it != list.end(); it++) {
		if (*it == el)
			return it;
	}
	return it;
}

static
bool
find(std::list<int> &list, int el)
{
	std::list<int>::iterator it;
	it = find_pos(list, el);
	if (it != list.end() && *it == el)
		return true;
	return false;
}

Graph::Graph(unsigned int verticesCount_, bool isOriented_):
	verticesCount(verticesCount_),
	isOriented(isOriented_)
{
	this->adjacency = std::vector<std::list<int> >(verticesCount);
}

Graph::~Graph(void)
 { }

void Graph::addEdge(int v_src, int v_dst)
{
	if (!find(this->adjacency[v_src], v_dst)) {
		this->adjacency[v_src].push_front(v_dst);
		if (!this->isOriented) {
			this->adjacency[v_dst].push_front(v_src);
		}
	}
}

void Graph::removeEdge(int v_src, int v_dst)
{
	this->adjacency[v_src].remove(v_dst);
	if (!this->isOriented) {
		this->adjacency[v_dst].push_front(v_src);
	}
}

bool Graph::hasEdge(int v_src, int v_dst)
{
	return find(this->adjacency[v_src], v_dst);
}

unsigned int Graph::size(void)
{
	return this->verticesCount;
}

