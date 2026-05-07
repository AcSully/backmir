// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMServer/GameWorld/DBThread.cpp (LuaStackGuard guard(L))
//
// RAII 保护 Lua 栈：构造时记录栈顶，析构时恢复，防止函数中途返回导致栈泄漏。
#pragma once
#ifndef _INC_LUASTACKGUARD_
#define _INC_LUASTACKGUARD_

#include "lua_compat.h"

class LuaStackGuard
{
public:
    explicit LuaStackGuard(lua_State* L) : m_L(L), m_nTop(lua_gettop(L)) {}
    ~LuaStackGuard() { lua_settop(m_L, m_nTop); }

private:
    lua_State* m_L;
    int        m_nTop;
};

#endif // _INC_LUASTACKGUARD_
