// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMServer/GameWorld/ExceptionHandler.h (class StackWalkerLog : public StackWalker)
//   BMClient/Common/ExceptionHandler.h   (same)
//   ExceptionHandler.cpp: StackWalkerLog sw; sw.ShowCallstack(); (implicit)
//   StackWalkerLog::OnOutput(LPCSTR szText) — override that logs the text
//
// StackWalker is a well-known open-source Win32 stack-walking helper by Jochen Kalmbach.
// This is a minimal stub that satisfies the inheritance and virtual override used here.
// For a full implementation see: https://github.com/JochenKalmbach/StackWalker
#pragma once
#ifndef _INC_STACKWALKER_
#define _INC_STACKWALKER_

#ifdef _WIN32
#include <Windows.h>
#else
#include "../platform_compat.h"
// CONTEXT is Windows-specific; stub it for Linux
struct CONTEXT {};
#endif

class StackWalker
{
public:
    enum StackWalkOptions
    {
        RetrieveNone        = 0,
        RetrieveSymbol      = 1,
        RetrieveLine        = 2,
        RetrieveModuleInfo  = 4,
        RetrieveFileVersion = 8,
        OptionsAll          = 0x0F,
    };

    explicit StackWalker(int options = OptionsAll,
                         LPCSTR szSymPath = NULL,
                         DWORD dwProcessId = GetCurrentProcessId(),
                         HANDLE hProcess = GetCurrentProcess());
    virtual ~StackWalker();

    // Walk the call stack of the current thread (or the thread described by
    // _pContext if non-NULL) and call OnOutput for each frame.
    bool ShowCallstack(HANDLE hThread = GetCurrentThread(),
                       const CONTEXT* _pContext = NULL);

protected:
    // Override to receive each line of stack output.
    virtual void OnOutput(LPCSTR szText);

private:
    int    m_options;
    DWORD  m_dwProcessId;
    HANDLE m_hProcess;
};

#endif // _INC_STACKWALKER_
