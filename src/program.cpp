#include <iostream>

#include "random/rand_generator.h"
#include "graph/grid.h"
#include "graph/geometric.h"
#include "graph/graph.h"

// el rand generator ha de ser directament proporcional al radi
// en el cas de Geometric ja que si el espai de posicions es molt gran
// el radi a de ser mes gran per compensar.

int main(){
    RandGenerator::setSeed(445);
    int n = 500;
    int dim = 2;
    float radius = 0.7;
    Grid grid(n);

    Graph g = grid.createGraph();

    std::cout << "Graph created!" << std::endl;
    auto components = g.getTotalConnectedComponents();
    float step = 0.02;
    long int old_components = 0;

    for(float i = 0; i <= 1; i += step){
        std::cout << "Using q=" << i << std::endl;
        auto g_p = Graph::applyBondPercolation(g, i);
        components = g_p.getTotalConnectedComponents();
        std::cout << "Connected Components: " << components << std::endl;
        std::cout << "Differece: " << components - old_components << std::endl;
        old_components = components;
        while(true);
    }
    return 0;
}
