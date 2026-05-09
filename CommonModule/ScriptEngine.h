// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMClient/BackMir/BackMir.h (GetScriptEngine() -> LuaClientEngine*)
//   BMServer/GameWorld/GameWorld.h (GetLuaEngine() -> LuaServerEngine*)
//
// ScriptEngine 是 LuaBaseEngine 的别名头，保持向后兼容。
// 原始代码中有注释掉的 ScriptEngine* 引用，说明曾有独立的 ScriptEngine 类，
// 后被 LuaBaseEngine 替代。此头文件仅作兼容性 include。
#pragma once
#ifndef _INC_SCRIPTENGINE_
#define _INC_SCRIPTENGINE_

#include "LuaBaseEngine.h"

// 兼容别名
typedef LuaBaseEngine ScriptEngine;

#endif // _INC_SCRIPTENGINE_
