#include "config.h"
#include "level.h"
#include "rng.h"

#ifdef LIBTCOD

#else

#include <curses.h>

#endif

#include <vector>
#include <string>
#include <iostream>
#include <ctime>

using namespace::std;

void updateMessages(WINDOW *msgWin, const vector<string> &msgs);

RNG rng (time(0));

int main() {

    int gameState = 0;

    WINDOW * mapWindow;
    WINDOW * messageWindow;
    WINDOW * infoWindow;

    vector< vector<int> > levelLayout(100, vector<int>(60, 0));
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 60; j++) {
            if (i == 0 || j == 0 || i == 99 || j == 59)
                levelLayout[i][j] = 1;
        }
    }
    Level currLevel(100, 60, levelLayout);
    currLevel.generateMonsters();

    getch();
    initscr();
    start_color();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    int input;

    mapWindow = newwin(view::map.height, view::map.width, 0, 0);
    messageWindow = newwin(view::message.height, view::message.width, view::map.height, 0);
    infoWindow = newwin(view::info.height, view::info.width, 0, view::map.width);
    
    box(infoWindow,0,0);

    refresh();

    vector<string> messages;

    currLevel.drawLevel(mapWindow);
    updateMessages(messageWindow, messages);
    wrefresh(infoWindow);

    while(gameState != -1) {
        // Get input
        input = getch();
        if (input == 'q') {
            gameState = -1;
            messages.push_back("Quitting game");
        } else {
            // Move player
            gameState = currLevel.update(input, messages);
        }

        // Update messages
        updateMessages(messageWindow, messages);

        // Update map
        currLevel.drawLevel(mapWindow);
    }
    getch();
    delwin(mapWindow); 
    delwin(messageWindow); 
    delwin(infoWindow); 
    endwin();
    return 0;
}

void updateMessages(WINDOW *msgWin, const vector<string> &msgs) {
    int size = msgs.size();
    for (int i = 0; i < 4; i++) {
        int index;
        if (i < size)
            index = size - 1 - i;
        else
            break;
        wmove(msgWin, 3 - i, 0);
        wclrtoeol(msgWin);
        mvwprintw(msgWin, 3 - i, 0, "Character action: %s", msgs[index].c_str());
    }
    wrefresh(msgWin);
}
//  [Last modified: 2019 08 24 at 09:32:55 MDT]
