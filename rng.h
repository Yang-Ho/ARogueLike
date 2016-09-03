#ifndef RNG_H
#define RNG_H 

#include <random>

using namespace::std;

class RNG {
    private:
        int seed;
        minstd_rand0 generator;
    public:
        RNG(int s);
        int getSeed();
        int getRandomInt(int min=0, int max=10);
};

#endif /* RNG_H */
