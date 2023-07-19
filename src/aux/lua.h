#pragma once
typedef struct lua_State lua_State;
/**
 * @brief For lua tables that are simple arrays.  Do something for each one, passing i and value into the func
 *
 * @param func
 * @return int
 */
int LuaForEachTable(lua_State *L, void (*func)(int, const char* ,  void *), void *modifyThing);
int LuaLoadFile(lua_State *L, const char *file);
void DumpLuaStack (lua_State *state);