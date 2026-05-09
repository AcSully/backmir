// [reconstructed] 重建于 2026-05-06
// Linux 下整个 TU 为空，避免 windows.h 依赖。
// Windows 下提供最小可用实现，与 BMClient/Common/SKnl3Helper.cpp 不冲突。
#include "SKnl3Helper.h"

#ifdef _WIN32
#include <cstring>

bool SKNL3EnableCurrentDbgPrivilege(bool _bEnable)
{
    HANDLE hToken = NULL;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
        return false;

    LUID luid;
    if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid))
    {
        CloseHandle(hToken);
        return false;
    }

    TOKEN_PRIVILEGES tp;
    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = _bEnable ? SE_PRIVILEGE_ENABLED : 0;

    BOOL bOk = AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
    CloseHandle(hToken);
    return bOk == TRUE;
}

DWORD SKNL3GetProcessPID(LPCTSTR _lpszProcessName)
{
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap == INVALID_HANDLE_VALUE) return 0;

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(pe);
    DWORD dwPid = 0;
    if (Process32First(hSnap, &pe))
    {
        do {
            if (lstrcmpi(pe.szExeFile, _lpszProcessName) == 0)
            {
                dwPid = pe.th32ProcessID;
                break;
            }
        } while (Process32Next(hSnap, &pe));
    }
    CloseHandle(hSnap);
    return dwPid;
}

#endif // _WIN32
