#include "config.h"
#include "level.h"
#include "rng.h"

#include "libtcod.hpp"
#include <SDL.h>

#include <vector>
#include <string>
#include <iostream>
#include <ctime>

using namespace::std;

RNG rng (time(0));

int main() {

    // Tcod Initialization
	bool fullscreen=false;

	TCOD_renderer_t renderer=TCOD_RENDERER_SDL2;
	TCOD_key_t key = {TCODK_NONE,0};

    int gameState = 0;

    vector< vector<int> > levelLayout(100, vector<int>(60, 0));
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 60; j++) {
            if (i == 0 || j == 0 || i == 99 || j == 59)
                levelLayout[i][j] = 1;
        }
    }
    //Level currLevel(100, 60, levelLayout);
    //currLevel.generateMonsters();
    

    TCODConsole::initRoot(80,50,"libtcod C++ tutorial",false, renderer);
    while ( !TCODConsole::isWindowClosed() ) {
		// did the user hit a key ?
        TCODConsole::root->clear();
        TCODConsole::root->putChar(40,25,'@');
        TCODConsole::flush();
		TCODSystem::checkForEvent((TCOD_event_t)(TCOD_EVENT_KEY_PRESS),&key,NULL);
        if ( key.c == 'q' ) {
            TCOD_quit();
        }
    }
    return 0;
}

//  [Last modified: 2019 08 24 at 12:05:18 MDT]
