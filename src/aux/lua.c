#include <aux/lua.h>
int LuaForEachTable(lua_State *L, int (*func)(lua_State *, void *), void *modifyThing)
{
    lua_pushnil(L);
    while (lua_next(L, -2))
    {
        // stack now contains: -1 => value; -2 => key; -3 => table
        // copy the key so that lua_tostring does not modify the original
        lua_pushvalue(L, -2);
        const char* key = lua_tostring(L, -1);
        const char* value = lua_tostring(L, -2);
        printf("Key is %s Value is %s", key, value);
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