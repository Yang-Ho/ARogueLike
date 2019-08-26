#ifndef MONSTER_H
#define MONSTER_H 

class Monster {
    private:
        int x, y;
        int health, MAX_HEALTH;
    public:
        Monster();
        Monster(int X, int Y, int H);

        int getX() const;
        int getY() const;
        int getHealth() const;
        int getMaxHealth() const;
        
        void setCoord(int X, int Y);
        void dealtDamage(int dmg);

        void move();
};
#endif /* MONSTER_H */
//  [Last modified: 2019 08 15 at 15:49:27 MDT]
