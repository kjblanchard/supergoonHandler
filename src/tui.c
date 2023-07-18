#include <tui.h>
#include <platform/gn_curses.h>

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
static WINDOW *charWindow;

int InitCurses()
{
    initscr();            /* Start curses mode 		*/
    cbreak();             /* Line buffering disabled, Pass on
                           * everty thing to me 		*/
    keypad(stdscr, TRUE); /* I need that nifty F1 	*/

    printw("Press F1 to exit\n");
    // Updates every second
    timeout(1000);
    int startx, starty, width, height;
    height = 10;
    width = 20;
    starty = (LINES - height) / 2; /* Calculating for a center placement */
    startx = (COLS - width) / 2;   /* of the window		*/
    charWindow = create_newwin(height, width, starty, startx);
    refresh();
    return 0;
}
int UpdateCharacterWindow(Character *character)
{
    int ch;
    int x = 5;
    int y = 3;
    wclear(charWindow);
    box(charWindow, 0, 0);
    mvwprintw(charWindow, y, x, "Health: %d", character->Health);
    ++y;
    mvwprintw(charWindow, y, x, "Mana: %d", character->Mana);
    ++y;
    mvwprintw(charWindow, y, x, "Stamina: %d", character->Stamina);
    ++y;
    mvwprintw(charWindow, y, x, "Gold: %d", character->Gold);
    ++y;
    wmove(charWindow, y, x);
    wrefresh(charWindow);
    ch = getch();
    if (ch == KEY_F(1))
    {
        return 0;
    }
    return 1;
}

int EndCurses()
{
    endwin();
    return 0;
}
WINDOW *create_newwin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    // box(local_win, 0, 0); /* 0, 0 gives default characters
    //                        * for the vertical and horizontal
    //                        * lines			*/
    // wrefresh(local_win);  /* Show that box 		*/

    return local_win;
}

void destroy_win(WINDOW *local_win)
{
    /* box(local_win, ' ', ' '); : This won't produce the desired
     * result of erasing the window. It will leave it's four corners
     * and so an ugly remnant of window.
     */
    wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    /* The parameters taken are
     * 1. win: the window on which to operate
     * 2. ls: character to be used for the left side of the window
     * 3. rs: character to be used for the right side of the window
     * 4. ts: character to be used for the top side of the window
     * 5. bs: character to be used for the bottom side of the window
     * 6. tl: character to be used for the top left corner of the window
     * 7. tr: character to be used for the top right corner of the window
     * 8. bl: character to be used for the bottom left corner of the window
     * 9. br: character to be used for the bottom right corner of the window
     */
    wrefresh(local_win);
    delwin(local_win);
}

int DrawScreenLoop()
{
    return 0;
}