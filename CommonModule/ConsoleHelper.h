// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMServer/GameWorld/ObjectEngine.h (extern g_xConsole)
//   BMServer/CMainServer/CMainServer.cpp (InitConsole, CPrint)
//   BMServer/GameWorld/HeroObject.cpp (CPrint)
//   BMServer/GameWorld/GameScene.cpp (CPrint)
//
// 服务端控制台输出辅助类。
// InitConsole() 分配 Windows 控制台窗口；CPrint() 格式化输出一行。
#pragma once
#ifndef _INC_CONSOLEHELPER_
#define _INC_CONSOLEHELPER_

class ConsoleHelper
{
public:
    ConsoleHelper();
    ~ConsoleHelper();

    // 分配并初始化控制台窗口（仅 Windows）
    void InitConsole();

    // printf 风格输出，自动换行
    void CPrint(const char* _pszFmt, ...);
};

#endif // _INC_CONSOLEHELPER_
