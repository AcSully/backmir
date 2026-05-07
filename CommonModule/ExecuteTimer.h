// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMServer/GameWorld/GameScene.cpp (ExecuteTimer xSceneTime; xSceneTime.Start(); xSceneTime.GetExecuteTime())
//   BMServer/GameWorld/HeroObject.cpp (ExecuteTimer xExeTimer; xExeTimer.Start(); xExeTimer.GetExecuteTime())
//
// 简单执行计时器：Start() 记录起始时刻，GetExecuteTime() 返回已过毫秒数。
#pragma once
#ifndef _INC_EXECUTETIMER_
#define _INC_EXECUTETIMER_

#include "platform_compat.h"
#ifdef _WIN32
#  include <windows.h>
#endif

class ExecuteTimer
{
public:
    ExecuteTimer() : m_dwStart(0) {}

    void Start() { m_dwStart = GetTickCount(); }

    unsigned int GetExecuteTime() const
    {
        return GetTickCount() - m_dwStart;
    }

private:
    unsigned int m_dwStart;
};

#endif // _INC_EXECUTETIMER_
