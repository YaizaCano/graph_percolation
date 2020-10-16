#ifndef KD_TREE_H
#define KD_TREE_H

#include <vector>
#include <queue>
#include <list>
#include <memory>
#include <future>

#include "hyperrectangle.h"
#include "node.h"




typedef std::vector<float> PositionType;
typedef std::list<std::pair<NodeIndex, NodeIndex>> BondPairs;


/**
 * @class KDTree
 * @brief A KDTree is a k-dimensional binary tree used to represents points
 *        of multiple dimensions within the space, it is used to generate
 *        random geometric graphs as it is more efficient to calculate
 *        pairs witihn a radius search.
 * */
class KDTree{

public:


    /**
     * @brief Basic constructor of a K dimensional tree
     * @param data is a list of points to add to the tree
     * */
    KDTree(std::vector<PositionType> const& d);


    /**
     * @brief Given a search radius it calculates all the pairs of points that
     *        are within that ditance
     * @param p center of the ball to search
     * @param radius is the radius of the search area
     * @returns a list of pairs of identifiers
     * */
    BondPairs radiusRangeSearch(float radius) const;


private:

    /**
     * @brief Builds the entire KDTree recursively using a sliding-midpoint subdivision
     *        (Maneewongvatana, It's okay to be skinny, if your friends are fat, 1999)
     * @param idx contains the indices of the current node area
     * @param maxes contains the maximum values for the indices specified
     * @param mins contains the minimum values for the indices
     * @retursn a node containing all the subtree
     * */
    std::shared_ptr<Node> build(std::list<NodeIndex> const& idx,
                                IntervalValuesType const& maxes,
                                IntervalValuesType const& mins, int depth=0) const;


    void traverseCheckRectangles(BondPairs& connections, NodePtr const& left, Hyperrectangle const& leftR,
                                 NodePtr const& right, Hyperrectangle const& rightR, float radius) const;

    void traverseSimple(BondPairs& connections, NodePtr const& left, NodePtr const& right) const;

    /**
     * @brief Filters all the indices, whose value is lower or equal than the split value
     * @param indices to filter
     * @param dim is the dimension in which to filter the data points
     * @param split is the separation value
     * @returns returns a list of indices
     * */
    std::list<NodeIndex> filterLower(std::list<NodeIndex> const& indices, unsigned int dim, float split)const;

    /**
     * @brief Filters all the indices, whose value is bigger than the split value
     * @param indices to filter
     * @param dim is the dimension in which to filter the data points
     * @param split is the separation value
     * @returns returns a list of indices
     * */
    std::list<NodeIndex> filterBigger(std::list<NodeIndex> const& indices, unsigned int dim, float split)const;

    /**
     * @brief Find the minimum value of the data based on the indices given
     * @param indices to work with
     * @param dim is the dimension to calculate the minimum in
     * @returns the minimum value
     * */
    float findMin(std::list<NodeIndex> const& indices, unsigned int dim) const;

    /**
     * @brief Find the maximum value of the data based on the indices given
     * @param indices to work with
     * @param dim is the dimension to calculate the maximum in
     * @returns the maximum value
     * */
    float findMax(std::list<NodeIndex> const& indices, unsigned int dim) const;

    /**
     * @brief Finds the biggest value of a substraction of vectors and returns its argument
     * @param a an array
     * @param b the other array
     * @returns the argument of the biggest substraction
     * */
    static unsigned int argmax(IntervalValuesType const& a, IntervalValuesType const& b);

    /**
     * @brief Creates a list of numbers enumerated from 0 to n - 1
     * @param size is equal the number of elements
     * @returns a list of consecutive integers
     * */
    static std::list<NodeIndex> arange(unsigned int size);


    /**
     * @brief For each dimension, it calculates its maximum
     * @param values is a sequence of positions with multiple dimensions
     * @returns a vector of max values, one per dimension
     * */
    static std::vector<float> maximumValues(std::vector<PositionType> const& values);

    /**
     * @brief For each dimension, it calculates its minimum
     * @param values is a sequence of positions with multiple dimensions
     * @returns a vector of min values, one per dimension
     * */
    static std::vector<float> minimumValues(std::vector<PositionType> const& values);

    /**
     * @brief Contains the positions data of the tree
     * */
    std::vector<PositionType> data;

    /**
     * @brief Contains the list of maximum values of the data
     * */
    std::vector<float> maxValues;

    /**
     * @brief Contains the list of minimum values of data
     * */
    std::vector<float> minValues;

    /**
     * @brief Contains the tree data structure
     * */
    std::shared_ptr<Node> tree;

    /**
     * @brief Specifies the minimum size in which a partition is made,
     *        when the number of indices to split is less than
     *        MIN_LEAF_SIZE, they are all saved in a leaf node.
     * */
    static const unsigned int MIN_LEAF_SIZE = 10;


};


#endif
