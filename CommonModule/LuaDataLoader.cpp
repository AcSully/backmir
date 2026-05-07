// [reconstructed] ÖØ½¨ÓÚ 2026-05-06
#include "LuaDataLoader.h"
#include "item_extra_suit_def.h"
#include <lauxlib.h>

bool LuaDataLoader::LoadSuitAttrib(lua_State* L, const char* _pszName,
                                   std::map<int, ItemExtraAttribList*>& _out)
{
    if (!L || !_pszName) return false;
    lua_getglobal(L, _pszName);
    if (!lua_istable(L, -1)) { lua_pop(L, 1); return false; }

    lua_pushnil(L);
    while (lua_next(L, -2) != 0)
    {
        if (lua_type(L, -2) == LUA_TNUMBER && lua_istable(L, -1))
        {
            int suitId = (int)lua_tointeger(L, -2);
            ItemExtraAttribList* pList = new ItemExtraAttribList();

            int nLen = (int)lua_objlen(L, -1);
            for (int i = 1; i <= nLen; ++i)
            {
                lua_rawgeti(L, -1, i);
                if (lua_istable(L, -1))
                {
                    ItemExtraAttribItem item = { 0, 0 };
                    lua_rawgeti(L, -1, 1); item.nAttribID    = (int)lua_tointeger(L, -1); lua_pop(L, 1);
                    lua_rawgeti(L, -1, 2); item.nAttribValue = (int)lua_tointeger(L, -1); lua_pop(L, 1);
                    pList->items.push_back(item);
                }
                lua_pop(L, 1);
            }
            _out[suitId] = pList;
        }
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
    return true;
}

bool LuaDataLoader::LoadRawVectorInt(lua_State* L, const char* _pszName, std::vector<int>& _out)
{
    if (!L || !_pszName) return false;
    lua_getglobal(L, _pszName);
    if (!lua_istable(L, -1)) { lua_pop(L, 1); return false; }
    int n = (int)lua_objlen(L, -1);
    _out.clear();
    _out.reserve(n);
    for (int i = 1; i <= n; ++i)
    {
        lua_rawgeti(L, -1, i);
        if (lua_type(L, -1) == LUA_TNUMBER)
            _out.push_back((int)lua_tointeger(L, -1));
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
    return true;
}
