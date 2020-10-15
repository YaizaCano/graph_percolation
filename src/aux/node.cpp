#include "node.h"


InnerNode::InnerNode(float split, unsigned int dim, NodePtr ln, NodePtr rn){
    splitValue = split;
    dimension = dim;
    left = ln;
    right = rn; 
}


LeafNode::LeafNode(std::list<NodeIndex> const& i){
    indices = i;
}
