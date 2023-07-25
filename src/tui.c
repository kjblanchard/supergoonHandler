#include <gnpch.h>
#include <tui.h>
#include <platform/gn_curses.h>
#include <tui/messageWindow.h>
#include <tui/charWindow.h>
#include <tui/inventoryWindow.h>
#include <tui/unitWindow.h>
#include <primitives/point.h>

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

    int width, height, x, y;
    height = 10;
    width = 20;
    x = (COLS - width) / 2;
    y = height;
    InitCharWindow(x, y, width, height);

    x = x - width - 2;
    InitInventoryWindow(x, y, width, height);

    x = ((COLS - width) / 2) + (width + 2);
    InitUnitWindow(x, y, width, height);

    height = 25;
    width = COLS - 4;
    x = 1;
    y = LINES - height - 2;
    InitMessageWindow(x, y, width, height);
    refresh();
    return 0;
}

int UpdateCurses(Inventory *inventory, Character *character, DiabloPath* path, DiabloUnit* unit, PlayerData* data)
{
    UpdateMessageWindow();
    UpdateInventoryWindow(inventory);
    int shouldExit = UpdateCharacterWindow(character);
    UpdateUnitWindow(unit, path, data);
    return shouldExit;
}

int WriteDebugMessage(const char *line)
{
    SendMessageToMessageWindow(line);
}

int EndCurses()
{
    endwin();
    return 0;
}
