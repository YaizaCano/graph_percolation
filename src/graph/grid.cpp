#include "grid.h"

Grid::Grid(unsigned int num){
    n = num;
}


Graph Grid::createGraph() const{
    Graph g;
    // add vertices
    for(auto i = 0; i < n*n; ++i){
        g.addSite();
    }

    // O(|V|) |V| == n*n
    for(auto i = 0; i < n - 1; ++i){
        for(auto j = 0; j < n - 1; ++j){
            auto pos = i * n + j;
            g.addBond(pos, pos + 1);
            g.addBond(pos, pos + n);
        }
    }

    return g; // graella
}
