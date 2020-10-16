#include "node.h"


/** =================================
 *            INNER NODE
 *  =================================*/

InnerNode::InnerNode(float split, unsigned int dim, NodePtr ln, NodePtr rn){
    splitValue = split;
    dimension = dim;
    left = ln;
    right = rn;
}


bool InnerNode::isLeaf() const{
    return false;
}

/** =================================
 *              LEAF NODE
 *  =================================*/

bool LeafNode::isLeaf() const{
    return true; 
}

LeafNode::LeafNode(std::list<NodeIndex> const& i){
    indices = i;
}
