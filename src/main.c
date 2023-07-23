#include <gnpch.h>
#include <character.h>
#include <inventory.h>
#include <debug.h>
#include <tui.h>
#include <settings.h>
#include <platform/gn_system.h>

static Settings *settings;
static Inventory *mainInventory;
static Character *mainBoi;
static int bro;

static int Init()
{
    InitializeDebugLogFile();
    settings = CreateSettings();
    InitializeMemoryReader();
    mainBoi = NewCharacter(settings);
    mainInventory = NewInventory(settings);
    InitCurses();
    bro = 0;
    return 0;
}

static int Close()
{
    EndCurses();
    CloseMemoryReader();
    CloseDebugLogFile();
    return EXIT_SUCCESS;
}

static int Loop(Character *character)
{
    RefreshCharacter(mainBoi);
    RefreshInventory(mainInventory);
    UpdateInventoryWindow(mainInventory);
    if(bro < 2)
    {
        ++bro;
        SendMessageToMessageWindow("hello!!! From the boi here");
    }
    if (UpdateCharacterWindow(character))
    {
        return 1;
    }
    return 0;
}

int main()
{
    Init();
    UpdateMessageWindow();

    while (Loop(mainBoi))
    {
    }
    return Close();
}
