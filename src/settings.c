#include <settings.h>
#include <stdlib.h>
#include <string.h>
#include <aux/lua.h>
#include <debug.h>
static int SetCharacterOffsets(lua_State *L, void *thing);
static int SetImages(lua_State *L, void *thing);

int InitializeLua(lua_State *state)
{
    luaL_openlibs(state);
    return 1;
}

Settings *CreateSettings()
{
    Settings *settings = malloc(sizeof(*settings));
    int result = 0;
    lua_State *L = luaL_newstate();
    InitializeLua(L);
    if(!LuaLoadFile(L,  "./scripts/config.lua"))
    {
        LogError("Could not read settings file!");
        return NULL;
    }
    lua_getglobal(L, "Settings");
    lua_getfield(L, -1, "resolution");
    lua_getfield(L, -1, "width");
    settings->resolution.width = lua_tointeger(L, -1);
    lua_pop(L, 1);
    lua_pushstring(L, "height");
    lua_gettable(L, -2);
    settings->resolution.height = lua_tointeger(L, -1);
    lua_pop(L, 2);
    lua_getfield(L, -1, "images");
    settings->images.count = lua_rawlen(L, -1);
    settings->images.images = calloc(settings->characterMemoryLocation.offsetCount, sizeof(char*));
    LuaForEachTable(L, SetImages, settings);
    lua_pop(L, 1);
    lua_getfield(L, -1, "memoryLocations");
    lua_getfield(L, -1, "character");
    lua_getfield(L, -1, "base");
    settings->characterMemoryLocation.base = lua_tointeger(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, -1, "offsets");
    settings->characterMemoryLocation.offsetCount = lua_rawlen(L, -1);
    settings->characterMemoryLocation.offsets = calloc(settings->characterMemoryLocation.offsetCount, sizeof(int));
    LuaForEachTable(L, SetCharacterOffsets, settings);
    // offsets, character, memorylocations, Settings
    lua_settop(L, 0);
    return settings;
}
static int SetImages(lua_State *L, void *thing)
{
    Settings *settings = (Settings *)thing;
    if (!settings)
        return 1;
    int i = lua_tointeger(L, -1) -1;
    const char*  value = lua_tostring(L, -2);
    settings->images.images[i] = strdup(value);
}

static int SetCharacterOffsets(lua_State *L, void *thing)
{
    Settings *settings = (Settings *)thing;
    if (!settings)
        return 1;
    int i = lua_tointeger(L, -1) -1;
    int offset = lua_tointeger(L, -2);
    settings->characterMemoryLocation.offsets[i] = offset;
}