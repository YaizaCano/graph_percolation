#include <iostream>

#include "random/rand_generator.h"
#include "graph/graph.h"

int main(){
    RandGenerator::setSeed(432432);
    Graph g;
    g.addSite();
    g.addSite();
    g.addSite();
    g.addSite();
    g.addBond(0, 1);
    g.addBond(2, 3);
    std::cout << "Graph created!" << std::endl;
    auto components = g.getTotalConnectedComponents();
    for(float i = 1; i > 0; i -=0.05){
        std::cout << "Using q=" << i << std::endl;
        auto g_p = Graph::applyBondPercolation(g, i);
        components = g_p.getTotalConnectedComponents();
        std::cout << "Connected Components: " << components << std::endl;
    }
    return 0;
}
