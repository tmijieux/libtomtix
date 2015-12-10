#include <cstdlib>
#include "tree_node.hpp"

Tree::Node::Node(NodeType type, void *data_):
    data(data_)
{
    switch (type) {
    case SENTINEL_NODE:
	this->isSentinel_ = 1;
	break;
    case INTERNAL_NODE:
	this->isSentinel_ = 0;
	break;
    case LEAF_NODE:
	this->isSentinel_ = 0;
	this->leftChild = new Tree::Node(SENTINEL_NODE, NULL);
	this->rightChild = new Tree::Node(SENTINEL_NODE, NULL);
	break;
    }
}

Tree::Node::~Node(void)
{
    if (!this->isSentinel_) {
	delete this->leftChild;
	delete this->rightChild;
    }
}

bool Tree::Node::isSentinel(void)
{
    return this->isSentinel_;
}

Tree::Node& Tree::Node::getRightChild(void)
{
    return *this->rightChild;
}

void Tree::Node::setRightChild(Tree::Node& t)
{
    this->rightChild = &t;
}

Tree::Node& Tree::Node::getLeftChild(void)
{
    return *this->leftChild;
}

void Tree::Node::setLeftChild(Tree::Node& t)
{
    this->leftChild = &t;
}

void Tree::Node::setData(void *data)
{
    this->data = data;
}

void* Tree::Node::getData(void)
{
    return this->data;
}
