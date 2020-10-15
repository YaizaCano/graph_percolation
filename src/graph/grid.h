#ifndef GRID_H
#define GRID_H

#include "graph_generator.h"

class Grid : public GraphGenerator{


public:

    Grid(unsigned int num);

    virtual Graph createGraph() const;

    virtual std::string name() const;

private:

    unsigned int n;

};

#endif
