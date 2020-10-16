#include "geometric.h"

Geometric::Geometric(unsigned int num, unsigned int dim, float r){
    n = num;
    dimension = dim;
    radius = r;
}

std::string Geometric::name() const{
    return "geometric " + std::to_string(radius);
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

    for(auto const& p : pairs)g.addBond(p.first, p.second);



    return g; // graella
}
