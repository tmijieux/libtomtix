#ifndef TREE_H
#define TREE_H

class Tree {
public:
    struct Node {
	enum NodeType {
	    ROOT_NODE,
	    SENTINEL_NODE,
	    LEAF_NODE,
	    INTERNAL_NODE
	};
	
	Node(NodeType t, void *el);
	~Node();
	
	Node& getRightChild(void);
	Node& getLeftChild(void);
	
	bool isSentinel(void);
	void* getData(void);
	
	void setRightChild(Node& rightChild);
	void setLeftChild(Node& leftChild);
	void setData(void *data);
    private:
	void *data;
	Node *leftChild;
	Node *rightChild;
	bool isSentinel_;
	
    };
    
    // create a tree whose root node is the given argument
    Tree();
    Tree(Node& rootNode);
    ~Tree(void);

    
    Node& getRootNode(void);
    
private:
    Node *rootSentinel;
};

#endif //TREE_H
