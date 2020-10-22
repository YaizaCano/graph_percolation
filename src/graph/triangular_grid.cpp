#include "triangular_grid.h"

TriangularGrid::TriangularGrid(unsigned int num){
    n = num;
}


std::string TriangularGrid::name() const{
    return "triangular";
}

Graph TriangularGrid::createGraph() const{
    Graph g;
    g.reserve((n*(n-1)/2)+n);

    // add vertices
    int numVertices = n*(n - 1)/2 + n;
    for(auto i = 0; i < numVertices; ++i){
        g.addSite();
    }

    // O(|V|) |V| == n*n
    for(auto i = 0; i < n; ++i){
        for(auto j = 0; j < n - i; ++j){
            auto pos = i * n + j;
            auto posleft = pos - 1;
            auto posdown = pos + n;
            if (posleft != -1 ) g.addBond(posleft, pos);
            if ( !(i == n-1) && !(j == n-i-1) ) g.addBond(pos, posdown);
        }
    }

    return g; // graella
}
