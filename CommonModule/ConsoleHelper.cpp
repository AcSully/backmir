// [reconstructed] 重建于 2026-05-06
#include "ConsoleHelper.h"
#include "platform_compat.h"
#ifdef _WIN32
#  include <windows.h>
#endif
#include <stdio.h>
#include <stdarg.h>

ConsoleHelper::ConsoleHelper()
{
}

ConsoleHelper::~ConsoleHelper()
{
}

void ConsoleHelper::InitConsole()
{
#ifdef _WIN32
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
#endif
}

void ConsoleHelper::CPrint(const char* _pszFmt, ...)
{
    if (!_pszFmt)
        return;

    char szBuf[2048];
    va_list args;
    va_start(args, _pszFmt);
    vsnprintf(szBuf, sizeof(szBuf) - 1, _pszFmt, args);
    va_end(args);
    szBuf[sizeof(szBuf) - 1] = '\0';

    printf("%s\n", szBuf);
}
