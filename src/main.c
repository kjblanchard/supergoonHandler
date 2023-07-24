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
static char strings[20][20] = {"Helloolgirl", "no u", "onceler", "lorax", "birthdayboi", "turtle", "mal", "bro", "biggie", "smalls", "what", "boring", "old"};

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
    if (bro < 15)
    {
        SendMessageToMessageWindow(strings[bro]);
        ++bro;
    }
    PrintDebugTui();
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
