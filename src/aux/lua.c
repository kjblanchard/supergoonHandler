#include <gnpch.h>
#include <aux/lua.h>

int LuaForEachTable(lua_State *L, void (*func)(int, const char *, void *), void *modifyThing)
{
  lua_pushnil(L);
  while (lua_next(L, -2))
  {
    // stack now contains: -1 => value; -2 => key; -3 => table
    // copy the key so that lua_tostring does not modify the original
    lua_pushvalue(L, -2);
    // stack now contains: -1 => key; -2 => value; -3 => key; -4 => table
    int key = lua_tointeger(L, -1) - 1;
    const char *value = lua_tostring(L, -2);
    func(key, value, modifyThing);
    // pop value + copy of key, leaving original key
    lua_pop(L, 2);
    // stack now contains: -1 => key; -2 => table
  }
  return 0;
}

int LuaLoadFile(lua_State *L, const char *file)
{
  luaL_loadfile(L, file);
  int result = lua_pcall(L, 0, 0, 0);
  if (result != LUA_OK)
  {
    const char *error = lua_tostring(L, -1);
    LogError("Could not load file, error result: %d, error: %s", result, error);
    lua_pop(L, 1);
    return false;
  }
  return true;
}
void DumpLuaStack(lua_State *state)
{
  int top = lua_gettop(state);
  for (int i = 1; i <= top; i++)
  {
    LogWarn("%d\t%s\t", i, luaL_typename(state, i));
    switch (lua_type(state, i))
    {
    case LUA_TNUMBER:
      LogWarn("%g", lua_tonumber(state, i));
      break;
    case LUA_TSTRING:
      LogWarn("%s", lua_tostring(state, i));
      break;
    case LUA_TBOOLEAN:
      LogWarn("%s", (lua_toboolean(state, i) ? "true" : "false"));
      break;
    case LUA_TNIL:
      LogWarn("%s", "nil");
      break;
    default:
      LogWarn("%p", lua_topointer(state, i));
      break;
    }
  }
}