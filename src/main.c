#include <gnpch.h>
#include <character.h>
#include <inventory.h>
#include <debug.h>
#include <tui.h>
#include <settings.h>
#include <aux/lua.h>
#include <scripting/luaGlue.h>
#include <platform/gn_system.h>

static Settings *settings;
static Inventory *mainInventory;
static Character *mainBoi;
static DiabloPath *path;
static DiabloUnit *unit;
static PlayerData *playerData;

static int Init()
{
    InitializeDebugLogFile();
    InitializeLua();
    LuaLoadFileIntoGlobalState("goonBase.lua");
    settings = CreateSettings();
    if (!settings)
    {
        LogError("Could not generate settings properly!");
        exit(1);
    }
    SetLogLevel(settings->debugLogLevel);
    InitializeMemoryReader();
    mainBoi = NewCharacter(settings);
    mainInventory = NewInventory(settings);
    unit = NewDiabloCharacterData(settings);
    path = calloc(1, sizeof(*path));
    playerData = calloc(1, sizeof(*playerData));
    InitializeBotLuaL();
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
    UpdateBotLuaL();
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
