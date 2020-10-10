#include "rand_generator.h"


/** =================================
 *               PUBLIC
 *  =================================*/

BigInt RandGenerator::seed;

void RandGenerator::setSeed(BigInt s){
    seed = s;
}

float RandGenerator::generateProbability(){
    return (generate() * 1.0) / m; 
}

BigInt RandGenerator::generate() {
    auto r = (seed * a + c) % m;
    seed = r;
    return r;
}

std::vector<BigInt> RandGenerator::generatePermutations(unsigned int size) {
    std::vector<BigInt> sequence(size);
    for(auto & element : sequence){
        element = generate();
    }
    return sequence;
}
