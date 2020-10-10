#include "graph.h"



/** =================================
 *               PUBLIC
 *  =================================*/



unsigned int Graph::getTotalConnectedComponents() const{

    return 1;
}


void Graph::addSite(){
    nodeList.push_back(std::list<SiteID>);
}

void Graph::addBond(SiteID v, SiteID u){
    nodeList[v].push_back(v);
    nodeList[u].push_back(u);
}


unsigned int Graph::totalSites() const{
    return nodeList.size(0);
}

unsigned int Graph::totalBonds(SiteID v) const{
    return nodeList[v].size();
}

Graph Graph::applySitePercolation(Graph const& g, float q){
    // represents if a vertex has been removed already
    std::vector<bool> removedSites(false);
    // the new percolation graph is empty
    Graph percolatedGraph;

    auto nVertices = g.totalSites();
    for(int i = 0; i < nVertices; ++i){
        percolatedGraph.addSite();
        auto nBonds = g.totalBonds(i);
        for(int j = 0; j < nBonds; ++j){

        }
    }

    return percolatedGraph;
}




/** =================================
 *               PRIVATE
 *  =================================*/
