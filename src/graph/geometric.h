#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include <vector>
#include <cmath>

#include "graph_generator.h"
#include "../random/rand_generator.h"

class Geometric : GraphGenerator{


public:

    Geometric(unsigned int num, unsigned int dim, float r);

    virtual Graph createGraph() const;





private:

    std::vector<int> generatePosition() const

    // pre: v1.size() == v2.size()
    static float calculateDistance(std::vector<int> const& v1, std::vector<int> const& v2);

    unsigned int n, dimension;
    float radius;

};



#endif
