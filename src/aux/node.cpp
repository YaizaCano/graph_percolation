#include "node.h"



Node::Node(float split, unsigned int dim, NodePtr ln, NodePtr rn){
    splitValue = split;
    dimension = dim;
    left = ln;
    right = rn;
    leaf = false;
    id = idCounter++;
}

Node::Node(std::list<NodeIndex> const& i){
    indices = i;
    leaf = true;
    id = idCounter++;
}


std::list<NodeIndex> Node::getIndices() const{
    return indices; 
}

bool Node::operator==(Node const& other) const{
    return id == other.id;
}


bool Node::isLeaf() const{
    return leaf;
}



unsigned int Node::getDimension() const{
    return dimension;
}

float Node::getSplitValue() const{
    return splitValue;
}

NodePtr Node::leftNode() const{
    return left;
}

NodePtr Node::rightNode() const{
    return right;
}
