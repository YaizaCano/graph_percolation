#include "rand_generator.h"


/** =================================
 *               PUBLIC
 *  =================================*/

void RandGenerator::setSeed(BigInt s){
    seed = s;
}

float RandGenerator::generateProbability(){
    return (generateInteger() * 1.0) / m; 
}

BigInt RandGenerator::generateInteger(BigInt seed) {
    return (seed * a + c) % m;
}

std::vector<BigInt> RandGenerator::generatePermutations(BigInt seed, unsigned int size) {
    std::vector<BigInt> sequence(size);
    for(auto & element : sequence){
        element = generate(seed);
        seed = element;
    }
    return sequence;
}
