// LuaIterator.h - Lua table iteration helper
#pragma once
#ifndef _INC_LUAITERATOR_
#define _INC_LUAITERATOR_

#include "lua_compat.h"

// RAII helper: pushes nil on construction for lua_next iteration;
// cleans up on destruction.
// Usage:
//   lua_getglobal(L, "tbl");
//   for (LuaIterator it(L); it.Next(); ) {
//       // stack: ..., key(-2), value(-1)
//   }
//   lua_pop(L, 1);  // pop tbl
class LuaIterator
{
public:
    explicit LuaIterator(lua_State* _L) : m_pL(_L), m_bStarted(false) {}

    bool Next()
    {
        if (!m_bStarted) { lua_pushnil(m_pL); m_bStarted = true; }
        else             { lua_pop(m_pL, 1); }
        return lua_next(m_pL, -2) != 0;
    }

private:
    lua_State* m_pL;
    bool       m_bStarted;
};

#endif // _INC_LUAITERATOR_
