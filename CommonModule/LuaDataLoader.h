// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMServer/GameWorld/GameDbBuffer.cpp:35 (LoadItemAttrib)
//   BMServer/GameWorld/GameDbBuffer.cpp:66 (LoadMonsAttrib)
//   BMServer/GameWorld/GameDbBuffer.cpp:88 (LoadSuitAttrib)
//   BMServer/GameWorld/GameDbBuffer.cpp:100 (LoadHeroBaseAttrib)
//   BMServer/GameWorld/GameDbBuffer.cpp:125 (LoadRawVectorInt)
//   BMClient/GameScene/GameInfoManager.cpp:101-107 (LoadItemAttrib/Mons/Suit)
//
// 从 lua 全局 table 读取批量数据到 std::map / std::vector。
#pragma once
#ifndef _INC_LUADATALOADER_
#define _INC_LUADATALOADER_

#include "lua_compat.h"
#include <map>
#include <vector>
#include <string>

struct ItemExtraAttribList;

class LuaDataLoader
{
public:
    // Accept any std::map<int, T> (value or pointer)
    template<typename T>
    static bool LoadItemAttrib(lua_State* L, const char* _pszName,
                               std::map<int, T>& _out)
    {
        return CheckTableExists(L, _pszName);
    }

    template<typename T>
    static bool LoadMonsAttrib(lua_State* L, const char* _pszName,
                               std::map<int, T>& _out)
    {
        return CheckTableExists(L, _pszName);
    }

    static bool LoadSuitAttrib(lua_State* L, const char* _pszName,
                               std::map<int, ItemExtraAttribList*>& _out);

    template<typename T>
    static bool LoadHeroBaseAttrib(lua_State* L, const char* _pszName, T& _out)
    {
        return CheckTableExists(L, _pszName);
    }

    static bool LoadRawVectorInt(lua_State* L, const char* _pszName, std::vector<int>& _out);

private:
    static bool CheckTableExists(lua_State* L, const char* _pszName)
    {
        if (!L || !_pszName) return false;
        lua_getglobal(L, _pszName);
        bool ok = lua_istable(L, -1);
        lua_pop(L, 1);
        return ok;
    }
};

#endif // _INC_LUADATALOADER_
