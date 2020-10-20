#ifndef NODE_H
#define NODE_H

#include <memory>
#include <list>

class Node;


typedef unsigned int NodeIndex;

typedef std::shared_ptr<Node> NodePtr;

class Node{


public:

    // constructor for leaf node
    Node(std::list<NodeIndex> const& i);

    // constructor for inner node
    Node(float split, unsigned int dim, NodePtr left, NodePtr right);

    unsigned int getDimension() const;

    float getSplitValue() const;

    std::list<NodeIndex> getIndices() const;

    bool isLeaf() const;

    NodePtr leftNode() const;

    NodePtr rightNode() const;

    bool operator==(Node const& other) const;

private:

    static unsigned int idCounter;

    unsigned int id;

    bool leaf;

    std::list<NodeIndex> indices;

    unsigned int dimension; // split dimension

    float splitValue;

    NodePtr left; // lesser

    NodePtr right; // greater


};




#endif
