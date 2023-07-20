#include <gnpch.h>
#include <character.h>
#include <inventory.h>
#include <debug.h>
#include <tui.h>
#include <settings.h>
#include <platform/gn_system.h>

static Settings *settings;
static Inventory* mainInventory;
static Character *mainBoi;

static int Init()
{
    InitializeDebugLogFile();
    settings = CreateSettings();
    InitializeMemoryReader();
    mainBoi = NewCharacter(settings);
    mainInventory = NewInventory(settings);
    InitCurses();
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
    if (UpdateCharacterWindow(character))
    {
        return 1;
    }
    return 0;
}

int main()
{
    Init();


    while (Loop(mainBoi))
    {

    }
    return Close();
}
