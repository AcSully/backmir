// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMClient/BackMir/LuaClientEngine.h (class LuaClientEngine : public LuaBaseEngine)
//   BMServer/GameWorld/LuaServerEngine.h (class LuaServerEngine : public LuaBaseEngine)
//   BMClient/GameDialog/ScriptWnd.h (class WndScriptEngine : public LuaBaseEngine, public LuaBaseExecutor)
//   BMServer/GameWorld/GameWorld.h (m_xScript.Create/DoModule/LoadFile/GetVM/DispatchEvent)
//   BMServer/GameWorld/GameScene.cpp (m_xScript.Create/DoModule/LoadFile/GetVM)
//   BMClient/BackMir/LuaClientEngine.cpp (SetZipPassword, m_eFileExt, LoadFileInZip, PushInt)
//   BMServer/GameWorld/LuaServerEngine.cpp (SetZipPassword, m_eFileExt, LoadFileInZip, LoadFile, PushInt, GetVM)
//
// LuaBaseEngine 封装一个 Lua VM 实例，提供：
//   - Create()        : 创建 lua_State，注册基础库
//   - DoModule()      : 加载并执行 .lua/.bjt 模块文件
//   - LoadFile()      : 加载并执行单个文件
//   - LoadFileInZip() : 从 ZIP 包中加载并执行文件
//   - GetVM()         : 返回底层 lua_State*
//   - PushInt/PushString/PushFloat : 向 Lua 栈压值
//   - DispatchEvent() : 触发 Lua 事件回调
//   - Log()           : 格式化日志（调用虚函数 Output）
//   - Output()        : 纯虚，子类实现日志输出
//   - OnDispatchEvent/OnDispatchEventResult : 纯虚，子类实现事件参数推送
#pragma once
#ifndef _INC_LUABASEENGINE_
#define _INC_LUABASEENGINE_

#include "lua_compat.h"


#include <string>

// ---------------------------------------------------------------------------
// Lua 事件分发结构
// ---------------------------------------------------------------------------
struct LuaDispatchEvent
{
    int   nEventId;
    void* pEvent;
};

struct LuaDispatchInfo
{
    int nArgs;      // 子类在 OnDispatchEvent 中设置的参数个数
    int nResults;   // 期望返回值个数（默认 0）

    LuaDispatchInfo() : nArgs(0), nResults(0) {}
};

// ---------------------------------------------------------------------------
// Lua 文件扩展名枚举
// ---------------------------------------------------------------------------
enum LuaFileExt
{
    kLuaFileExt_Lua = 0,    // .lua  (debug)
    kLuaFileExt_Bjt = 1,    // .bjt  (release, 加密/压缩)
};

// ---------------------------------------------------------------------------
// 模块加载模式（与 SetModulePath 配合）
//   LOADMODE_PATH : 直接从文件系统目录加载
//   LOADMODE_ZIP  : 从一个 zip 包中加载
// ---------------------------------------------------------------------------
enum LuaLoadMode
{
    LOADMODE_PATH = 0,
    LOADMODE_ZIP  = 1,
};

// ---------------------------------------------------------------------------
// LuaBaseEngine
// ---------------------------------------------------------------------------
class LuaBaseEngine
{
public:
    LuaBaseEngine();
    virtual ~LuaBaseEngine();

    // 创建 Lua VM，注册标准库；返回 false 表示失败
    bool Create();

    // 关闭并释放 Lua VM
    void Destroy();

    // 加载并执行模块文件（路径不含扩展名，由 m_eFileExt 决定后缀）
    bool DoModule(const char* _pszModuleFile);

    // 加载并执行单个文件（完整路径）
    bool LoadFile(const char* _pszFilePath);

    // 从 ZIP 包中加载并执行文件
    bool LoadFileInZip(const char* _pszZipFile, const char* _pszSubFile, const char* _pszPassword);

    // 返回底层 lua_State*
    lua_State* GetVM();

    // 向 Lua 栈压值
    void PushInt(int _nValue);
    void PushString(const char* _pszValue);
    void PushFloat(float _fValue);

    // 触发 Lua 事件：调用 OnDispatchEvent 推参数，再 pcall 全局函数 "OnEvent"
    void DispatchEvent(int _nEventId, void* _pEvent);

    // 格式化日志，调用 Output
    void Log(const char* _pszFmt, ...);

    // 将引擎自身以 "LuaBaseEngine" 类型推入 Lua 全局变量 "ENGINE"
    void PushEngine();

    // 设置 ZIP 解密密码
    void SetZipPassword(const char* _pszPassword);

    // 设置模块根路径（DoModule 拼接子模块名时使用）
    void SetModulePath(const char* _pszPath, LuaLoadMode _eMode = LOADMODE_PATH);

    // 把 _pszPath 加入 lua 的 package.path，便于脚本 require
    void SetLuaLoadPath(const char* _pszPath);

    // ---------------------------------------------------------------------------
    // 纯虚接口，子类实现
    // ---------------------------------------------------------------------------
    virtual void Output(const char* _pszLog) = 0;

    virtual int  OnDispatchEvent(const LuaDispatchEvent* _pEvent, LuaDispatchInfo* _pInfo) { return 0; }
    virtual void OnDispatchEventResult(const LuaDispatchEvent* _pEvent, bool bResult) {}

protected:
    lua_State*   L;             // Lua VM（别名，与 m_pState 相同）
    lua_State*   m_pState;
    LuaFileExt   m_eFileExt;
    std::string  m_xZipPassword;
    std::string  m_xModulePath;
    LuaLoadMode  m_eLoadMode;
};

#endif // _INC_LUABASEENGINE_
