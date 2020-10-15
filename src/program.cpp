#include <iostream>

#include "random/rand_generator.h"
#include "graph/grid.h"
#include "graph/geometric.h"
#include "graph/graph.h"
#include "data/csv_file.h"

void usage(){
    std::cerr << "Usage: ./program n seed outputDir" << std::endl << std::endl;
    std::cerr << "    n: the total number of vertices" << std::endl;
    std::cerr << "    seed: the random seed for the data generation" << std::endl;
    std::cerr << "    dim: number of dimensions for geometric graphs" << std::endl;
    std::cerr << "    stepSize: the step size of probability q" << std::endl;
    std::cerr << "    outputDir: the directory where the experiment must be placed, the directory must exist" << std::endl << std::endl;
}


// el rand generator ha de ser directament proporcional al radi
// en el cas de Geometric ja que si el espai de posicions es molt gran
// el radi a de ser mes gran per compensar.

int main(int argc, char* argv[]){

    // parameter check
    if(argc != 6){
        usage();
        return 1;
    }

    // parameter definition
    int n = std::stoi(argv[1]);
    int seed = std::stoi(argv[2]);
    int dim = std::stoi(argv[3]);
    float step = std::stof(argv[4]);
    std::string outputPath = argv[5];
    if(outputPath[outputPath.size() - 1] != '/')outputPath += '/';
    RandGenerator::setSeed(seed);
    // radius definition
    float radius = 0.05;
    std::list<GraphGenerator*> generators;

    // define generators
    Grid grid2d(sqrt(n));
    generators.push_back(&grid2d);
    while(radius < 1){
        Geometric* generator = new Geometric(n, dim, radius);
        generators.push_back(generator);
        radius += 0.05;
    }
    std::cout << "Intiailizing bond percolation" << std::endl;
    for(auto const& gen : generators){
        std::cout << "=================================" << std::endl;
        std::cout << "Generator: " << gen->name() << std::endl;
        std::cout << "=================================" << std::endl;
        Graph g = gen->createGraph();
        std::cout << "Graph created!" << std::endl;
        long int old_components = 0;

        for(float i = 0; i <= 1.05; i += step){
            std::cout << "Using q=" << i << std::endl;
            auto g_p = Graph::applyBondPercolation(g, i);

            auto components = g_p.getTotalConnectedComponents();
            std::cout << "Connected Components: " << components << std::endl;
            std::cout << "Differece: " << components - old_components << std::endl;
            old_components = components;

        }
    }








    return 0;
}
