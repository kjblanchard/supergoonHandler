#include <settings.h>
#include <stdlib.h>
#include <string.h>
#include <aux/lua.h>
static int DoTheThing(lua_State *L, void *thing);
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
    // -1 is now resolution table
    lua_getfield(L, -1, "resolution");
    // lua_pushstring(L, "resolution");
    // lua_gettable(L, -2);
    // lua_pushstring(L, "width");
    // lua_gettable(L, -2);
    lua_getfield(L, -1, "width");
    settings->resolution.width = (int)lua_tonumber(L, -1);
    lua_pop(L, 1);
    lua_pushstring(L, "height");
    lua_gettable(L, -2);
    settings->resolution.height = (int)lua_tonumber(L, -1);
    // Pop off the height, resolution
    lua_pop(L, 2);

    lua_pushstring(L, "images");
    lua_gettable(L, -2);
    LuaForEachTable(L, SetImages, settings);
    lua_pushstring(L, "memoryLocations");
    lua_gettable(L, -2);
    lua_pushstring(L, "character");
    lua_gettable(L, -2);
    lua_pushstring(L, "base");
    settings->characterMemoryLocation.base = (int)lua_tonumber(L, -1);
    lua_pop(L, 1);
    lua_pushstring(L, "offsets");
    lua_gettable(L, -2);
    settings->characterMemoryLocation.offsetCount = lua_rawlen(L, -1);
    settings->characterMemoryLocation.offsets = calloc(settings->characterMemoryLocation.offsetCount, sizeof(int));
    LuaForEachTable(L, DoTheThing, settings);
    lua_pop(L, 3);
    return settings;
}
static int SetImages(lua_State *L, void *thing)
{
    Settings *settings = (Settings *)thing;
    if (!settings)
        return 1;
    int i = lua_tointeger(L, -1);
    const char*  value = lua_tostring(L, -2);
    settings->images.images[i] = strdup(value);
}

static int DoTheThing(lua_State *L, void *thing)
{
    Settings *settings = (Settings *)thing;
    if (!settings)
        return 1;
    int i = lua_tointeger(L, -1);
    int offset = lua_tointeger(L, -2);
    settings->characterMemoryLocation.offsets[i] = offset;
}