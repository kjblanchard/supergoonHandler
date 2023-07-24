#include <gnpch.h>
#include <tui.h>
#include <platform/gn_curses.h>

struct Point
{
    int x;
    int y;
};

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
static WINDOW *charWindow;
static struct Point charDisplayPoint;
static WINDOW *invDisplayWindow;
static struct Point invDisplayPoint;
static WINDOW *messageWindow;
static struct Point messageDisplayPoint;

typedef char messageWindowMessage[150];
static messageWindowMessage messageWindowMessages[20];
// static char **messageWindowMessages;
static int messageWindowMessagesLength; // 4 23
static size_t messageWindowMessageSize;
static int messageWindowLastMessage;

void PrintDebugTui()
{
    char message[30];
    sprintf(message, "cols is %d", COLS);
    SendMessageToMessageWindow(message);
}

InitCurses()
{
    initscr();            /* Start curses mode 		*/
    cbreak();             /* Line buffering disabled, Pass on
                           * everty thing to me 		*/
    keypad(stdscr, TRUE); /* I need that nifty F1 	*/

    printw("Supergoon Bot\nPress F1 to exit\n");
    // Updates every second
    timeout(1000);
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_GREEN);
    init_pair(2, COLOR_CYAN, COLOR_BLUE);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    use_default_colors();

    int width, height;
    height = 10;
    width = 20;
    charDisplayPoint.y = 2;
    charDisplayPoint.x = (COLS - width) / 2;
    charWindow = create_newwin(height, width, charDisplayPoint.y, charDisplayPoint.x);

    invDisplayPoint.y = charDisplayPoint.y;
    invDisplayPoint.x = charDisplayPoint.x - width - 2;
    invDisplayWindow = create_newwin(height, width, invDisplayPoint.y, invDisplayPoint.x);

    height = 25;
    width = COLS - 4;
    messageDisplayPoint.x = 1;
    messageDisplayPoint.y = LINES - height - 2;
    messageWindow = create_newwin(height, width, messageDisplayPoint.y, messageDisplayPoint.x);
    scrollok(messageWindow, TRUE);

    messageWindowLastMessage = 0;
    messageWindowMessageSize = COLS - 5;
    messageWindowMessagesLength = height - 2;
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
    mvwprintw(charWindow, 0, 1, "Status");
    wrefresh(charWindow);
    ch = getch();
    if (ch == KEY_F(1) || ch == 'q')
    {
        return 0;
    }
    return 1;
}

int UpdateInventoryWindow(Inventory *inventory)
{
    wclear(invDisplayWindow);
    int x = 2;
    int y = 2;
    wmove(invDisplayWindow, y, x);

    for (size_t i = 0; i < INVENTORY_ITEM_SLOTS; i++)
    {
        if (inventory->Items[i])
        {
            wattron(invDisplayWindow, COLOR_PAIR(4));

            waddch(invDisplayWindow, 'x');
            wattroff(invDisplayWindow, COLOR_PAIR(4));
        }
        else
        {
            wattron(invDisplayWindow, COLOR_PAIR(3));
            waddch(invDisplayWindow, 'o');
            wattroff(invDisplayWindow, COLOR_PAIR(3));
        }
        ++x;
        if (x > 11)
        {
            x = 2;
            ++y;
            wmove(invDisplayWindow, y, x);
        }
    }
    box(invDisplayWindow, 0, 0);
    mvwprintw(invDisplayWindow, 0, 1, "Inventory");
    wrefresh(invDisplayWindow);
}

int UpdateMessageWindow()
{
    box(messageWindow, 0, 0);
    mvwprintw(messageWindow, 0, 1, "Messages");
    wrefresh(messageWindow);
}
void SendMessageToMessageWindow(const char *line)
{
    wclear(messageWindow);
    size_t newLineLength, oldLineLength = 0;
    // Increment the last message
    messageWindowLastMessage = messageWindowLastMessage < 16 ? messageWindowLastMessage + 1 : 16;
    // Shift all messages up one, starting with the last
    for (size_t i = messageWindowLastMessage - 1 ; i > 0 ; i--)
    {
            oldLineLength = strlen(messageWindowMessages[i]);
            newLineLength = strlen(messageWindowMessages[i - 1]);
            if (oldLineLength > newLineLength)
                memset(messageWindowMessages[i], '\0', oldLineLength);
            strcpy(messageWindowMessages[i], messageWindowMessages[i - 1]);
    }
    // Calculate the max length of the line, incase we are over the max line size so it doesn't wrap.
    newLineLength = strlen(line);
    newLineLength = newLineLength > messageWindowMessageSize ? messageWindowMessageSize : newLineLength;
    oldLineLength = strlen(messageWindowMessages[0]);
    if (oldLineLength > newLineLength)
        memset(messageWindowMessages[0], '\0', oldLineLength);
    strncpy(messageWindowMessages[0], line, newLineLength);

    for (int i = 0; i < messageWindowLastMessage; i++)
    {
        mvwprintw(messageWindow, i + 1, 2, messageWindowMessages[i]);
    }
    wrefresh(messageWindow);
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