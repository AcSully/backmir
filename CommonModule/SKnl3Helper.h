// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMServer/BackMirServer13.vcxproj 引用 ..\CommonModule\SKnl3Helper.{cpp,h}
//   BMClient 自有 BMClient/Common/SKnl3Helper.{cpp,h}（PE/进程权限/Token 工具，
//   含 HANDLE/TlHelp32 等纯 Win32 API；用于客户端 anti-cheat / 反调试集成）。
//
// BMServer 引用此文件大概是因为某些反作弊检测需要在服务端镜像声明同名函数；
// 实际 BMServer 不会调用（或仅条件编译调用）。
//
// 本文件提供 Windows 下与 BMClient/Common/SKnl3Helper.h 兼容的最小声明集。
// Linux 下整个文件在 #ifdef _WIN32 内编译，避免拉入 windows.h。
#pragma once
#ifndef _INC_SKNL3HELPER_COMMONMODULE_
#define _INC_SKNL3HELPER_COMMONMODULE_

#ifdef _WIN32
#  include <Windows.h>
#  include <TlHelp32.h>

bool  SKNL3EnableCurrentDbgPrivilege(bool _bEnable);
DWORD SKNL3GetProcessPID(LPCTSTR _lpszProcessName);
#endif // _WIN32

#endif // _INC_SKNL3HELPER_COMMONMODULE_
