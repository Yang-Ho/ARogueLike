#include "level.h"
#include "utilities.h"

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace::std;

auto is_dead = [](Monster* m) {
    bool return_value = false;
    if (m->getHealth() == 0.0) {
        return_value = true;
    }
    return return_value;
};

/*
void Level::drawLevel(WINDOW *mapWin) {
    for (int y = 0; y < view::map.height; y++) {
        int yCoord = y + player.getY() - view::map.height / 2;
        for (int x = 0; x < view::map.width; x++) {
            int xCoord = x + player.getX() -view::map.width / 2;
            if (yCoord >= 0 && yCoord < height) {
                if (xCoord >= 0 && xCoord < width) {
                    if (layout[xCoord][yCoord] == EMPTY)
                        mvwaddch(mapWin, y, x, '.');
                    else if (layout[xCoord][yCoord] == WALL)
                        mvwaddch(mapWin, y, x, '#');
                    else if (layout[xCoord][yCoord] == PLAYER)
                        mvwaddch(mapWin, y, x, '@');
                    else if (layout[xCoord][yCoord] == MONSTER)
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
*/

void Level::drawLevelIterator1() {
    for (auto it = layout.begin(); it != layout.end(); ++it) {
        for (auto jt = it->begin(); jt != it->end(); ++jt) {
            cout<<*jt;
        }
        cout<<'\n';
    }
}

void Level::generateMonsters() {
    monsters.push_back(new Monster(30,30,10));
    for (auto it = monsters.begin(); it != monsters.end(); ++it) {
        layout[(*it)->getX()][(*it)->getY()] = MONSTER;
    }
}

string Level::playerAction(char input) {
    string message;
    layout[player.getX()][player.getY()] = EMPTY;
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
        vector< Monster* >::iterator target;
        switch(input) {
            case 'k':
                target = find_if(monsters.begin(), monsters.end(), MonsterAtLoc(player.getX(), player.getY() - 1));
                break;
            case 'j':
                target = find_if(monsters.begin(), monsters.end(), MonsterAtLoc(player.getX(), player.getY() + 1));
                break;
            case 'h':
                target = find_if(monsters.begin(), monsters.end(), MonsterAtLoc(player.getX() - 1, player.getY()));
                break;
            case 'l': 
                target = find_if(monsters.begin(), monsters.end(), MonsterAtLoc(player.getX() + 1, player.getY()));
                break;
            case 'y': 
                target = find_if(monsters.begin(), monsters.end(), MonsterAtLoc(player.getX() - 1, player.getY() - 1));
                break;
            case 'u': 
                target = find_if(monsters.begin(), monsters.end(), MonsterAtLoc(player.getX() + 1, player.getY() - 1));
                break;
            case 'b': 
                target = find_if(monsters.begin(), monsters.end(), MonsterAtLoc(player.getX() - 1, player.getY() + 1));
                break;
            case 'n': 
                target = find_if(monsters.begin(), monsters.end(), MonsterAtLoc(player.getX() + 1, player.getY() + 1));
                break;
            default:
                target = monsters.end();
                message = "Unknown command";
                break;
        }
        if (target != monsters.end()) {
            message = "Attacked monster!";
            (*target)->dealtDamage(player.damageRoll());
        }
    }

    layout[player.getX()][player.getY()] = PLAYER;
    return message;
}

int Level::update(char input, vector<string> &msgs) {
    int gameState = 0;
    msgs.push_back(playerAction(input));
    if (player.getHealth() <= 0) {
        gameState = -1;
        msgs.push_back("Player died!");
    }
    auto dead_monsters_it = remove_if(monsters.begin(), monsters.end(), is_dead);
    for (auto it = dead_monsters_it; it != monsters.end(); ++it) {
        layout[(*it)->getX()][(*it)->getY()] = EMPTY;
        delete (*it);
    }
    monsters.erase(dead_monsters_it, monsters.end());
    return gameState;
}
//  [Last modified: 2019 08 24 at 12:03:37 MDT]
