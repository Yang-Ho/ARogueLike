#ifndef LEVEL_H
#define LEVEL_H 

#include "config.h"
#include "player.h"
#include "monster.h"

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace::std;

enum class PlayerAction {
    move,
    attack,
    bump_wall,
    invalid
};

enum LayoutTiles {
    EMPTY,
    WALL,
    PLAYER,
    MONSTER
};

struct MonsterAtLoc{
    private:
        int x, y;
    public:
    explicit MonsterAtLoc(int X, int Y) {x=X; y=Y;}
    inline bool operator()(const Monster* m) { return (m->getX() == x && m->getY() == y);}
};

class Level {
    private:
        int width, height;
        vector< vector<int> > layout;
        Player player;
        vector< Monster* > monsters; 
    public:
        Level() {
            width = 100;
            height = 60;
            player.setCoord(width / 2, height / 2);
        }
        Level(int W, int H) {
            width = W;
            height = H;
            player.setCoord(width / 2, height / 2);
        }
        Level(int W, int H, const vector< vector<int> > &l) {
            width = W;
            height = H;
            layout = l;
            player.setCoord(width / 2, height / 2);
            player.setCoord(width / 2, 9);
            layout[player.getX()][player.getY()] = 2;
        }
        int getWidth() { return width; }
        int getHeight() { return height; }
        int getTile(int x, int y) { return layout[x][y]; }

        //void drawLevel(WINDOW *mapWin);
        void drawLevelIterator1();
        void updateLayout();

        void generateMonsters();

        string playerAction(char input);

        int update(char input, vector<string> &msgs);
};
#endif /* LEVEL_H */
//  [Last modified: 2019 08 24 at 12:06:29 MDT]
