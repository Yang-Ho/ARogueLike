#include <ncurses.h>

int main() {
    WINDOW *my_win;

    int startx, starty, width, height;
    int input;

    int playerx, playery;

    initscr();
    start_color();

    raw();
    keypad(stdscr, TRUE);
    noecho();

    width = 80;
    height = 24;
    startx = 0;
    starty = 0;

    playerx = width / 2;
    playery = height / 2;

    my_win = newwin(height, width, starty, startx);
    box(my_win, 0, 0);
    wborder(my_win, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwaddch(my_win, playery, playerx, '@');
    refresh();
    wrefresh(my_win);

    move(playery+starty, playerx+startx);
    
    while( (input = getch()) != 'q' ) {
        switch(input) {
            case 'w':
                wborder(my_win, '|', '|', '-', '-', '+', '+', '+', '+');
                mvwaddch(my_win, playery, playerx, '.');
                mvwaddch(my_win, --playery, playerx, '@');
                break;
            case 's':
                wborder(my_win, '|', '|', '-', '-', '+', '+', '+', '+');
                mvwaddch(my_win, playery, playerx, '.');
                mvwaddch(my_win, ++playery, playerx, '@');
                break;
            case 'a':
                wborder(my_win, '|', '|', '-', '-', '+', '+', '+', '+');
                mvwaddch(my_win, playery, playerx, '.');
                mvwaddch(my_win, playery, --playerx, '@');
                break;
            case 'd':
                wborder(my_win, '|', '|', '-', '-', '+', '+', '+', '+');
                mvwaddch(my_win, playery, playerx, '.');
                mvwaddch(my_win, playery, ++playerx, '@');
                break;
        }
        move(playery+starty, playerx+startx);
        wrefresh(my_win);
    }

    delwin(my_win);
    endwin();
    return 0;
}
