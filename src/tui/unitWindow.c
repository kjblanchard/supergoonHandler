#include <gnpch.h>
#include <tui/tuiShared.h>
#include <tui/unitWindow.h>
#include <character.h>
#include <primitives/rectangle.h>

static WINDOW *g_UnitWindow;
static Gn_Rectangle g_unitWindowRect;

int InitUnitWindow(int x, int y, int width, int height)
{
    g_unitWindowRect.x = x;
    g_unitWindowRect.y = y;
    g_unitWindowRect.w = width;
    g_unitWindowRect.h = height;
    g_UnitWindow = create_newwin(height, width, y, x);
}
int UpdateUnitWindow(DiabloUnit *unit, DiabloPath *path, PlayerData *playerData)
{
    int x = 5;
    int y = 3;
    wclear(g_UnitWindow);
    box(g_UnitWindow, 0, 0);
    mvwprintw(g_UnitWindow, y, x, "Name %s", playerData->Name);
    ++y;
    mvwprintw(g_UnitWindow, y, x, "X: %d", path->X);
    ++y;
    mvwprintw(g_UnitWindow, y, x, "Y: %d", path->Y);
    ++y;
    mvwprintw(g_UnitWindow, y, x, "Act Number: %d", unit->ActNumber + 1);
    ++y;
    wmove(g_UnitWindow, y, x);
    mvwprintw(g_UnitWindow, 0, 1, "Character");
    wrefresh(g_UnitWindow);
}
