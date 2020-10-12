#include <iostream>

#include "random/rand_generator.h"
#include "graph/grid.h"
#include "graph/graph.h"

int main(){
    RandGenerator::setSeed(44545);
    int n = 50;
    Grid grid(n);

    Graph g = grid.createGraph();

    std::cout << "Graph created!" << std::endl;
    auto components = g.getTotalConnectedComponents();
    float step = 0.05;
    for(float i = 0; i <= 1; i += step){
        std::cout << "Using q=" << i << std::endl;
        auto g_p = Graph::applyBondPercolation(g, i);
        components = g_p.getTotalConnectedComponents();
        std::cout << "Connected Components: " << components << std::endl;
    }
    return 0;
}
