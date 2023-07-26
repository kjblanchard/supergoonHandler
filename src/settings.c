#include <gnpch.h>
#include <settings.h>
#include <aux/lua.h>

#pragma region MACROS
/**
 * @brief Grabs all the offsets from a specific table inside of lua config.
 */
#define SET_SETTINGS_FROM_LUA(name, classname, function)                                \
    lua_getfield(L, -1, name);                                                          \
    lua_getfield(L, -1, "offsets");                                                     \
    settings->classname.offsetCount = lua_rawlen(L, -1);                                \
    settings->classname.offsets = calloc(settings->classname.offsetCount, sizeof(int)); \
    LuaForEachTable(L, function, settings);                                             \
    lua_pop(L, 2)
/**
 * @brief Creates a static function to grab offsets for something
 * Name is the name of the function
 * type is the type to get from settings
 */
#define CREATE_OFFSET_FUNC(name, type)                        \
    static void name(int key, const char *value, void *thing) \
    {                                                         \
        Settings *settings = (Settings *)thing;               \
        int val = atoi(value);                                \
        settings->type.offsets[key] = val;                    \
    }

CREATE_OFFSET_FUNC(Set_Char, characterMemoryLocation)
CREATE_OFFSET_FUNC(Set_Inv, inventoryMemoryLocation)
CREATE_OFFSET_FUNC(Set_CharData, diabloCharacterDataMemoryLocation)
#pragma endregion


Settings *CreateSettings()
{
    Settings *settings = malloc(sizeof(*settings));
    lua_State* L = GetGlobalLuaState();
    LuaLoadFileIntoGlobalState("config.lua");
    // -1 settings
    lua_getglobal(L, "Settings");
    lua_getfield(L, -1, "logLevel");
    settings->debugLogLevel = lua_tointeger(L, -1);
    // lua_pop(2);
    lua_settop(L, -2);
    // -1 memoryLocations -2 settings
    lua_getfield(L, -1, "memoryLocations");
    SET_SETTINGS_FROM_LUA("character", characterMemoryLocation, Set_Char);
    SET_SETTINGS_FROM_LUA("inventory", inventoryMemoryLocation, Set_Inv);
    SET_SETTINGS_FROM_LUA("charData", diabloCharacterDataMemoryLocation, Set_CharData);
    lua_settop(L, 0);
    return settings;
}