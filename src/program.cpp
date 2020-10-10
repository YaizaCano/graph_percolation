#include <iostream>

#include "random/rand_generator.h"

int main(){
    for(int i = 0; i < 100; ++i){
        std::cout << RandGenerator::generateProbability() << std::endl; 
    }

    return 0;
}
