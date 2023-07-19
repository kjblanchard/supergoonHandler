#pragma once
typedef struct lua_State lua_State;
/**
 * @brief -1 on The stack is the key, -2 on the stack is the value -3 is original key, -4 is table
 *
 * @param L
 * @param func
 * @return int
 */
int LuaForEachTable(lua_State *L, void (*func)(const char*, const char* ,  void *), void *modifyThing);
int LuaLoadFile(lua_State *L, const char *file);
void DumpLuaStack (lua_State *state);