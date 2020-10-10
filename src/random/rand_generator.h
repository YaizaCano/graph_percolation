#ifndef RAND_GENERATOR_H
#define RAND_GENERATOR_H


#include <vector>

/**
  * @typedef type definition for a really big unsigned int
  * */
typedef long long unsigned int BigInt;


/**
 * @class RandGenerator
 * @brief Random number generator that
 *        generates a sequence of random numbers
 *        based on a specific seed. The numbers generated
 *        here are based on the Linear Congruential Method
 *        D. H . Lehmer (Cambridge, Mass.: Harvard University Press, 1951[141-146])
 *
 * */
class RandGenerator {

public:

    /**
     * @brief setter for the initial number
     * @param s is the starting number
     * */
    static void setSeed(BigInt s);

    /**
     * @brief generates a probability between 0 and 1
     * @returns a number between 0 and 1
     * */
    static float generateProbability();

    /**
     * @brief generate a random number based on a seed
     * @param seed is the starting number
     * @returns the next number in the sequence
     * */
    static BigInt generate();

    /**
     *  @brief generate a random sequence of numbers
     *  @param seed is the starting number in the sequence
     *  @param size is the size of the sequence
     *  @returns the sequence of integers
     * */
    static std::vector<BigInt> generatePermutations(unsigned int size);

private:

    /**
     * @brief the modulus of the formula
     * */
    static BigInt seed;

    /**
     * @brief the modulus of the formula
     * */
    static const BigInt m = 2147483647;
    /**
     * @brief the multiplier
     * */
    static const BigInt a = 1664525;

    /**
     * @brief the increment
     * */
    static const BigInt c = 1013904223;


};


#endif //A_RAND_GENERATOR_H
