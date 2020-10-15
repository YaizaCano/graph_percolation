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


std::list<unsigned int> KDTree::radiusRangeSearch(PositionType const& p, float radius) const{

}

/** =================================
 *               PRIVATE
 *  =================================*/




 std::shared_ptr<Node> KDTree::build(std::vector<NodeIndex> const& idx,
                             std::vector<float> const& maxes,
                             std::vector<float> const& mins){

    if(idx.size() > MIN_LEAF_SIZE){
        auto dim = argmax(maxes, mins);
        auto maxValue = maxes[dim];
        auto minValue = mins[dim];

        float split = (maxValue + minValue) / 2.0;
        std::list<NodeIndex> lessIndices = filterLower(idx, split);
        std::list<NodeIndex> greaterIndices = filterBigger(idx, split);

        if(lessIndices.empty()){
            split = findMin(idx);
            lessIndices = filterLower(idx, split);
            greaterIndices = filterBigger(idx, split);
        }
        if(greaterIndices.empty()){
            split = findMax(idx);
            lessIndices = filterLower(idx, split);
            greaterIndices = filterBigger(idx, split);
        }

        auto lessMaxValues = maxes;
        lessMaxValues[dim] = split;
        auto greaterMinValues = mins;
        greaterMinValues[dim] = split;
        return InnerNode(split, dim,
                        build(lessIndices, lessMaxValues, mins),
                        build(greaterIndices, maxes, greaterMinValues));

    }
    else{
        return LeafNode(idx);
    }




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

unsigned int KDTree::argmax(std::vector<float> const& a, std::vector<float> const& b){
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
