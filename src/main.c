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
static DiabloPath *path;
static DiabloUnit *unit;
static PlayerData *playerData;
// int bro;

static int Init()
{
    InitializeDebugLogFile();
    settings = CreateSettings();
    if (!settings)
    {
        LogError("Could not generate settings properly!");
        exit(1);
    }

    InitializeMemoryReader();
    mainBoi = NewCharacter(settings);
    mainInventory = NewInventory(settings);
    unit = NewDiabloCharacterData(settings);
    path = calloc(1, sizeof(*path));
    playerData = calloc(1, sizeof(*playerData));
    // bro = 0;
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

static int Loop()
{
    RefreshCharacter(mainBoi);
    RefreshInventory(mainInventory);
    RefreshDiabloCharacterData(unit, path, playerData);
    int shouldExit = UpdateCurses(mainInventory, mainBoi, path, unit, playerData);
    // ++bro;
    return shouldExit;
}

int main()
{
    Init();
    while (Loop())
    {
    }
    return Close();
}
