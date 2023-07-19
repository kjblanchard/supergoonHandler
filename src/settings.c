#include <gnpch.h>
#include <settings.h>
#include <aux/lua.h>

#define SET_SETTINGS_FROM_LUA(name, classname, function)                                \
    lua_getfield(L, -1, name);                                                          \
    lua_getfield(L, -1, "offsets");                                                     \
    settings->classname.offsetCount = lua_rawlen(L, -1);                                \
    settings->classname.offsets = calloc(settings->classname.offsetCount, sizeof(int)); \
    LuaForEachTable(L, function, settings);                                             \
    lua_pop(L, 2)

static void SetCharacterOffsets(int key, const char *value, void *thing)
{
    Settings *settings = (Settings *)thing;
    int val = atoi(value);
    settings->characterMemoryLocation.offsets[key] = val;
}

static void SetInventoryOffsets(int key, const char *value, void *thing)
{
    Settings *settings = (Settings *)thing;
    int val = atoi(value);
    settings->inventoryMemoryLocation.offsets[key] = val;
}

int InitializeLua(lua_State *state)
{
    luaL_openlibs(state);
    return 1;
}

Settings *CreateSettings()
{
    Settings *settings = malloc(sizeof(*settings));
    lua_State *L = luaL_newstate();
    InitializeLua(L);
    if (!LuaLoadFile(L, "./scripts/config.lua"))
    {
        LogError("Could not read settings file!");
        return NULL;
    }
    // -1 settings
    lua_getglobal(L, "Settings");
    // -1 memoryLocations -2 settings
    lua_getfield(L, -1, "memoryLocations");
    SET_SETTINGS_FROM_LUA("character", characterMemoryLocation, SetCharacterOffsets);
    SET_SETTINGS_FROM_LUA("inventory", inventoryMemoryLocation, SetInventoryOffsets);
    lua_settop(L, 0);
    return settings;
}