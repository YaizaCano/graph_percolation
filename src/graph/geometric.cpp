#include "geometric.h"

/** =================================
 *               PUBLIC
 *  =================================*/

Geometric::Geometric(unsigned int num, unsigned int dim, float r){
    n = num;
    dimension = dim;
    radius = r;
}




std::vector<float> Geometric::generatePosition() const{
    std::vector<float> pos(dimension);
    for(auto &p : pos){
        p = RandGenerator::generateProbability();
    }

    return pos;
}

Graph Geometric::createGraph() const{
    Graph g;
    std::vector<std::vector<float>> positions(n, std::vector<float>(dimension));
    // add vertices
    // Add initial position
    positions[0] = generatePosition();
    KDTree root(positions[0], 0);
    g.addSite();
    // add other positions with time O(nlogn)
    for(auto i = 1; i < n; ++i){
        g.addSite();
        positions[i] = generatePosition(); // position
        root.add(positions[i], i);
    }


    for(auto i = 0; i < n; ++i){
        // O(logn)
        auto pairs = root.radiusRangeSearch(positions[i], radius);
        // O(|pairs|) <= O(n)
        for(auto const& id : pairs){
            g.addBond(i, id);
        }

    }

    return g; // graella
}
