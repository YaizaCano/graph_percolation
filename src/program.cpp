#include <iostream>

#include "random/rand_generator.h"
#include "graph/graph.h"

int main(){
    Graph g;
    g.addSite();
    g.addSite();
    g.addSite();
    g.addSite();
    g.addBond(0, 1);
    g.addBond(2, 3);
    std::cout << "Graph created!" << std::endl;
    auto components = g.getTotalConnectedComponents();
    std::cout << "Connected Components: " << components << std::endl;
    g = Graph::applySitePercolation(g, 0.8);
    components = g.getTotalConnectedComponents();
    std::cout << "Connected Components with bond percolation: " << components << std::endl;
    return 0;
}
