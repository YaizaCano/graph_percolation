#include "kd_tree.h"


/** =================================
 *               PUBLIC
 *  =================================*/


KDTree::KDTree(std::vector<PositionType> const& d){
    data = d;
    maxValues = maximumValues(data);
    minValues = minimumValues(data);

    tree = build(arange(d.size()), maxValues, minValues);

}


BondPairs KDTree::radiusRangeSearch(float radius) const{
    BondPairs connections;
    // create initial hyperrectangle
    Hyperrectangle rectangle(maxValues, minValues);
    // traverse tree by comparing hyperrectangles
    traverseCheckRectangles(connections, tree, rectangle, tree, rectangle, radius);

    return connections;
}

/** =================================
 *               PRIVATE
 *  =================================*/




 std::shared_ptr<Node> KDTree::build(std::vector<NodeIndex> const& idx,
                             IntervalValuesType const& maxes,
                             IntervalValuesType const& mins){
    // if the size of the indices that we are inserting into the tree
    // are less than a specific threshold, then we add them all inside
    // a leaf node
    if(idx.size() > MIN_LEAF_SIZE){
        // we first calculate the dimension
        // with maximum range
        auto dim = argmax(maxes, mins);
        auto maxValue = maxes[dim];
        auto minValue = mins[dim];
        // we then calculate a possible split value as the
        // center in the selected dimension, we then
        // filter the data that based on its value
        float split = (maxValue + minValue) / 2.0;
        std::list<NodeIndex> lessIndices = filterLower(idx, split);
        std::list<NodeIndex> greaterIndices = filterBigger(idx, split);

        // if the left data is empty, we must move the split
        // to the closest index
        if(lessIndices.empty()){
            split = findMin(idx);
            lessIndices = filterLower(idx, split);
            greaterIndices = filterBigger(idx, split);
        }
        // if the right data is empty we must move the split
        // data to the closest index
        if(greaterIndices.empty()){
            split = findMax(idx);
            lessIndices = filterLower(idx, split);
            greaterIndices = filterBigger(idx, split);
        }
        // finally we create the subddivision of the maximum and minimum
        // values of the left and right subtree
        auto lessMaxValues = maxes;
        lessMaxValues[dim] = split;
        auto greaterMinValues = mins;
        greaterMinValues[dim] = split;
        // finally, we recursively build the left and right subtree 
        return InnerNode(split, dim,
                        build(lessIndices, lessMaxValues, mins),
                        build(greaterIndices, maxes, greaterMinValues));

    }
    else{
        return LeafNode(idx);
    }

}

void KDTree::traverseCheckRectangles(BondPairs& connections, NodePtr const& left, Hyperrectangle const& leftR,
                             NodePtr const& right, Hyperrectangle const& rightR, float radius) const{

    // distance between hyperrectangles must be less than the
    // minimum possible distance, that is the radius. Otherwise
    // the rectangles do not intersect and don't have any connected
    // components
    if(leftR.minDistance(rightR) <= radius){
        // if the maximum possible distance between rectangles is less
        // than the radius, that means that the rectangles are inside each
        // other, and all components are connected between them
        if(leftR.maxDistance(rightR) <= radius){
            // traverses the tree without checking distances
            traverseSimple(connections, left, right);
        }
        if(left->isLeaf()){

        }
        else if(right->isLeaf()){

        }
        else{

        }

    }

}

void KDTree::traverseSimple(BondPairs& connections, NodePtr const& left, NodePtr const& right) const{

}

std::list<NodeIndex> KDTree::filterLower(std::vector<NodeIndex> const& indices, unsigned int dim, float split) const{
    std::list<NodeIndex> filteredIndices;
    for(auto const& i : indices){
        if(data[i][dim] <= split)filteredIndices.push_back(i);
    }

    return filteredIndices;
}

std::list<NodeIndex> KDTree::filterBigger(std::vector<NodeIndex> const& indices, unsigned int dim, float split) const{
    std::list<NodeIndex> filteredIndices;
    for(auto const& i : indices){
        if(data[i][dim] > split)filteredIndices.push_back(i);
    }

    return filteredIndices;
}

 float KDTree::findMin(std::vector<NodeIndex> const& indices, unsigned int dim) const{
     auto min = data[indices[0]][dim];
     for(int i = 1; i < indices.size(); ++i){
         if(data[indices[i]][dim] < min){
             min = data[indices[i]][dim];
         }
     }
     return min;
 }

 float KDTree::findMax(std::vector<NodeIndex> const& indices, unsigned int dim) const{
     auto max = data[indices[0]][dim];
     for(int i = 1; i < indices.size(); ++i){
         if(data[indices[i]][dim] > max){
             max = data[indices[i]][dim];
         }
     }
     return max;
 }

unsigned int KDTree::argmax(IntervalValuesType const& a, IntervalValuesType const& b){
    auto max = a[0] - b[0];
    auto arg = 0;
    for(int i = 1; i < a.size(); ++i){
        auto sub = a[i] - b[i];
        if(sub > max){
            max = sub;
            arg = i;
        }
    }

    return arg;
}


 std::vector<unsigned int> KDTree::arange(unsigned int size){
     std::vector<unsigned int> tensor;
     tensor.reserve(size);
     for(int i = 0; i < size; ++i)tensor.push_back(i);
     return tensor;
 }


std::vector<float> KDTree::maximumValues(std::vector<PositionType> const& values){
    // create output a value per dimension
    auto dim = values[0].size();
    std::vector<float> output(dim, 0);
    for(auto const&  v : values){
        for(int i = 0; i < dim; ++i){
            if(v[i] > output[i])output[i] = v[i];
        }
    }

    return output;
}

std::vector<float> KDTree::minimumValues(std::vector<PositionType> const& values){
    // create output a value per dimension
    auto dim = values[0].size();
    std::vector<float> output(dim, 1);
    for(auto const&  v : values){
        for(int i = 0; i < dim; ++i){
            if(v[i] < output[i])output[i] = v[i];
        }
    }

    return output;
}
