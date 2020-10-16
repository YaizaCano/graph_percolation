#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include <vector>

#include "graph_generator.h"
#include "../random/rand_generator.h"
#include "../aux/kd_tree.h"

class Geometric : public GraphGenerator{


public:

    Geometric(unsigned int num, unsigned int dim, float r);

    virtual Graph createGraph() const;

    virtual std::string name() const;



private:

    std::vector<float> generatePosition() const;

    unsigned int n, dimension;
    float radius;

};



#endif
