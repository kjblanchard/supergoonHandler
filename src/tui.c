#include <gnpch.h>
#include <tui.h>
#include <platform/gn_curses.h>
#include <tui/messageWindow.h>
#include <tui/charWindow.h>
#include <tui/inventoryWindow.h>
#include <tui/unitWindow.h>
#include <primitives/point.h>

static WINDOW *mainWindow;
static const int g_updateTimeInMs = 500;
static const int g_minCharWindowSizeY = 6;
static const int g_minCharWindowSizeX = 20;

static void InitWindows()
{
    int width, height, x, y, xpadding, ypadding;
    xpadding = COLS / 20;
    ypadding = LINES / 10;
    height = g_minCharWindowSizeY + ypadding;
    width = g_minCharWindowSizeX + xpadding;
    x = (COLS - width) / 8;
    y = height / 4;
    InitCharWindow(x, y, width, height);
    x = x + width + 2;
    InitInventoryWindow(x, y, width, height);
    x = x + width + 2;
    InitUnitWindow(x, y, width, height);
    height = LINES / 3;
    width = COLS - 4;
    x = 2;
    y = LINES - height - 2;
    InitMessageWindow(x, y, width, height);
}

int InitCurses()
{
    mainWindow = initscr();
    cbreak();
    keypad(stdscr, TRUE);
    // Updates every second
    timeout(g_updateTimeInMs);
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_GREEN);
    init_pair(2, COLOR_CYAN, COLOR_BLUE);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    use_default_colors();
    box(mainWindow, 0, 0);
    mvwprintw(mainWindow, 0, 2, "Supergoon Bot");
    refresh();
    InitWindows();
    return 0;
}

int UpdateCurses(Inventory *inventory, Character *character, DiabloPath *path, DiabloUnit *unit, PlayerData *data)
{
    UpdateInventoryWindow(inventory);
    UpdateUnitWindow(unit, path, data);
    UpdateMessageWindow();
    int shouldExit = UpdateCharacterWindow(character);
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
