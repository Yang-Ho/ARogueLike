#include <ncurses.h>

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

    while(gameover == 0) {
        input = getch();
    }
    delwin(mapWindow); 
    delwin(messageWindow); 
    delwin(infoWindow); 
    endwin();
    return 0;
}
