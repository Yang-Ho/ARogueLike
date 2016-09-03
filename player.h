#ifndef PLAYER_H_
#define PLAYER_H_

class Player {
    private:
        int x, y;
        int health, MAX_HEALTH;
    public:
        Player() { 
            x = 0;
            y = 0;
            MAX_HEALTH = 10;
            health = MAX_HEALTH;
        }
        Player(int X, int Y) {
            x = X;
            y = Y;
            MAX_HEALTH = 10;
            health = MAX_HEALTH;
        }
        void setCoord(int X, int Y) {
            x = X;
            y = Y;
        }
        void moveUp() {
            y--;
        }
        void moveDown() {
            y++;
        }
        void moveLeft() {
            x--;
        }
        void moveRight() {
            x++;
        }
        void dealDamage(int d) {
            health -= d;
        }
        int getX() { return x; }
        int getY() { return y; }
        int getHealth() { return health; }
        int getMaxHealth() { return MAX_HEALTH; }
};
#endif
