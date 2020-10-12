#ifndef GRID_H
#define GRID_H

#include "graph_generator.h"

class Grid : GraphGenerator{


public:

    Grid(unsigned int num);

    virtual Graph createGraph() const;



private:

    unsigned int n;

};

#endif
