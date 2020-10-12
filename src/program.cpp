#include <iostream>

#include "random/rand_generator.h"
#include "graph/grid.h"
#include "graph/geometric.h"
#include "graph/graph.h"

int main(){
    RandGenerator::setSeed(44545);
    int n = 50;
    int dim = 3;
    float radius = 2000;
    Geometric grid(n, dim, radius);

    Graph g = grid.createGraph();

    std::cout << "Graph created!" << std::endl;
    auto components = g.getTotalConnectedComponents();
    float step = 0.05;
    for(float i = 0; i <= 1; i += step){
        std::cout << "Using q=" << i << std::endl;
        auto g_p = Graph::applySitePercolation(g, i);
        components = g_p.getTotalConnectedComponents();
        std::cout << "Connected Components: " << components << std::endl;
    }
    return 0;
}
