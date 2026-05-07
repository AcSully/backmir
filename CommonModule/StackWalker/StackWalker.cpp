// StackWalker.cpp - Stack walking helper (stub)
#include "StackWalker.h"

StackWalker::StackWalker(int options, LPCSTR szSymPath, DWORD dwProcessId, HANDLE hProcess)
    : m_options(options)
    , m_dwProcessId(dwProcessId)
    , m_hProcess(hProcess)
{
    (void)szSymPath;
}

StackWalker::~StackWalker()
{
}

bool StackWalker::ShowCallstack(HANDLE hThread, const CONTEXT* _pContext)
{
    (void)hThread;
    (void)_pContext;
    // Stub: no-op on both platforms
    return true;
}

void StackWalker::OnOutput(LPCSTR szText)
{
    (void)szText;
    // Stub: no-op
}
