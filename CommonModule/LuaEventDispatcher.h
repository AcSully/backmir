// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMServer/GameWorld/WorldEventDispatcher.h: class WorldEventDispatcher : public LuaEventDispatcher
//     ↑ 整个 WorldEventDispatcher.h 当前被 /* */ 注释包裹（dead code），
//     说明 LuaEventDispatcher 这条事件分发链路在最终版本中已停用。
//
// 此处仍提供最小骨架，使若有 .cpp 启用了上述被注释代码也能通过编译。
#pragma once
#ifndef _INC_LUAEVENTDISPATCHER_
#define _INC_LUAEVENTDISPATCHER_

#include "LuaBaseEngine.h"

class LuaEventDispatcher
{
public:
    LuaEventDispatcher() {}
    virtual ~LuaEventDispatcher() {}

    virtual int  OnDispatchEvent(const LuaDispatchEvent* _pEvent, LuaDispatchInfo* _pInfo) { return 0; }
    virtual void OnDispatchEventResult(const LuaDispatchEvent* _pEvent, bool _bResult) {}
};

#endif // _INC_LUAEVENTDISPATCHER_
