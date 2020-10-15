#include "kd_tree.h"


/** =================================
 *               PUBLIC
 *  =================================*/

KDTree::KDTree(PositionType const& p, unsigned int id,  float d){
    position = p;
    depth = d;
    identifier = id;
}

void KDTree::add(PositionType const& p){
    auto dimension = depth % p.size();
    if(position[dimension] > p[dimension]){
        if(left == nullptr)
            left = std::make_shared(KDTree(p, depth + 1));
        else
            left.add(p);
    }
    else{
        if(right == nullptr)
            right = std::make_shared(KDTree(p, depth + 1));
        else
            right.add(p);
    }
}



std::list<PositionType> KDTree::radiusRangeSearch(PositionType const& p, float radius) const;{
    std::list<unsigned int> closest;
    std::queue<std::shared_ptr<KDTree>> candidates;
    candidates.push(std::make_shared(*this));

    while(!candidates.empty()){
        auto current = candidates.top();
        candidates.pop();
        if(current != nullptr){
            if(distance(current.position, p) <= radius)closest.push_back(current.identifier);

        }
    }


    return closest;
}

/** =================================
 *               PRIVATE
 *  =================================*/


float KDTree::calculateDistance(PositionType const& v1, PositionType const& v2){
    auto size = v1.size();
    float distance = 0;
    for(auto i = 0; i < size; ++i){
        distance += v1[i]*v1[i] + v2[i]*v2[i];
    }

    return sqrt(distance);
}
