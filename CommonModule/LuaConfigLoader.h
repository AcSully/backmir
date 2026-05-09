// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   仅 vcxproj 引用，源码未直接 #include。
//   功能职责：从 lua_State 读取全局配置变量到 C++ 数据结构。
#pragma once
#ifndef _INC_LUACONFIGLOADER_
#define _INC_LUACONFIGLOADER_

#include "lua_compat.h"
#include <string>
#include <vector>

class LuaConfigLoader
{
public:
    static bool LoadInt(lua_State* L, const char* _pszGlobalName, int& _out);
    static bool LoadString(lua_State* L, const char* _pszGlobalName, std::string& _out);
    static bool LoadVectorString(lua_State* L, const char* _pszGlobalName, std::vector<std::string>& _out);
};

#endif // _INC_LUACONFIGLOADER_
