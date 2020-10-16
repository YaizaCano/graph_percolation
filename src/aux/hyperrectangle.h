#ifndef HYPERRECTANGLE_H
#define HYPERRECTANGLE_H

// DEBUG
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

typedef std::vector<float> IntervalValuesType;

/**
 * @class Hyperrectangle
 * @brief A Hyperrectangle is represented as the cartesian product of
 *        of intervals, it represents a rectangle (bounding box) used
 *        for multiple dimensions.
 *
 * */
class Hyperrectangle{

public:

    /**
     * @brief Basic constructor of an hyperrectangle based on a list of intervals
     * @param maxValues represents a list of the maximum values of the bounding box
     * @param minValues represents a list of the minimum values of the bounding box
     * */
    Hyperrectangle(IntervalValuesType const& maxs, IntervalValuesType const& mins);

    /**
     * @brief A split of the hyperrectangle into two parts
     * @param axis is the dimension to do the split in
     * @param splitValue specifies where the split must be done
     * @returns a pair of hyperrectangles, (lesser, greater)
     * */
    std::pair<Hyperrectangle, Hyperrectangle> split(unsigned int axis, float splitValue) const;

    float minDistance(Hyperrectangle const& other) const;

    float maxDistance(Hyperrectangle const& other) const;


    /**
     * @brief Minkowski distance between two points where p=2 (Eucledian distance)
     * @param v1 is a point
     * @param v2 is another point with the same size as v1
     * @returns the distance between both points
     * */
    static float calculateDistance(IntervalValuesType const& v1, IntervalValuesType const& v2);

private:


    static IntervalValuesType maximum(IntervalValuesType const& v1, IntervalValuesType const& v2);

    static IntervalValuesType minimum(IntervalValuesType const& v1, IntervalValuesType const& v2);

    static IntervalValuesType substract(IntervalValuesType const& v1, IntervalValuesType const& v2);

    /**
     * @brief Contains the list of maximum values of the rectangle
     * */
    IntervalValuesType maxValues;

    /**
     * @brief Contains the list of minimum values of the rectangle
     * */
    IntervalValuesType minValues;


};


#endif
