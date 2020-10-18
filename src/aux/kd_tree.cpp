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
    int threadCount = 0;
    traverseCheckRectangles(connections, tree, rectangle, tree, rectangle, radius, threadCount);

    return connections;
}

/** =================================
 *               PRIVATE
 *  =================================*/




 std::shared_ptr<Node> KDTree::build(std::list<NodeIndex> const& idx,
                             IntervalValuesType const& maxes,
                             IntervalValuesType const& mins, int depth) const{
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
        std::list<NodeIndex> lessIndices = filterLower(idx, dim, split);
        std::list<NodeIndex> greaterIndices = filterBigger(idx, dim, split);

        // if the left data is empty, we must move the split
        // to the closest index
        if(lessIndices.empty()){
            split = findMin(idx, dim);
            lessIndices = filterLower(idx, dim, split);
            greaterIndices = filterBigger(idx,dim,  split);
        }
        // if the right data is empty we must move the split
        // data to the closest index
        if(greaterIndices.empty()){
            split = findMax(idx, dim);
            lessIndices = filterLower(idx, dim, split);
            greaterIndices = filterBigger(idx, dim, split);
        }
        // finally we create the subddivision of the maximum and minimum
        // values of the left and right subtree
        auto lessMaxValues = maxes;
        lessMaxValues[dim] = split;
        auto greaterMinValues = mins;
        greaterMinValues[dim] = split;
        // finally, we recursively build the left and right subtree
        if(depth < 2){
            auto futureLeft = std::async(&KDTree::build, this, lessIndices, lessMaxValues, mins, depth + 1);
            auto futureRight = std::async(&KDTree::build, this, greaterIndices, maxes, greaterMinValues, depth + 1);

            return std::make_shared<Node>(Node(split, dim, futureLeft.get(), futureRight.get()));
        }
        else{
            return std::make_shared<Node>(Node(split, dim,
                        build(lessIndices, lessMaxValues, mins, depth + 1),
                        build(greaterIndices, maxes, greaterMinValues, depth + 1)));
        }


    }
    else{
        return std::make_shared<Node>(Node(idx));
    }

}

void KDTree::traverseCheckRectangles(BondPairs& connections, NodePtr const& left, Hyperrectangle const& leftR,
                             NodePtr const& right, Hyperrectangle const& rightR, float radius, int& threadCount) const{

    // distance between hyperrectangles must be less than the
    // minimum possible distance, that is the radius. Otherwise
    // the rectangles do not intersect and don't have any connected
    // components
    if(leftR.minDistance(rightR) <= radius){
        // if the maximum possible distance between rectangles is less
        // than the radius, that means that the rectangles are inside each
        // other, and all components are connected between them
        /*if(leftR.maxDistance(rightR) <= radius){
            // traverses the tree without checking distances
            traverseSimple(connections, left, right);
        }*/
        if(left->isLeaf()){
            // if both nodes are leaf nodes, we add the possible
            // pairs based on their positions
            // otherwise we must continue traversing the tree in the
            // right direction
            if(right->isLeaf()){
                auto leftIndices = left->getIndices();
                auto rightIndices = right->getIndices();
                if(*left == *right){
                    for(auto const& i : leftIndices){
                        for(auto const& j : rightIndices){
                            if(Hyperrectangle::calculateDistance(data[i], data[j]) <= radius && i < j){
                                std::lock_guard<std::mutex> lock(nodeListMutex);
                                connections.push_back({i, j});
                            }
                        }
                    }
                }
                else{
                    for(auto const& i : leftIndices){
                        for(auto const& j : rightIndices){
                            if(Hyperrectangle::calculateDistance(data[i], data[j]) <= radius && i != j){
                                std::lock_guard<std::mutex> lock(nodeListMutex);
                                connections.push_back({i, j});
                            }
                        }
                    }
                }
            }
            else{
                auto splitRight = rightR.split(right->getDimension(), right->getSplitValue());
                traverseCheckRectangles(connections, left, leftR,
                                        right->leftNode(), splitRight.first, radius, threadCount);
                traverseCheckRectangles(connections, left, leftR,
                                        right->rightNode(), splitRight.second, radius, threadCount);
            }
        }
        else if(right->isLeaf()){
            // if the right is leaf, we must continue traversing the tree in
            // the left direction
            auto splitLeft = leftR.split(left->getDimension(), left->getSplitValue());
            traverseCheckRectangles(connections, left->leftNode(), splitLeft.first,
                                    right, rightR, radius, threadCount);
            traverseCheckRectangles(connections, left->rightNode(), splitLeft.second,
                                    right, rightR, radius, threadCount);
        }
        else{
            // There isn't any leaf node, so we must traverse all directions
            // possible.
            auto splitLeft = leftR.split(left->getDimension(), left->getSplitValue());
            auto splitRight = rightR.split(right->getDimension(), right->getSplitValue());
            // we first define two threads
            std::thread t1, t2;
            // the thread counter needs to be read and updated so
            // we must lock it first, if we create a thread or not
            // we must not forget to unlock the mutex
            threadCounterMutex.lock();
            if(threadCount < 6){
                // if we currently have less than 6 threads running
                // we can create one
                threadCount += 1;
                threadCounterMutex.unlock();
                t1 = std::thread(&KDTree::traverseCheckRectangles, this, std::ref(connections), left->leftNode(), splitLeft.first,
                                        right->leftNode(), splitRight.first, radius, std::ref(threadCount));
            }
            else{
                threadCounterMutex.unlock();
                traverseCheckRectangles(connections, left->leftNode(), splitLeft.first,
                                        right->leftNode(), splitRight.first, radius, threadCount);
            }
            // we make the same appraoch as before
            threadCounterMutex.lock();
            if(threadCount < 6){
                threadCount += 1;
                threadCounterMutex.unlock();
                t2  = std::thread(&KDTree::traverseCheckRectangles, this, std::ref(connections), left->leftNode(), splitLeft.first,
                                        right->rightNode(), splitRight.second, radius, std::ref(threadCount));
            }
            else{
                threadCounterMutex.unlock();
                traverseCheckRectangles(connections, left->leftNode(), splitLeft.first,
                                        right->rightNode(), splitRight.second, radius, threadCount);
            }

            // we leave the following two functions free for the maint thread to execute
            // the first time we call this subrutine we won't enter this condition
            if(!(*left == *right)){
                // traverse right with left
                traverseCheckRectangles(connections, left->rightNode(), splitLeft.second,
                                        right->leftNode(), splitRight.first, radius, threadCount);
            }
            // traverse right with right
            traverseCheckRectangles(connections, left->rightNode(), splitLeft.second,
                                    right->rightNode(), splitRight.second, radius, threadCount);
            // if we have created new threads we must wait for them
            // to complete their execution 
            if(t1.joinable())t1.join();
            if(t2.joinable())t2.join();
        }
    }
}

