#include "geometric.h"

Geometric::Geometric(unsigned int num, unsigned int dim, float r){
    n = num;
    dimension = dim;
    radius = r;
}

std::string Geometric::name() const{
    return "geometric_" + std::to_string(radius);
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


BondPairs Geometric::addPairs(int begin, int end, std::vector<std::vector<float>> const& positions) const{

    BondPairs pairs;
    for(int i = begin; i < end; ++i){
        for(int j = i + 1; j < positions.size(); ++j){
            if(i < j && Hyperrectangle::calculateDistance(positions[i], positions[j]) < radius)
                pairs.push_back({i, j});
        }
    }

    return pairs;
}


void Geometric::concurrentRadiusRange(Graph& g, std::vector<std::vector<float>> const& positions) const{
    unsigned int nThreads = 24;

    std::vector<std::future<BondPairs>> threads(nThreads);
    int stride = positions.size() / nThreads;
    for(auto i = 0; i < nThreads; ++i){

        int begin =  stride * i;
        int end = begin + stride;
        threads[i] = std::async(&Geometric::addPairs, this, begin, end, positions);
    }
    auto totalBonds = 0;
    // wait for threads to finish
    for(auto& t : threads){
        auto pairs = t.get();
        for(auto const& p : pairs){
            totalBonds++;
            g.addBond(p.first, p.second);
        }
    }
    std::cout << "Total bonds: " << totalBonds << std::endl;



}
