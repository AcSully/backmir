// [reconstructed] ÖØ½¨ÓÚ 2026-05-06
#include "LuaConfigLoader.h"
#include <lauxlib.h>

bool LuaConfigLoader::LoadInt(lua_State* L, const char* _pszGlobalName, int& _out)
{
    if (!L || !_pszGlobalName) return false;
    lua_getglobal(L, _pszGlobalName);
    bool ok = (lua_type(L, -1) == LUA_TNUMBER);
    if (ok) _out = (int)lua_tointeger(L, -1);
    lua_pop(L, 1);
    return ok;
}

bool LuaConfigLoader::LoadString(lua_State* L, const char* _pszGlobalName, std::string& _out)
{
    if (!L || !_pszGlobalName) return false;
    lua_getglobal(L, _pszGlobalName);
    bool ok = (lua_type(L, -1) == LUA_TSTRING);
    if (ok) _out = lua_tostring(L, -1);
    lua_pop(L, 1);
    return ok;
}

bool LuaConfigLoader::LoadVectorString(lua_State* L, const char* _pszGlobalName, std::vector<std::string>& _out)
{
    if (!L || !_pszGlobalName) return false;
    lua_getglobal(L, _pszGlobalName);
    if (!lua_istable(L, -1)) { lua_pop(L, 1); return false; }
    _out.clear();
    int n = (int)lua_objlen(L, -1);
    for (int i = 1; i <= n; ++i)
    {
        lua_rawgeti(L, -1, i);
        if (lua_type(L, -1) == LUA_TSTRING)
            _out.push_back(lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
    return true;
}
