#include "geometric.h"

Geometric::Geometric(unsigned int num, unsigned int dim, float r){
    n = num;
    dimension = dim;
    radius = r;
}

std::string Geometric::name() const{
    return "geometric " + std::to_string(radius);
}

float Geometric::calculateDistance(std::vector<float> const& v1, std::vector<float> const& v2){
    auto size = v1.size();
    float distance = 0;
    for(auto i = 0; i < size; ++i){
        auto tmp = v1[i] + v2[i];
        distance += tmp*tmp;
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

    KDTree tree(positions);
    std::cout << "Tree built" << std::endl;
    auto pairs = tree.radiusRangeSearch(radius);
    std::cout << "Pairs: " << pairs.size() << std::endl;
    int counter = 0;
    for(auto i = 0; i < n; ++i){
        for(auto j = i + 1; j < n; ++j){
            auto distance = calculateDistance(positions[i], positions[j]);
            if(distance <= radius){
                g.addBond(i, j);
                counter += 1;
            }

        }
    }

    std::cout << "Bonds: " << counter << std::endl;


    return g; // graella
}
