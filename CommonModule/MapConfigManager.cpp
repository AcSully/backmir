#include "MapConfigManager.h"
#include "lua_compat.h"

#include <string.h>

MapConfigManager::MapConfigManager() {}
MapConfigManager::~MapConfigManager() {}

bool MapConfigManager::Init(lua_State* _pL)
{
    if (!_pL) return false;
    // Load map config from lua global "config_maps" table
    lua_getglobal(_pL, "config_maps");
    if (!lua_istable(_pL, -1)) { lua_pop(_pL, 1); return true; } // ok if not present
    lua_pushnil(_pL);
    while (lua_next(_pL, -2) != 0) {
        if (lua_istable(_pL, -1)) {
            LuaMapInfo info;
            memset(&info, 0, sizeof(info));
            lua_getfield(_pL, -1, "id");      info.nMapID = (int)lua_tointeger(_pL, -1); lua_pop(_pL, 1);
            lua_getfield(_pL, -1, "type");    info.nMapType = (int)lua_tointeger(_pL, -1); lua_pop(_pL, 1);
            lua_getfield(_pL, -1, "resid");   info.nResID = (int)lua_tointeger(_pL, -1); lua_pop(_pL, 1);
            lua_getfield(_pL, -1, "name");    const char* n = lua_tostring(_pL, -1); if (n) strncpy(info.szMapChName, n, 63); lua_pop(_pL, 1);
            lua_getfield(_pL, -1, "resfile"); const char* r = lua_tostring(_pL, -1); if (r) strncpy(info.szMapResFile, r, 259); lua_pop(_pL, 1);
            m_xMap[info.nMapID] = info;
            if (info.nMapType == 0) m_xFixedMaps.push_back(info.nMapID);
        }
        lua_pop(_pL, 1);
    }
    lua_pop(_pL, 1);
    return true;
}

const LuaMapInfo* MapConfigManager::GetLuaMapInfo(int _nMapID) const
{
    auto it = m_xMap.find(_nMapID);
    return (it == m_xMap.end()) ? nullptr : &it->second;
}

void MapConfigManager::Insert(const LuaMapInfo& _info)
{
    m_xMap[_info.nMapID] = _info;
    if (_info.nMapType == 0) m_xFixedMaps.push_back(_info.nMapID);
}

void MapConfigManager::Clear()
{
    m_xMap.clear();
    m_xFixedMaps.clear();
}
