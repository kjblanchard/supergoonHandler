#include <gnpch.h>
#include <platform/gn_curses.h>
#include <tui/charWindow.h>
#include <tui/tuiShared.h>
#include <character.h>

static WINDOW *g_charWindow;
static Gn_Rectangle g_charWindowRect;

int InitCharWindow(int x, int y, int width, int height)
{

    g_charWindowRect.x = x;
    g_charWindowRect.y = y;
    g_charWindowRect.w = width;
    g_charWindowRect.h = height;
    g_charWindow = create_newwin(height, width, y, x);
}

int UpdateCharacterWindow(Character *character)
{
    int ch;
    int x = 5;
    int y = 3;
    wclear(g_charWindow);
    box(g_charWindow, 0, 0);
    mvwprintw(g_charWindow, y, x, "Health: %d", character->Health);
    ++y;
    mvwprintw(g_charWindow, y, x, "Mana: %d", character->Mana);
    ++y;
    mvwprintw(g_charWindow, y, x, "Stamina: %d", character->Stamina);
    ++y;
    mvwprintw(g_charWindow, y, x, "Gold: %d", character->Gold);
    ++y;
    wmove(g_charWindow, y, x);
    mvwprintw(g_charWindow, 0, 1, "Status");
    wrefresh(g_charWindow);
    ch = getch();
    if (ch == KEY_F(1) || ch == 'q')
    {
        return 0;
    }
    return 1;
}

Gn_Rectangle GetCharWindowRect();
Point GetCharWindowPos();
Point GetCharWindowSize();