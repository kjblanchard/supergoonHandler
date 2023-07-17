#include <settings.h>
#include <stdlib.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <string.h>

int InitializeLua(lua_State *state)
{
    luaL_openlibs(state);
    return 1;
}

Settings *CreateSettings()
{
    Settings *settings = malloc(sizeof(*settings));
    settings->images.count = 3;
    settings->images.images = calloc(settings->images.count, sizeof(char*));
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
    lua_pushstring(L, "resolution");
    lua_gettable(L, -2);
    lua_pushstring(L, "width");
    lua_gettable(L, -2);
    settings->resolution.width = (int)lua_tonumber(L, -1);
    lua_pop(L, 1);
    printf("Width is: %d\n", settings->resolution.width);
    lua_pushstring(L, "height");
    lua_gettable(L, -2);
    settings->resolution.height = (int)lua_tonumber(L, -1);
    printf("Height is: %d\n", settings->resolution.height);
    // Pop off the height, resolution
    lua_pop(L, 2);

    lua_pushstring(L, "images");
    // Settings->Images
    lua_gettable(L, -2);
    // Settings->Images->Nil, we use nil as the first key to traverse.
    lua_pushnil(L);
    int iter = 0;
    // Uses table on -2 (images) and pushes key and value onto the top of the stack
    while (lua_next(L, -2))
    {
        // stack now contains: -1 => value; -2 => key; -3 => table
        // copy the key so that lua_tostring does not modify the original
        lua_pushvalue(L, -2);
        // stack now contains: -1 => key; -2 => value; -3 => key; -4 => table
        const char *key = lua_tostring(L, -1);
        const char *value = lua_tostring(L, -2);
        settings->images.images[iter] = strdup(value);
        iter++;
        // pop value + copy of key, leaving original key
        lua_pop(L, 2);
        // stack now contains: -1 => key; -2 => table
    }
    lua_pop(L, 1);

    for (size_t i = 0; i < (size_t)settings->images.count; i++)
    {
        printf("Thing is %s\n", settings->images.images[i]);
    }
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
    // Character Get offsets.
    lua_pushnil(L);
    for (size_t i = 0; i < settings->characterMemoryLocation.offsetCount; i++)
    {
        lua_next(L, -2);
        lua_pushvalue(L, -2);
        settings->characterMemoryLocation.offsets[i] = lua_tointeger(L, -2);
        lua_pop(L, 2);
    }
    lua_pop(L, 2);
    lua_pop(L, 3);
    return settings;
}