#include <stdlib.h>
#include "tree.hpp"
#include "tree_node.hpp"

Tree::Tree():
    rootSentinel(NULL) {}

Tree::Tree(Tree::Node& rootNode)
{
    this->rootSentinel = new Tree::Node(Tree::Node::SENTINEL_NODE, NULL);
    this->rootSentinel->setLeftChild(rootNode);
}

Tree::Node& Tree::getRootNode(void)
{
    return this->rootSentinel->getLeftChild();
}

Tree::~Tree(void)
{
    delete &this->rootSentinel->getLeftChild();
    delete this->rootSentinel;
}
