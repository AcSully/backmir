// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMClient/GameDialog/ScriptWnd.h (class WndScriptEngine : public LuaBaseEngine, public LuaBaseExecutor)
//   BMClient/GameDialog/ScriptWnd.cpp (AddCallItem, m_xBaseCallList, LuaBaseCallItem, nCallType, xCallFuncName, dwLastCallTime)
//
// LuaBaseExecutor 维护一个"回调注册表"：
//   - AddCallItem(type, funcName, param) 注册一个 Lua 函数名与回调类型的映射
//   - m_xBaseCallList 供子类遍历，按 nCallType 过滤后调用对应 Lua 函数
#pragma once
#ifndef _INC_LUABASEEXECUTOR_
#define _INC_LUABASEEXECUTOR_

#include <string>
#include <list>
#include "platform_compat.h"
#ifdef _WIN32
#  include <windows.h>
#endif

struct LuaBaseCallItem
{
    int          nCallType;
    std::string  xCallFuncName;
    int          nParam;
    DWORD        dwLastCallTime;

    LuaBaseCallItem()
        : nCallType(0), nParam(0), dwLastCallTime(0) {}
};

typedef std::list<LuaBaseCallItem*> LuaBaseCallList;

class LuaBaseExecutor
{
public:
    LuaBaseExecutor();
    virtual ~LuaBaseExecutor();

    // 注册一个回调项
    void AddCallItem(int _nCallType, const char* _pszFuncName, int _nParam);

    // 清空所有回调项
    void ClearCallItems();

protected:
    LuaBaseCallList m_xBaseCallList;
};

#endif // _INC_LUABASEEXECUTOR_
