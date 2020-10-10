#include "rand_generator.h"


/** =================================
 *               PUBLIC
 *  =================================*/



BigInt RandGenerator::generate(BigInt seed) {
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


