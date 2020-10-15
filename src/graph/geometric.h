#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include <vector>
#include <cmath>

#include "graph_generator.h"
#include "../random/rand_generator.h"

class Geometric : public GraphGenerator{


public:

    Geometric(unsigned int num, unsigned int dim, float r);

    virtual Graph createGraph() const;

    virtual std::string name() const;



private:

    std::vector<float> generatePosition() const;

    // pre: v1.size() == v2.size()
    static float calculateDistance(std::vector<float> const& v1, std::vector<float> const& v2);

    unsigned int n, dimension;
    float radius;

};



#endif
