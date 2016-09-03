#ifndef MONSTER_H
#define MONSTER_H 

class Monster {
    private:
        int x, y;
        int health, MAX_HEALTH;
    public:
        Monster();
        Monster(int X, int Y, int H);
        void setCoord(int X, int Y);
        void move();
        int getX();
        int getY();
        int getHealth();
        int getMaxHealth();
};
#endif /* MONSTER_H */
