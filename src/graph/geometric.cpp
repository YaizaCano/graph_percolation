#include "geometric.h"

/** =================================
 *               PUBLIC
 *  =================================*/

Geometric::Geometric(unsigned int num, unsigned int dim, float r){
    n = num;
    dimension = dim;
    radius = r;
}

float Geometric::calculateDistance(std::vector<float> const& v1, std::vector<float> const& v2){
    auto size = v1.size();
    float distance = 0;
    for(auto i = 0; i < size; ++i){
        distance += v1[i]*v1[i] + v2[i]*v2[i];
    }

    return sqrt(distance);
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
    for(auto i = 0; i < n; ++i){
        g.addSite();
        positions[i] = generatePosition(); // position
    }
    // O(n^2), USE KDTree
    for(auto i = 0; i < n; ++i){
        for(auto j = 0; j < n; ++j){
            auto distance = calculateDistance(positions[i], positions[j]);
            if(distance <= radius)
                g.addBond(i, j);
        }
    }

    return g; // graella
}
