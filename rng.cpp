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
//  [Last modified: 2019 08 15 at 15:19:38 MDT]
