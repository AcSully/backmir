// [reconstructed] 重建于 2026-05-06
#include "LuaBaseEngine.h"
#include "platform_compat.h"
#include <cstdio>
#include <cstdarg>
#include <cstring>

// tolua++ runtime
#include <tolua++.h>

// ZIP support: ZipArchive on Windows, stub on Linux (Phase 2.3 will add minizip)
#ifdef _WIN32
#include <ZipArchive.h>
#endif

LuaBaseEngine::LuaBaseEngine()
    : L(NULL), m_pState(NULL), m_eFileExt(kLuaFileExt_Lua)
{
}

LuaBaseEngine::~LuaBaseEngine()
{
    Destroy();
}

bool LuaBaseEngine::Create()
{
    Destroy();
    m_pState = luaL_newstate();
    if (!m_pState)
        return false;
    L = m_pState;
    luaL_openlibs(m_pState);
    return true;
}

void LuaBaseEngine::Destroy()
{
    if (m_pState)
    {
        lua_close(m_pState);
        m_pState = NULL;
        L = NULL;
    }
}

bool LuaBaseEngine::DoModule(const char* _pszModuleFile)
{
    if (!m_pState || !_pszModuleFile)
        return false;

    const char* pszExt = (m_eFileExt == kLuaFileExt_Bjt) ? ".bjt" : ".lua";
    char szPath[512];
    snprintf(szPath, sizeof(szPath), "%s%s", _pszModuleFile, pszExt);

    int nRet = luaL_dofile(m_pState, szPath);
    if (nRet != 0)
    {
        const char* pszErr = lua_tostring(m_pState, -1);
        Log("DoModule failed [%s]: %s", szPath, pszErr ? pszErr : "unknown");
        lua_pop(m_pState, 1);
        return false;
    }
    return true;
}

bool LuaBaseEngine::LoadFile(const char* _pszFilePath)
{
    if (!m_pState || !_pszFilePath)
        return false;

    int nRet = luaL_dofile(m_pState, _pszFilePath);
    if (nRet != 0)
    {
        const char* pszErr = lua_tostring(m_pState, -1);
        Log("LoadFile failed [%s]: %s", _pszFilePath, pszErr ? pszErr : "unknown");
        lua_pop(m_pState, 1);
        return false;
    }
    return true;
}

bool LuaBaseEngine::LoadFileInZip(const char* _pszZipFile, const char* _pszSubFile, const char* _pszPassword)
{
#ifdef _WIN32
    if (!m_pState || !_pszZipFile || !_pszSubFile)
        return false;

    CZipArchive zip;
    try
    {
        zip.Open(_pszZipFile, CZipArchive::zipOpenReadOnly);
    }
    catch (...)
    {
        Log("LoadFileInZip: cannot open zip [%s]", _pszZipFile);
        return false;
    }

    ZIP_INDEX_TYPE nIdx = zip.FindFile(_pszSubFile);
    if (nIdx == ZIP_FILE_INDEX_NOT_FOUND)
    {
        Log("LoadFileInZip: file [%s] not found in [%s]", _pszSubFile, _pszZipFile);
        zip.Close();
        return false;
    }

    CZipFileHeader header;
    zip.GetFileInfo(header, nIdx);
    DWORD dwSize = header.m_uUncomprSize;

    char* pBuf = new char[dwSize + 1];
    pBuf[dwSize] = '\0';

    CZipMemFile mf;
    if (_pszPassword && _pszPassword[0])
        zip.SetPassword(_pszPassword);
    zip.ExtractFile(nIdx, mf);
    mf.SeekToBegin();
    mf.Read(pBuf, dwSize);
    zip.Close();

    int nRet = luaL_loadbuffer(m_pState, pBuf, dwSize, _pszSubFile);
    delete[] pBuf;

    if (nRet != 0)
    {
        const char* pszErr = lua_tostring(m_pState, -1);
        Log("LoadFileInZip loadbuffer failed [%s]: %s", _pszSubFile, pszErr ? pszErr : "unknown");
        lua_pop(m_pState, 1);
        return false;
    }

    nRet = lua_pcall(m_pState, 0, LUA_MULTRET, 0);
    if (nRet != 0)
    {
        const char* pszErr = lua_tostring(m_pState, -1);
        Log("LoadFileInZip pcall failed [%s]: %s", _pszSubFile, pszErr ? pszErr : "unknown");
        lua_pop(m_pState, 1);
        return false;
    }
    return true;
#else
    // TODO Phase 2.3: implement via minizip
    (void)_pszZipFile; (void)_pszSubFile; (void)_pszPassword;
    Log("LoadFileInZip: not implemented on this platform");
    return false;
#endif
}

lua_State* LuaBaseEngine::GetVM()
{
    return m_pState;
}

void LuaBaseEngine::PushInt(int _nValue)
{
    if (m_pState)
        lua_pushinteger(m_pState, _nValue);
}

void LuaBaseEngine::PushString(const char* _pszValue)
{
    if (m_pState)
        lua_pushstring(m_pState, _pszValue ? _pszValue : "");
}

void LuaBaseEngine::PushFloat(float _fValue)
{
    if (m_pState)
        lua_pushnumber(m_pState, (lua_Number)_fValue);
}

void LuaBaseEngine::DispatchEvent(int _nEventId, void* _pEvent)
{
    if (!m_pState)
        return;

    LuaDispatchEvent evt;
    evt.nEventId = _nEventId;
    evt.pEvent   = _pEvent;

    LuaDispatchInfo info;

    // Let subclass push arguments
    OnDispatchEvent(&evt, &info);

    // Call global "OnEvent" with the pushed args
    lua_getglobal(m_pState, "OnEvent");
    if (!lua_isfunction(m_pState, -1))
    {
        lua_pop(m_pState, 1 + info.nArgs);
        return;
    }

    // Move function before args: rotate stack
    // Stack: [arg1..argN, func] -> [func, arg1..argN]
    if (info.nArgs > 0)
        lua_insert(m_pState, -(info.nArgs + 1));

    int nRet = lua_pcall(m_pState, info.nArgs, info.nResults, 0);
    bool bOk = (nRet == 0);
    if (!bOk)
    {
        const char* pszErr = lua_tostring(m_pState, -1);
        Log("DispatchEvent[%d] error: %s", _nEventId, pszErr ? pszErr : "unknown");
        lua_pop(m_pState, 1);
    }

    OnDispatchEventResult(&evt, bOk);
}

void LuaBaseEngine::Log(const char* _pszFmt, ...)
{
    if (!_pszFmt)
        return;
    char szBuf[2048];
    va_list args;
    va_start(args, _pszFmt);
    vsnprintf(szBuf, sizeof(szBuf) - 1, _pszFmt, args);
    va_end(args);
    szBuf[sizeof(szBuf) - 1] = '\0';
    Output(szBuf);
}

void LuaBaseEngine::SetZipPassword(const char* _pszPassword)
{
    m_xZipPassword = _pszPassword ? _pszPassword : "";
}

void LuaBaseEngine::PushEngine()
{
    if (!m_pState)
        return;
    tolua_pushusertype(m_pState, this, "LuaBaseEngine");
    lua_setglobal(m_pState, "ENGINE");
}
