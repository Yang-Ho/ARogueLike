#ifndef LEVEL_H
#define LEVEL_H 

#include "config.h"
#include "player.h"
#include "monster.h"

#include <curses.h>
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

struct MonsterAtLoc{
    private:
        int x, y;
    public:
    explicit MonsterAtLoc(int X, int Y) {x=X; y=Y;}
    inline bool operator()(const Monster& m) { return (m.getX() == x && m.getY() == y);}
};

class Level {
    private:
        int width, height;
        vector< vector<int> > layout;
        Player player;
        vector< Monster > monsters; 
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

        void generateMonsters();

        string playerAction(char input);

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
                    else if (layout[xCoord][yCoord] == 3)
                        mvwaddch(mapWin, y, x, 'M');
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

void Level::generateMonsters() {
    monsters.push_back(Monster(30,30,10));
    for (vector< Monster >::iterator it = monsters.begin(); it != monsters.end(); ++it) {
        layout[it->getX()][it->getY()] = 3;
    }
}

string Level::playerAction(char input) {
    string message;
    layout[player.getX()][player.getY()] = 0;
    char direction = 0;
    PlayerAction action;
    int new_loc;
    switch(input) {
        case 'k':
            new_loc = layout[player.getX()][player.getY() - 1];
            if (new_loc == 0) {
                action = PlayerAction::move;
            } else if (new_loc == 1) {
                action = PlayerAction::bump_wall;
            } else if (new_loc == 3) {
                action = PlayerAction::attack;
            }
            break;
        case 'j':
            new_loc = layout[player.getX()][player.getY() + 1];
            if (new_loc == 0) {
                action = PlayerAction::move;
            } else if (new_loc == 1) {
                action = PlayerAction::bump_wall;
            } else if (new_loc == 3) {
                action = PlayerAction::attack;
            }
            break;
        case 'h':
            new_loc = layout[player.getX() - 1][player.getY()];
            if (new_loc == 0) {
                action = PlayerAction::move;
            } else if (new_loc == 1) {
                action = PlayerAction::bump_wall;
            } else if (new_loc == 3) {
                action = PlayerAction::attack;
            }
            break;
        case 'l': 
            new_loc = layout[player.getX() + 1][player.getY()];
            if (new_loc == 0) {
                action = PlayerAction::move;
            } else if (new_loc == 1) {
                action = PlayerAction::bump_wall;
            } else if (new_loc == 3) {
                action = PlayerAction::attack;
            }
            break;
        case 'y': 
            new_loc = layout[player.getX() - 1][player.getY() - 1];
            if (new_loc == 0) {
                action = PlayerAction::move;
            } else if (new_loc == 1) {
                action = PlayerAction::bump_wall;
            } else if (new_loc == 3) {
                action = PlayerAction::attack;
            }
            break;
        case 'u': 
            new_loc = layout[player.getX() + 1][player.getY() - 1];
            if (new_loc == 0) {
                action = PlayerAction::move;
            } else if (new_loc == 1) {
                action = PlayerAction::bump_wall;
            } else if (new_loc == 3) {
                action = PlayerAction::attack;
            }
            break;
        case 'b': 
            new_loc = layout[player.getX() - 1][player.getY() + 1];
            if (new_loc == 0) {
                action = PlayerAction::move;
            } else if (new_loc == 1) {
                action = PlayerAction::bump_wall;
            } else if (new_loc == 3) {
                action = PlayerAction::attack;
            }
            break;
        case 'n': 
            new_loc = layout[player.getX() + 1][player.getY() + 1];
            if (new_loc == 0) {
                action = PlayerAction::move;
            } else if (new_loc == 1) {
                action = PlayerAction::bump_wall;
            } else if (new_loc == 3) {
                action = PlayerAction::attack;
            }
            break;
        default:
            action = PlayerAction::invalid;
            break;
    }

    if (action == PlayerAction::move) {
        switch(input) {
            case 'k':
                player.moveUp();
                message = "Moved up!";
                break;
            case 'j':
                player.moveDown();
                message = "Moved down!";
                break;
            case 'h':
                player.moveLeft();
                message = "Moved left!";
                break;
            case 'l': 
                player.moveRight();
                message = "Moved right!";
                break;
            case 'y': 
                player.moveLeft();
                player.moveUp();
                message = "Moved up left!";
                break;
            case 'u': 
                player.moveRight();
                player.moveUp();
                message = "Moved up right!";
                break;
            case 'b': 
                player.moveLeft();
                player.moveDown();
                message = "Moved down left!";
                break;
            case 'n': 
                player.moveRight();
                player.moveDown();
                message = "Moved down right!";
                break;
            default:
                message = "Unknown command";
                break;
        }
    } else if (action == PlayerAction::bump_wall) {
        message = "Bumped into wall!";
    } else if (action == PlayerAction::attack) {
        vector< Monster >::iterator target;
        switch(input) {
            case 'k':
                target = find_if(monsters.begin(), monsters.end(), MonsterAtLoc(player.getX(), player.getY() - 1));
                if (target != monsters.end()) {
                    message = "Attacked monster!";
                }
                break;
            case 'j':
                target = find_if(monsters.begin(), monsters.end(), MonsterAtLoc(player.getX(), player.getY() + 1));
                if (target != monsters.end()) {
                    message = "Attacked monster!";
                }
                break;
            case 'h':
                target = find_if(monsters.begin(), monsters.end(), MonsterAtLoc(player.getX() - 1, player.getY()));
                if (target != monsters.end()) {
                    message = "Attacked monster!";
                }
                break;
            case 'l': 
                target = find_if(monsters.begin(), monsters.end(), MonsterAtLoc(player.getX() + 1, player.getY()));
                if (target != monsters.end()) {
                    message = "Attacked monster!";
                }
                break;
            case 'y': 
                target = find_if(monsters.begin(), monsters.end(), MonsterAtLoc(player.getX() - 1, player.getY() - 1));
                if (target != monsters.end()) {
                    message = "Attacked monster!";
                }
                break;
            case 'u': 
                target = find_if(monsters.begin(), monsters.end(), MonsterAtLoc(player.getX() + 1, player.getY() - 1));
                if (target != monsters.end()) {
                    message = "Attacked monster!";
                }
                break;
            case 'b': 
                target = find_if(monsters.begin(), monsters.end(), MonsterAtLoc(player.getX() - 1, player.getY() + 1));
                if (target != monsters.end()) {
                    message = "Attacked monster!";
                }
                break;
            case 'n': 
                target = find_if(monsters.begin(), monsters.end(), MonsterAtLoc(player.getX() + 1, player.getY() + 1));
                if (target != monsters.end()) {
                    message = "Attacked monster!";
                }
                break;
            default:
                message = "Unknown command";
                break;
        }
    }

    layout[player.getX()][player.getY()] = 2;
    return message;
}

int Level::update(char input, vector<string> &msgs) {
    int gameState = 0;
    msgs.push_back(playerAction(input));
    if (player.getHealth() <= 0) {
        gameState = -1;
        msgs.push_back("Player died!");
    }
    return gameState;
}
#endif /* LEVEL_H */
