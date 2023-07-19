#include <gnpch.h>
#include <settings.h>
#include <aux/lua.h>

// #define SET_SETTINGS_FROM_LUA(name, classname, function) \
// -1 character -2 memoryLocations -3 settings\
    lua_getfield(L, -1, name);\
// -1 offsets -2 character -3 memoryLocations -4 settings\
    lua_getfield(L, -1, "offsets");\
    settings->classname.offsetCount = lua_rawlen(L, -1);\
    settings->classname.offsets = calloc(settings->classname.offsetCount, sizeof(int));\
// offsets, character, memorylocations, Settings\
    LuaForEachTable(L, function, settings);\
// -1 memoryLocations, -2 settings\
    lua_pop(L, 2);\

static void SetImages(int key, const char *value, void *thing)
{
    Settings *settings = (Settings *)thing;
    settings->images.images[key] = strdup(value);
}

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
    // -1 resolution -2 settings
    lua_getfield(L, -1, "resolution");
    // -1 width -2 resolution -3 settings
    lua_getfield(L, -1, "width");
    settings->resolution.width = lua_tointeger(L, -1);
    lua_pop(L, 1);
    // -1 height -2 resolution -3 settings
    lua_getfield(L, -1, "height");
    settings->resolution.height = lua_tointeger(L, -1);
    //  -1 settings
    lua_pop(L, 2);
    // -1 images  -2 settings
    lua_getfield(L, -1, "images");
    settings->images.count = lua_rawlen(L, -1);
    settings->images.images = calloc(settings->images.count, sizeof(char *));
    LuaForEachTable(L, SetImages, settings);
    // -1 settings
    lua_pop(L, 1);
    // -1 memoryLocations -2 settings
    lua_getfield(L, -1, "memoryLocations");
    // SET_SETTINGS_FROM_LUA("character", characterMemoryLocation, SetCharacterOffsets )
    // -1 character -2 memoryLocations -3 settings
    lua_getfield(L, -1, "character");
    // -1 offsets -2 character -3 memoryLocations -4 settings
    lua_getfield(L, -1, "offsets");
    settings->characterMemoryLocation.offsetCount = lua_rawlen(L, -1);
    settings->characterMemoryLocation.offsets = calloc(settings->characterMemoryLocation.offsetCount, sizeof(int));
    // offsets, character, memorylocations, Settings
    LuaForEachTable(L, SetCharacterOffsets, settings);
    // -1 memoryLocations, -2 settings
    lua_pop(L, 2);
    // -1 inventory, -2 memoryLocations, -3 settings
    lua_getfield(L, -1, "inventory");
    // -1 offsets -2 character -3 memoryLocations -4 settings
    lua_getfield(L, -1, "offsets");
    settings->inventoryMemoryLocation.offsetCount = lua_rawlen(L, -1);
    settings->inventoryMemoryLocation.offsets = calloc(settings->inventoryMemoryLocation.offsetCount, sizeof(int));
    // offsets, character, memorylocations, Settings
    LuaForEachTable(L, SetInventoryOffsets, settings);
    lua_settop(L, 0);
    return settings;
}