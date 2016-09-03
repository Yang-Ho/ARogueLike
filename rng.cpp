#include "rng.h"

#include <random>
#include <ctime>

using namespace::std;

RNG::RNG(int s=time(0)) : 
    seed(s), generator (s) {
}

int RNG::getSeed() {return seed;}

int RNG::getRandomInt(int min, int max) {
    return generator() % max + min;
} 