void KDTree::traverseSimple(BondPairs& connections, NodePtr const& left, NodePtr const& right) const{
    if(left->isLeaf()){
        // if both nodes are leaf nodes, we add the possible
        // pairs based on their positions
        // otherwise we must continue traversing the tree in the
        // right direction
        if(right->isLeaf()){
            auto leftIndices = left->getIndices();
            auto rightIndices = right->getIndices();
            if(*left == *right){
                for(auto const& i : leftIndices){
                    for(auto const& j : rightIndices){
                        if(i < j){
                            connections.push_back({i, j});
                        }
                    }
                }
            }
            else{
                for(auto const& i : leftIndices){
                    for(auto const& j : rightIndices){
                        if(i != j){
                            connections.push_back({i, j});
                        }
                    }
                }
            }
        }
        else{
            traverseSimple(connections, left, right->leftNode());
            traverseSimple(connections, left, right->rightNode());
        }
    }
    else{
        // There isn't any leaf node, so we must traverse all directions
        // possible.
        if(*left == *right){
            traverseSimple(connections, left->leftNode(), right->leftNode());
            traverseSimple(connections, left->leftNode(), right->rightNode());
            traverseSimple(connections, left->rightNode(), right->rightNode());
        }
        else{
            traverseSimple(connections, left->leftNode(), right);
            traverseSimple(connections, left->rightNode(), right);
        }


    }
}

std::list<NodeIndex> KDTree::filterLower(std::list<NodeIndex> const& indices, unsigned int dim, float split) const{
    std::list<NodeIndex> filteredIndices;
    for(auto const& i : indices){
        if(data[i][dim] <= split)filteredIndices.push_back(i);
    }

    return filteredIndices;
}

std::list<NodeIndex> KDTree::filterBigger(std::list<NodeIndex> const& indices, unsigned int dim, float split) const{
    std::list<NodeIndex> filteredIndices;
    for(auto const& i : indices){
        if(data[i][dim] > split)filteredIndices.push_back(i);
    }

    return filteredIndices;
}

 float KDTree::findMin(std::list<NodeIndex> const& indices, unsigned int dim) const{
     auto min = data[*indices.begin()][dim];

     for(auto const& i : indices){
         if(data[i][dim] < min){
             min = data[i][dim];
         }
     }

     return min;
 }

 float KDTree::findMax(std::list<NodeIndex> const& indices, unsigned int dim) const{
     auto max = data[*indices.begin()][dim];

     for(auto const& i : indices){
         if(data[i][dim] > max){
             max = data[i][dim];
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


 std::list<NodeIndex> KDTree::arange(unsigned int size){
     std::list<unsigned int> tensor;
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
