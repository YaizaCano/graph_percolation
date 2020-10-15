#ifndef KD_TREE_H
#define KD_TREE_H

#include <vector>
#include <queue>
#include <list>
#include <memory>

typedef std::vector<float> PositionType;

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
     * @param p is the point at the root of the tree
     * @param d is the depth of the current tree (relative)
     * */
    KDTree(PositionType const& p, unsigned int id, float d=0);


    /**
     * @brief Add a new point to the tree
     * @param p is new point to add
     * */
    void add(PositionType const& p);

    /**
     * @brief Given a point it searches all the points in the tree that are inside its radius,
     *        excluding the same point
     * @param p center of the ball to search
     * @param radius is the radius of the search area
     * @returns a list of identifiers
     * */
    std::list<unsigned int> radiusRangeSearch(PositionType const& p, float radius) const;


private:

    /**
     * @brief Minkowski distance between two points
     * @param v1 is a point
     * @param v2 is another point with the same size as v1
     * @returns the distance between both points
     * */
    static float calculateDistance(PositionType const& v1, PositionType const& v2);

    /**
     * @brief Represents the depth of the tree
     * */
    unsigned int depth;

    /**
     * @brief Represents identifier of the current point, to avoid duplicates. 
     * */
    unsigned int identifier;

    /**
     * @brief Contains the value of the current node
     * */
    PositionType position;

    /**
     * @brief Contains a pointer to the left subtree
     * */
    std::unique_ptr<KDTree> left;

    /**
     * @brief Contains a pointer to the right subtree
     * */
    std::unique_ptr<KDTree> right;


};


#endif
