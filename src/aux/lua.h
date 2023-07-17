#pragma once
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

/**
 * @brief -1 on The stack is the key, -2 on the stack is the value -3 is original key, -4 is table
 *
 * @param L
 * @param func
 * @return int
 */
int LuaForEachTable(lua_State *L, int(*func)(lua_State *, void *), void* modifyThing);
int LuaLoadFile(lua_State* L, const char* file);

