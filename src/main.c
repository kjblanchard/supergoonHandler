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
static char strings[20][20] = {"Helloolgirl", "no u", "onceler", "lorax", "birthdayboi", "turtle", "mal", "bro", "biggie", "smalls", "what", "boring", "old"};
int bro;

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
    bro = 0;
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
    int shouldExit = UpdateCurses(mainInventory, mainBoi, path, unit, playerData);
    WriteDebugMessage(strings[bro]);
    ++bro;
    return shouldExit;
}

int main()
{
    Init();
    while (Loop(mainBoi))
    {
    }
    return Close();
}
