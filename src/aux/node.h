#ifndef NODE_H
#define NODE_H

#include <memory>


typedef unsigned int NodeIndex;

/**
 * @class Node
 * @brief Represents a node in a KDTree
 * */
class Node{

public:

private:

};

/**
 * @class LeafNode
 * @brief Represents a leaf in a KDTree, a leaf contains a list of
 *        positions of the k-dimensional data
 * */
class LeafNode : public Node{

public:

    LeafNode(std::list<NodeIndex> const& i);

private:

    std::list<NodeIndex> indices;



};


typedef std::shared_ptr<Node> NodePtr;


/**
 * @class InnerNode
 * @brief Represents an inner node in a KDTree, this node has reference
 *        to the left and right subtrees and contains the partition of the
 *        space into two hyperrectangles.
 * */
class InnerNode : public Node{


public:


    InnerNode(float split, unsigned int dim, NodePtr left, NodePtr right);


private:


    unsigned int dimension; // split dimension

    float splitValue;

    NodePtr left; // lesser

    NodePtr right; // greater


};


#endif
