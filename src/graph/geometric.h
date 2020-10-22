#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include <vector>

#include "graph_generator.h"
#include "../random/rand_generator.h"
#include "../tree/kd_tree.h"

class Geometric : public GraphGenerator{


public:

    Geometric(unsigned int num, unsigned int dim, float r);

    virtual Graph createGraph() const;

    virtual std::string name() const;



private:

    BondPairs addPairs(int begin, int end, std::vector<std::vector<float>> const& positions) const;

    void concurrentRadiusRange(Graph& g, std::vector<std::vector<float>> const& positions) const;

    std::vector<float> generatePosition() const;

    unsigned int n, dimension;
    float radius;

};



#endif
