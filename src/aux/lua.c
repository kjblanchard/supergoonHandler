#include <aux/lua.h>
int LuaForEachTable(lua_State *L, int (*func)(lua_State *, void *), void *modifyThing)
{
    lua_pushnil(L);
    while (lua_next(L, -2))
    {
        // stack now contains: -1 => value; -2 => key; -3 => table
        // copy the key so that lua_tostring does not modify the original
        lua_pushvalue(L, -2);
        // stack now contains: -1 => key; -2 => value; -3 => key; -4 => table
        int funcResult = func(L, modifyThing);
        // pop value + copy of key, leaving original key
        lua_pop(L, 2);
        // stack now contains: -1 => key; -2 => table
        if (!funcResult)
        {
            break;
        }
    }
    // lua_pop(L, 1);
    // Stack now contains the initial table that was put on the stack
    return 0;
}

int LuaLoadFile(lua_State *L, const char *file)
{
    luaL_loadfile(L, file);
    int result = lua_pcall(L, 0, 0, 0);
    if (result != LUA_OK)
    {
        const char *error = lua_tostring(L, -1);
        fprintf(stderr, "Could not load file, error result: %d\nerror: %s", result, error);
        lua_pop(L, 1);
        return 0;
    }
    return 1;
}