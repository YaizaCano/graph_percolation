#ifndef HYPERRECTANGLE_H
#define HYPERRECTANGLE_H


#include <vector>
#include <utility>

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
    Hyperrectangle(std::vector<float> const& maxs, std::vector<float> const& mins);

    /**
     * @brief A split of the hyperrectangle into two parts
     * @param axis is the dimension to do the split in
     * @param splitValue specifies where the split must be done
     * @returns a pair of hyperrectangles, (lesser, greater)
     * */
    std::pair<Hyperrectangle, Hyperrectangle> split(unsigned int axis, float splitValue) const;

private:

    /**
     * @brief Contains the list of maximum values of the rectangle
     * */
    std::vector<float> maxValues;

    /**
     * @brief Contains the list of minimum values of the rectangle
     * */
    std::vector<float> minValues;


};


#endif
