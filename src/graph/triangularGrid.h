#ifndef TRIANGULAR_GRID_H
#define TRIANGULAR_GRID_H

#include "graph_generator.h"

class TriangularGrid :  GraphGenerator{

    public:

        TriangularGrid(unsigned int num);

        virtual TriangularGrid createGraph() const;

        virtual TriangularGrid std::string name() const;

    private:

        unsigned int n;

};

#endif
