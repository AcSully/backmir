// [reconstructed] 重建于 2026-05-06
// 与 LuaBaseEngine.cpp 配套；仅在此 TU 中实现路径相关方法，
// 避免与 LuaBaseEngine.cpp 中已有的 DoModule/LoadFile/LoadFileInZip 重复定义。
//
// vcxproj 把 LuaBaseEngine 的实现拆成了 .cpp / _Dispatcher.cpp / _ScriptLoader.cpp
// 三个 TU；用户生成的 LuaBaseEngine.cpp 已含主要逻辑，本 TU 与
// _Dispatcher.cpp 仅承载补丁方法以满足 vcxproj 的 ClCompile 列表。
#include "LuaBaseEngine.h"
#include <lualib.h>
#include <lauxlib.h>
#include <cstring>

void LuaBaseEngine::SetModulePath(const char* _pszPath, LuaLoadMode _eMode)
{
    if (_pszPath) m_xModulePath = _pszPath;
    else          m_xModulePath.clear();
    m_eLoadMode = _eMode;
}

void LuaBaseEngine::SetLuaLoadPath(const char* _pszPath)
{
    if (!m_pState || !_pszPath) return;
    // 在 lua 全局 package.path 后追加 "<path>/?.lua"
    lua_getglobal(m_pState, "package");
    if (lua_istable(m_pState, -1))
    {
        lua_getfield(m_pState, -1, "path");
        const char* pCur = lua_tostring(m_pState, -1);
        std::string sNew;
        if (pCur && pCur[0] != '\0')
        {
            sNew = pCur;
            sNew += ";";
        }
        sNew += _pszPath;
        sNew += "/?.lua";
        lua_pop(m_pState, 1);
        lua_pushstring(m_pState, sNew.c_str());
        lua_setfield(m_pState, -2, "path");
    }
    lua_pop(m_pState, 1);
}
