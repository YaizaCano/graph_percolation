#include "triangular_grid.h"

TriangularGrid::TriangularGrid(unsigned int num){
    n = num;
}


std::string TriangularGrid::name() const{
    return "triangular";
}

Graph TriangularGrid::createGraph() const{
    Graph g;
    g.reserve((n*(n-1)/2)+n);
    //std::cout << "Reserva d'espai feta" << std::endl;
    // add vertices
    int numVertices = n*(n - 1)/2 + n;
    for(auto i = 0; i < numVertices; ++i){
        g.addSite();
    }
    //std::cout << "afegits els vertex" << std::endl;

    int rounds = 0;
    int countdown = n;
    for(int i = 0; i < numVertices; ++i){
      --countdown;
      int pos = i;
      int posright = i + 1;
      int posdown = i + n-rounds;
      //std::cout << "pos: " << pos << " posr: " << posright << std::endl << std::endl;
      if (countdown == 0) {
        ++rounds;
        countdown = n - rounds;
        //std::cout << "Coundown: " << countdown << " rounds: " << rounds << std::endl;
      }
      else{
        g.addBond(pos,posright);
        g.addBond(pos,posdown);
        //std::cout << "aresta a la dreta: " << pos << " " << posright << std::endl;
        //std::cout << "aresta asota: " << pos << " " << posdown << std::endl;
      }
    }

    return g; // graella
}
