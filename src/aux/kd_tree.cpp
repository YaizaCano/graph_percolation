#include "kd_tree.h"


/** =================================
 *               PUBLIC
 *  =================================*/

KDTree::KDTree(PositionType const& p, float d){
    position = p;
    depth = d;
}

void KDTree::add(PositionType const& p){
    auto dimension = depth % p.size();
    if(position[dimension] > p[dimension]){
        if(left == nullptr)
            left = std::make_unique(KDTree(p, depth + 1));
        else
            left.add(p);
    }
    else{
        if(right == nullptr)
            right = std::make_unique(KDTree(p, depth + 1));
        else
            right.add(p);
    }
}



std::list<PositionType> KDTree::findClosest(PositionType const& p, float radius) const{
    std::list<PositionType> closest;
    

    return closest;
}
