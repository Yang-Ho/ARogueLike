#include <curses.h>
#include <vector>
#include <string>

using namespace::std;

int screenWidth = 80;
int screenHeight = 24;

int main() {
    int gameover = 0;

    WINDOW * mapWindow;
    WINDOW * messageWindow;
    WINDOW * infoWindow;

    initscr();
    start_color();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    int input;
    int playerX, playerY;

    int mapWidth, mapHeight;
    int messageWidth, messageHeight;
    int infoWidth, infoHeight;

    mapWidth = 60;
    mapHeight = 20;
    messageWidth = 60;
    messageHeight = 4;
    infoWidth = 20;
    infoHeight = 24;

    mapWindow = newwin(mapHeight, mapWidth, 0, 0);
    messageWindow = newwin(messageHeight, messageWidth, mapHeight, 0);
    infoWindow = newwin(infoHeight, infoWidth, 0, mapWidth);

    playerX = mapWidth / 2;
    playerY = mapHeight / 2;
    
    box(mapWindow,0,0);
    wborder(mapWindow, '*','*','*','*','*','*','*','*');
    mvwaddch(mapWindow, playerY, playerX, '@');

    box(messageWindow,0,0);
    wborder(messageWindow, '=','=','=','=','=','=','=','=');

    box(infoWindow,0,0);
    wborder(infoWindow, '+','+','+','+','+','+','+','+');
    refresh();
    wrefresh(mapWindow);
    wrefresh(messageWindow);
    wrefresh(infoWindow);

    move(playerY, playerX);

    vector<string> messages;

    while(gameover == 0) {
        // Get input
        input = getch();
        if (input == 'q') {
            gameover = 1;
        }

        // Move player
        wborder(mapWindow, '*','*','*','*','*','*','*','*');
        mvwaddch(mapWindow, playerY, playerX, '.');
        switch(input) {
            case 'w':
                playerY--;
                messages.push_back("Moved up!");
                break;
            case 's':
                playerY++;
                messages.push_back("Moved down!");
                break;
            case 'a':
                playerX--;
                messages.push_back("Moved left!");
                break;
            case 'd':
                playerX++;
                messages.push_back("Moved right!");
                break;
        }
        if (playerY < 0)
            playerY = 0;
        else if (playerY > mapHeight - 1)
            playerY = mapHeight - 1;
        if (playerX < 0)
            playerX = 0;
        else if (playerX > mapWidth - 1)
            playerX = mapWidth - 1;
       
        // Update messages 
        int size = messages.size();
        for (int i = 0; i < 4; i++) {
            int index;
            if (i < size)
                index = size - 1 - i;
            else
                break;
            wmove(messageWindow, 3 - i, 0);
            wclrtoeol(messageWindow);
            mvwprintw(messageWindow, 3 - i, 0, "Character action: %s", messages[index].c_str());
        }

        // Update map
        mvwaddch(mapWindow, playerY, playerX, '@');
        move(playerY, playerX);

        wrefresh(mapWindow);
        wrefresh(messageWindow);
    }
    delwin(mapWindow); 
    delwin(messageWindow); 
    delwin(infoWindow); 
    endwin();
    return 0;
}
