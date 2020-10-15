#include "grid.h"

Grid::Grid(unsigned int num){
    n = num;
}


std::string Grid::name() const{
    return "grid2d";
}

Graph Grid::createGraph() const{
    Graph g;
    g.reserve(n * n);

    // add vertices
    for(auto i = 0; i < n * n; ++i){
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

    for(auto i = 1; i < n - 1; ++i) {
        auto pos = n*(n-1)+i;
        g.addBond(pos, pos + 1);
    }

    for(auto i = 1; i < n - 1; ++i) {
        auto pos = n*i;
        g.addBond(pos, pos + n);
    }

    return g; // graella
}
