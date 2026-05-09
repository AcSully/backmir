// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   仅 BMServer/BackMirServer13.vcxproj 引用（早期 .vcproj 路径
//   "..\CommonModule\CRCVerifyThread\ThreadRunner.h" 已平铺到顶层）。
//   源码未直接 #include；提供 std::thread 的 RAII 包装，由 CommonModule
//   内部其他文件（如 DBThread 风格的工作线程）使用。
//
// API：Start(callable) / Stop / Join / IsRunning。
// Stop 仅设置 m_bStopFlag，由 callable 自行轮询；不强制中断线程。
#pragma once
#ifndef _INC_THREADRUNNER_
#define _INC_THREADRUNNER_

#include <thread>
#include <atomic>
#include <functional>

class ThreadRunner
{
public:
    ThreadRunner() : m_bStopFlag(false), m_bRunning(false) {}
    ~ThreadRunner() { Join(); }

    ThreadRunner(const ThreadRunner&) = delete;
    ThreadRunner& operator=(const ThreadRunner&) = delete;

    // _func 接受一个 stop_flag 引用，自行决定何时退出
    void Start(std::function<void(const std::atomic<bool>&)> _func)
    {
        if (m_bRunning) return;
        m_bStopFlag = false;
        m_bRunning  = true;
        m_xThread   = std::thread([this, _func]() {
            _func(m_bStopFlag);
            m_bRunning = false;
        });
    }

    void Stop() { m_bStopFlag = true; }

    void Join()
    {
        if (m_xThread.joinable())
            m_xThread.join();
    }

    bool IsRunning() const { return m_bRunning; }

    bool ShouldStop() const { return m_bStopFlag; }

private:
    std::atomic<bool> m_bStopFlag;
    std::atomic<bool> m_bRunning;
    std::thread       m_xThread;
};

#endif // _INC_THREADRUNNER_
