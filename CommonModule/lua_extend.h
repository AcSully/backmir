// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   仅 vcxproj 引用，源码未直接 #include。
//   按命名推测：注入若干 C 函数到 lua VM，扩展标准库（如 print 重定向到 glog、
//   字符串处理工具、定时器等）。
#pragma once
#ifndef _INC_LUA_EXTEND_
#define _INC_LUA_EXTEND_

#include "lua_compat.h"

// 在 lua_State 上注册扩展函数集合。返回注入的函数数量。
int RegisterLuaExtend(lua_State* L);

#endif // _INC_LUA_EXTEND_
