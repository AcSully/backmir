// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMClient/Net/PacketHandler.cpp (Load, WriteHeader, WriteData, ReadHeader, ReadData, GetDataSize, GetHeaderSize, Close)
//   BMClient/GameScene/GamePlayer.cpp (Load(file, MODE_READ), ReadHeader, ReadData, GetDataSize, GetHeaderSize, Close)
//   BMClient/BackMir/LuaClientEngine.cpp (CalcInternalPassword)
//   BMServer/GameWorld/LuaServerEngine.cpp (CalcInternalPassword)
//
// SaveFile 是角色存档文件的读写封装。
// 文件格式：[HeroHeader][compressed data]
// CalcInternalPassword 返回 ZIP 加密密码（固定字符串）。
#pragma once
#ifndef _INC_SAVEFILE_
#define _INC_SAVEFILE_

#include "GamePacket.h"  // HeroHeader

enum SaveFileMode
{
    MODE_READ  = 0,
    MODE_WRITE = 1,
};

class SaveFile
{
public:
    SaveFile();
    ~SaveFile();

    // 打开文件（不带 mode 参数时默认 WRITE）
    bool Load(const char* _pszFile);
    bool Load(const char* _pszFile, SaveFileMode _eMode);

    bool WriteHeader(const HeroHeader* _pHeader);
    bool WriteData(const char* _pData, unsigned int _dwLen);

    bool ReadHeader(HeroHeader* _pHeader);
    bool ReadData(char* _pData, unsigned int _dwLen);

    bool GetDataSize(unsigned int* _pSize);
    bool GetHeaderSize(unsigned int* _pSize);

    void Close();

    // 返回内部 ZIP 加密密码（固定值，用于 LuaEngine/ZipArchive）
    static const char* CalcInternalPassword();

private:
    FILE*        m_pFile;
    SaveFileMode m_eMode;
    bool         m_bOpen;
};

#endif // _INC_SAVEFILE_
