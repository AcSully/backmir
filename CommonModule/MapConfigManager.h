#pragma once
#ifndef _INC_MAPCONFIGMANAGER_
#define _INC_MAPCONFIGMANAGER_

#include <map>
#include <vector>
#include <string>

struct lua_State;

struct LuaMapInfo
{
    int         nMapID;
    int         nMapType;       // 0=normal, 1=instance
    int         nResID;         // resource/map file ID
    char        szMapChName[64];
    char        szMapResFile[260];
};

class MapConfigManager
{
public:
    MapConfigManager();
    ~MapConfigManager();

    bool Init(lua_State* _pL);

    const LuaMapInfo* GetLuaMapInfo(int _nMapID) const;
    const std::vector<int>& GetFixedMaps() const { return m_xFixedMaps; }

    void Insert(const LuaMapInfo& _info);
    void Clear();

private:
    std::map<int, LuaMapInfo> m_xMap;
    std::vector<int>          m_xFixedMaps;
};

MapConfigManager& GetMapConfigManager();

#endif // _INC_MAPCONFIGMANAGER_
