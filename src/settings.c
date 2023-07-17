#include <settings.h>
#include <stdlib.h>
#include <string.h>
#include <aux/lua.h>
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
    settings->images.count = 3;
    settings->images.images = calloc(settings->images.count, sizeof(char *));
    int result = 0;
    lua_State *L = luaL_newstate();
    InitializeLua(L);
    // Load the file into Luas space
    luaL_loadfile(L, "./scripts/config.lua");
    result = lua_pcall(L, 0, 0, 0);
    if (result != LUA_OK)
    {
        const char *error = lua_tostring(L, -1);
        fprintf(stderr, "Could not load file, error result: %d\nerror: %s", result, error);
        lua_pop(L, 1);
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
    LuaForEachTable(L, SetImages, settings);
    lua_pop(L, 1);
    lua_getfield(L, -1, "memoryLocations");
    lua_getfield(L, -1, "character");
    lua_getfield(L, -1, "base");
    settings->characterMemoryLocation.base = (int)lua_tonumber(L, -1);
    lua_pop(L, 1);
    lua_getfield(L, -1, "offsets");
    settings->characterMemoryLocation.offsetCount = lua_rawlen(L, -1);
    settings->characterMemoryLocation.offsets = calloc(settings->characterMemoryLocation.offsetCount, sizeof(int));
    LuaForEachTable(L, SetCharacterOffsets, settings);
    // offsets, character, memorylocations, Settings
    lua_pop(L, 4);
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