#ifndef LEVEL_H
#define LEVEL_H 

#include "config.h"
#include "player.h"

#include <curses.h>
#include <vector>
#include <iostream>
#include <string>

using namespace::std;

class Level {
    private:
        int width, height;
        vector< vector<int> > layout;
        Player player;
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
        void drawLevel(WINDOW *mapWin);
        void drawLevelIterator1();
        void updateLayout();
        string movePlayer(char input);
        int update(char input, vector<string> &msgs);
};

void Level::drawLevel(WINDOW *mapWin) {
    for (int y = 0; y < view::map.height; y++) {
        int yCoord = y + player.getY() - view::map.height / 2;
        for (int x = 0; x < view::map.width; x++) {
            int xCoord = x + player.getX() -view::map.width / 2;
            if (yCoord >= 0 && yCoord < height) {
                if (xCoord >= 0 && xCoord < width) {
                    if (layout[xCoord][yCoord] == 0)
                        mvwaddch(mapWin, y, x, '.');
                    else if (layout[xCoord][yCoord] == 1)
                        mvwaddch(mapWin, y, x, '#');
                    else if (layout[xCoord][yCoord] == 2)
                        mvwaddch(mapWin, y, x, '@');
                } else {
                    mvwaddch(mapWin, y, x, ' ');
                }
            } else {
                mvwaddch(mapWin, y, x, ' ');
            }
        }
    }
    wrefresh(mapWin);
}

void Level::drawLevelIterator1() {
    for (vector< vector<int> >::iterator it = layout.begin(); it != layout.end(); ++it) {
        for (vector<int>::iterator jt = it->begin(); jt != it->end(); ++jt) {
            cout<<*jt;
        }
        cout<<'\n';
    }
}

string Level::movePlayer(char input) {
    string message;
    layout[player.getX()][player.getY()] = 0;
    switch(input) {
        case 'w':
            if (layout[player.getX()][player.getY() - 1] == 0) {
                player.moveUp();
                message = "Moved up!";
            } else {
                message = "Bumped into wall!";
                player.dealDamage(1);
            }
            break;
        case 's':
            if (layout[player.getX()][player.getY() + 1] == 0) {
                player.moveDown();
                message = "Moved down!";
            } else {
                message = "Bumped into wall!";
            }
            break;
        case 'a':
            if (layout[player.getX() - 1][player.getY()] == 0) {
                player.moveLeft();
                message = "Moved left!";
            } else {
                message = "Bumped into wall!";
            }
            break;
        case 'd':
            if (layout[player.getX() + 1][player.getY()] == 0) {
                player.moveRight();
                message = "Moved right!";
            } else {
                message = "Bumped into wall!";
            }
            break;
    }
    layout[player.getX()][player.getY()] = 2;
    return message;
}

int Level::update(char input, vector<string> &msgs) {
    int gameState = 0;
    msgs.push_back(movePlayer(input));
    if (player.getHealth() <= 0) {
        gameState = -1;
        msgs.push_back("Player died!");
    }
    return gameState;
}
#endif /* LEVEL_H */
