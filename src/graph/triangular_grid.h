#ifndef TRIANGULAR_GRID_H
#define TRIANGULAR_GRID_H

#include "graph_generator.h"

class TriangularGrid :  public GraphGenerator{

    public:

        TriangularGrid(unsigned int num);

        virtual Graph createGraph() const;

        virtual std::string name() const;

    private:

        unsigned int n;

};

#endif
