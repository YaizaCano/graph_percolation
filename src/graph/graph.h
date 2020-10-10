#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>

/**
  * @typedef type definition for the identifier of a vertex in a graph
  * */
typedef unsigned int SiteID;

/**
 * @class Graph
 * @brief The graph class is a graph G=(V, E), it is represented as an
 *        adjacency list. It is an undirected graph
 *
 * */
class Graph{


    public:


    /**
     * @brief calculates the number of connected components of a graph in
     *        a computational time of O(|V| + |E|)
     * @returns the number of connected components
     * */
    unsigned int getTotalConnectedComponents() const;

    /**
     * @brief adds a new vertex to the graph with the smallest ID available,
     *        the id of a site is represented by its position in the array
     * */
    void addSite();

    /**
     * @brief adds an edge between two vertices, as a precondition, the edge must
     *        not exist already.
     * */
    void addBond(SiteID v, SiteID u);

    /**
     * @brief returns the number of vertices in the graph
     * */
    unsigned int totalSites() const;

    /**
     * @brief returns the total of bonds in a specific site.
     * */
    unsigned int totalBonds(SiteID v) const;



    /**
     * @brief generates a graph G' that is the result of applying site percolation
     *        to the given graph, it has a computational time complexity of O(|V| + |E|)
     *        and a space complexity of O(|V|)
     * @param g is the graph to percolate
     * @param q is the value of of the probability of percolation
     * @returns returns a percolated graph
     * */
    static Graph applySitePercolation(Graph const& g, float q);

    /**
     * @brief generates a graph G' that is the result of applying bond percolation
     *        to the given graph, it has a computational time complexity of O(|V| + |E|)
     *        and a space complexity of O(|V|^2)
     * @param g is the graph to percolate
     * @param q is the value of of the probability of percolation
     * @returns returns a percolated graph
     * */
    static Graph applyBondPercolation(Graph const& g, float q);


    private:


    /**
     * @brief Contains the list of nodes with their respective edge connecition
     *        it is the computatational representation of the graph, each vertex
     *        is represented by a numerical ID.
     * */
    std::vector<std::list<SiteID>> nodeList; // ADJACENCY LIST OR MATRIX

};



#endif
