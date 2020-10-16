#include "hyperrectangle.h"


/** =================================
 *               PUBLIC
 *  =================================*/


Hyperrectangle::Hyperrectangle(IntervalValuesType const& maxs, IntervalValuesType const& mins){
    maxValues = maxs;
    minValues = mins;
}



std::pair<Hyperrectangle, Hyperrectangle> Hyperrectangle::split(unsigned int axis, float splitValue) const{
    // split less rectangle
    auto mid = maxValues;
    mid[axis] = splitValue;
    auto less = Hyperrectangle(minValues, mid);
    // split greater rectangle
    mid = minValues;
    mid[axis] = splitValue;
    auto greater = Hyperrectangle(mid, maxValues);
    return {less, greater};

}

float Hyperrectangle::minDistance(Hyperrectangle const& other) const{
    IntervalValuesType zeros(minValues.size(), 0);
    IntervalValuesType zeros2(minValues.size(), 0);
    auto max1 = maximum(substract(minValues, other.maxValues), substract(other.minValues, maxValues));
    auto max2 = maximum(zeros2, max1);
    float dis = calculateDistance(zeros, max2);
    std::cout << "DISTANCE: " << dis << std::endl; 
    return dis;
}

float Hyperrectangle::maxDistance(Hyperrectangle const& other) const{
    IntervalValuesType zeros(minValues.size(), 0);
    return calculateDistance(zeros,
            maximum(substract(maxValues, other.minValues), substract(other.maxValues, minValues)));
}


IntervalValuesType Hyperrectangle::substract(IntervalValuesType const& v1, IntervalValuesType const& v2){
    IntervalValuesType sub;
    sub.reserve(v1.size());
    for(int i = 0; i < v1.size(); ++i){
        sub.push_back(v1[i] - v2[i]);
    }
    return sub;
}

IntervalValuesType Hyperrectangle::maximum(IntervalValuesType const& v1, IntervalValuesType const& v2){
    IntervalValuesType maxVector;
    maxVector.reserve(v1.size());
    for(int i = 0; i < v1.size(); ++i){
        if(v1[i] > v2[i])maxVector.push_back(v1[i]);
        else maxVector.push_back(v2[i]);
    }
    return maxVector;
}


float Hyperrectangle::calculateDistance(IntervalValuesType const& v1, IntervalValuesType const& v2){
    auto size = v1.size();
    float distance = 0;
    for(auto i = 0; i < size; ++i){
        auto tmp = v1[i] + v2[i];
        distance += tmp*tmp;
    }

    return sqrt(distance);
}
