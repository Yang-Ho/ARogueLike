#include "monster.h"
#include "rng.h"

using namespace::std;

extern RNG rng;

// Constructors
Monster::Monster() {
    x = 0;
    y = 0;
    MAX_HEALTH = 10;
    health = MAX_HEALTH;
}

Monster::Monster(int X, int Y, int H) {
    x = X;
    y = Y;
    MAX_HEALTH = H;
    health = MAX_HEALTH;
}

// Getters
int Monster::getX() { return x; }
int Monster::getY() { return y; }
int Monster::getHealth() { return health; }
int Monster::getMaxHealth() { return MAX_HEALTH; }

void Monster::setCoord(int X, int Y) {
    x = X;
    y = Y;
}

void Monster::move() {
    int direction = rng.getRandomInt(0,4);
}
