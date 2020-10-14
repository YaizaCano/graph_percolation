#ifndef GRAPH_H
#define GRAPH_H

// DEBUG
#include <iostream>
#include <vector>
#include <stack>

#include "../random/rand_generator.h"

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
     * @brief given a number of vertices reserves the space needed
     * @param n is the number of vertices to reserve
     * */
    void reserve(unsigned int n);

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
     * @param v a vertex connected to the edge
     * @param u is the vertex at the other side of the edge
     * */
    void addBond(SiteID v, SiteID u);

    /**
     * @brief returns the number of vertices in the graph
     * @returns the number of sites in the graph
     * */
    unsigned int totalSites() const;

    /**
     * @brief returns the total of bonds in a specific site.
     * @param v is the site in which to get the bonds
     * @returns the number bonds in a specific site
     * */
    unsigned int totalBonds(SiteID v) const;


    /**
     * @brief given a site and an edge position, it retursn the site that at that position
     * @param v is the site
     * @param pos is the position inside the list of edges
     * @returns the siteID of the given edge
     * */
    SiteID getBondSite(SiteID v, unsigned int pos) const;



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
    std::vector<std::vector<SiteID>> nodeList; // ADJACENCY LIST OR MATRIX?

};



#endif
