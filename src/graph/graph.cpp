#include "graph.h"



/** =================================
 *               PUBLIC
 *  =================================*/

void Graph::reserve(unsigned int n){
    nodeList.reserve(n);
}

unsigned int Graph::getTotalConnectedComponents() const{
    std::vector<bool> visited(nodeList.size(), false);
    auto nComponents = 0;
    // the idea behind this algorithm is that every time we iterate through
    // the loop we are at looking at a different vertex, if we have already seen
    // it it means it is already in a component so we can ignore it.
    for(int i = 0; i < nodeList.size(); ++i){
        // visit all the component starting from the selected vertex
        if(!visited[i]){
            // we do a bfs for each connected component
            std::stack<SiteID> elements;
            nComponents++;
            elements.push(i);
            while(!elements.empty()){
                auto current = elements.top();
                elements.pop();
                if(!visited[current]){
                    visited[current] = true;
                    auto nBonds = totalBonds(current);
                    for(int j = 0; j < nBonds; ++j){
                        auto site = getBondSite(current, j);
                        elements.push(site);
                    }
                }
            }
        }
    }

    return nComponents;
}


void Graph::addSite(){
    nodeList.push_back(std::vector<SiteID>());

}

void Graph::addBond(SiteID v, SiteID u){
    nodeList[v].push_back(u);
    nodeList[u].push_back(v);
}


unsigned int Graph::totalSites() const{
    return nodeList.size();
}

unsigned int Graph::totalBonds(SiteID v) const{
    return nodeList[v].size();
}

SiteID Graph::getBondSite(SiteID v, unsigned int pos)const{
    return nodeList[v][pos];
}

Graph Graph::applySitePercolation(Graph const& g, float q){
    // the new percolation graph is empty
    Graph percolatedGraph;
    auto nVertices = g.totalSites();
    percolatedGraph.reserve(nVertices);
    // represents if a vertex has been removed already
    std::vector<bool> removedSites(nVertices, false);
    // represents how many vertices have been removed at that index
    std::vector<int> removedCount(nVertices + 1, 0);
    // before adding any edge, we must add all vertices O(|V|)
    for(int i = 0; i < nVertices; ++i){
        auto p = RandGenerator::generateProbability();
        removedSites[i] =  p < q;
        // we need to keep count on how many indices we are shifting due to the
        // vertex deletion
        if(!removedSites[i]){
            percolatedGraph.addSite();
        }
        else{
            removedCount[i + 1] = 1;
        }
        removedCount[i + 1] += removedCount[i];
    }
    // for each site in the graph we add it
    // to the new graph only if the probability of
    // percolation permits it
    for(int i = 0; i < nVertices; ++i){

        // if the site has not been deleted, then
        // we add the corresponding edges.
        if(!removedSites[i]){

            auto nBonds = g.totalBonds(i);
            for(int j = 0; j < nBonds; ++j){
                auto site = g.getBondSite(i, j);
                // we only add the edge if the corresponding vertex has not
                // been deleted before
                if(!removedSites[site] && i < site)
                    percolatedGraph.addBond(i - removedCount[i + 1], site - removedCount[site + 1]);
            }
        }

    }

    return percolatedGraph;
}

Graph Graph::applyBondPercolation(Graph const& g, float q){

    // the new percolation graph is empty
    Graph percolatedGraph;
    auto nVertices = g.totalSites();
    percolatedGraph.reserve(nVertices);

    // before adding any edge, we must add all vertices O(|V|)
    for(int i = 0; i < nVertices; ++i){
        // always add a vertex
        percolatedGraph.addSite();
    }

    // in this algorithm we add all vertices
    for(int i = 0; i < nVertices; ++i){

        auto nBonds = g.totalBonds(i);
        for(int j = 0; j < nBonds; ++j){
            auto site = g.getBondSite(i, j);
            // now we can find two cases, since we will always visit the same edge
            // twice, if it is the first time we visit an edge, then we must calculate
            // the probability
            //
            // if it is the second visit => the probability has already been calculated

            if(i < site){
                auto p = RandGenerator::generateProbability();
                bool removedBond = p < q;
                if(!removedBond)percolatedGraph.addBond(i, site);
            }

        }
    }


    return percolatedGraph;
}



/** =================================
 *               PRIVATE
 *  =================================*/
