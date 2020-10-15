#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include <vector>
#include <cmath>

#include "graph_generator.h"
#include "../random/rand_generator.h"
#include "../aux/kd_tree.h"

class Geometric : GraphGenerator{


public:

    Geometric(unsigned int num, unsigned int dim, float r);

    virtual Graph createGraph() const;





private:

    std::vector<float> generatePosition() const;


    unsigned int n, dimension;
    float radius;

};



#endif
