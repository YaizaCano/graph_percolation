#ifndef KD_TREE_H
#define KD_TREE_H

#include <vector>
#include <list>
#include <memory>

typedef std::vector<float> PositionType;


class KDTree{

public:


    /**
     * @brief Basic constructor of a K dimensional tree
     * @param p is the point at the root of the tree
     * @param d is the depth of the current tree (relative)
     * */
    KDTree(PositionType const& p, float d=0);


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
     * @returns a list of k-dimensional positions 
     * */
    std::list<PositionType> radiusRangeSearch(PositionType const& p, float radius) const;


private:

    /**
     * @brief Represents the depth of the tree
     * */
    unsigned int depth;

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
