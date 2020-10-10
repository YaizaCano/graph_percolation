#include <iostream>

#include "random/rand_generator.h"
#include "graph/graph.h"

int main(){
    Graph g;
    g.addSite();
    g.addSite();
    g.addSite();
    g.addBond(0, 1);
    g.addBond(1, 2);
    g.addBond(2, 0);
    std::cout << "Connected Components: " << g.getTotalConnectedComponents() << std::endl; 

    return 0;
}
