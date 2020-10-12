#include "geometric.h"

Geometric::Geometric(unsigned int num, unsigned int dim, float r){
    n = num;
    dimension = dim;
    radius = r;
}

float Geometric::calculateDistance(std::vector<int> const& v1, std::vector<int> const& v2){
    auto size = v1.size();
    float distance = 0;
    for(auto i = 0; i < size; ++i){
        distance += v1[i]*v1[i] + v2[i]*v2[i];
    }

    return sqrt(distance);
}


std::vector<int> Geometric::generatePosition() const{
    std::vector<int> pos(dimension);
    for(auto &p : pos){
        p = RandGenerator::generate() % 2000;
    }

    return pos;
}

Graph Geometric::createGraph() const{
    Graph g;
    std::vector<std::vector<int>> positions(n, std::vector<int>(dimension));
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
