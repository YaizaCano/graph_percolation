#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H

#include "graph.h"


/**
 * @class GraphGenerator
 * @brief Generates a graph given a set of parameters.
 *
 * */
class GraphGenerator{

public:


    /**
     * @brief Creates a graph
     * @returns the graph
     * */
    virtual Graph createGraph() const = 0;

    /**
     * @brief Getter for the name of the current generator
     * @returns the name of the generator 
     * */
    virtual std::string name() const = 0

};


#endif
