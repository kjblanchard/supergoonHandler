#include <gnpch.h>
#include <platform/gn_curses.h>
#include <tui/inventoryWindow.h>
#include <tui/tuiShared.h>

static WINDOW *g_invDisplayWindow;
static Rectangle g_inventoryWindowRect;

int InitInventoryWindow(int x, int y, int width, int height)
{
    g_inventoryWindowRect.x = x;
    g_inventoryWindowRect.y = y;
    g_inventoryWindowRect.w = width;
    g_inventoryWindowRect.h = height;
    g_invDisplayWindow = create_newwin(height, width, y, x);

}

int UpdateInventoryWindow(Inventory *inventory)
{
    wclear(g_invDisplayWindow);
    int x = 2;
    int y = 2;
    wmove(g_invDisplayWindow, y, x);

    for (size_t i = 0; i < INVENTORY_ITEM_SLOTS; i++)
    {
        if (inventory->Items[i])
        {
            wattron(g_invDisplayWindow, COLOR_PAIR(4));

            waddch(g_invDisplayWindow, 'x');
            wattroff(g_invDisplayWindow, COLOR_PAIR(4));
        }
        else
        {
            wattron(g_invDisplayWindow, COLOR_PAIR(3));
            waddch(g_invDisplayWindow, 'o');
            wattroff(g_invDisplayWindow, COLOR_PAIR(3));
        }
        ++x;
        if (x > 11)
        {
            x = 2;
            ++y;
            wmove(g_invDisplayWindow, y, x);
        }
    }
    box(g_invDisplayWindow, 0, 0);
    mvwprintw(g_invDisplayWindow, 0, 1, "Inventory");
    wrefresh(g_invDisplayWindow);
}