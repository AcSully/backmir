// [reconstructed] ÖØ½¨ÓÚ 2026-05-06
#include "SaveFile.h"
#include <cstring>
#include <cstdio>

static const char kInternalPassword[] = "BackMIR_SaveFile_2014";

SaveFile::SaveFile()
    : m_pFile(nullptr), m_eMode(MODE_WRITE), m_bOpen(false)
{
}

SaveFile::~SaveFile()
{
    Close();
}

bool SaveFile::Load(const char* _pszFile)
{
    return Load(_pszFile, MODE_WRITE);
}

bool SaveFile::Load(const char* _pszFile, SaveFileMode _eMode)
{
    Close();
    m_eMode = _eMode;
    const char* szMode = (_eMode == MODE_READ) ? "rb" : "wb";
    m_pFile = fopen(_pszFile, szMode);
    if (!m_pFile) return false;
    m_bOpen = true;
    return true;
}

bool SaveFile::WriteHeader(const HeroHeader* _pHeader)
{
    if (!m_bOpen || m_eMode != MODE_WRITE || !_pHeader) return false;
    return fwrite(_pHeader, sizeof(HeroHeader), 1, m_pFile) == 1;
}

bool SaveFile::WriteData(const char* _pData, unsigned int _dwLen)
{
    if (!m_bOpen || m_eMode != MODE_WRITE || !_pData) return false;
    if (fwrite(&_dwLen, sizeof(_dwLen), 1, m_pFile) != 1) return false;
    return fwrite(_pData, 1, _dwLen, m_pFile) == (size_t)_dwLen;
}

bool SaveFile::ReadHeader(HeroHeader* _pHeader)
{
    if (!m_bOpen || m_eMode != MODE_READ || !_pHeader) return false;
    return fread(_pHeader, sizeof(HeroHeader), 1, m_pFile) == 1;
}

bool SaveFile::ReadData(char* _pData, unsigned int _dwLen)
{
    if (!m_bOpen || m_eMode != MODE_READ || !_pData) return false;
    unsigned int uStored = 0;
    if (fread(&uStored, sizeof(uStored), 1, m_pFile) != 1) return false;
    if (uStored != _dwLen) return false;
    return fread(_pData, 1, _dwLen, m_pFile) == (size_t)_dwLen;
}

bool SaveFile::GetDataSize(unsigned int* _pSize)
{
    if (!m_bOpen || !_pSize) return false;
    long lCur = ftell(m_pFile);
    fseek(m_pFile, (long)sizeof(HeroHeader), SEEK_SET);
    unsigned int uLen = 0;
    bool bOk = fread(&uLen, sizeof(uLen), 1, m_pFile) == 1;
    fseek(m_pFile, lCur, SEEK_SET);
    if (bOk) *_pSize = uLen;
    return bOk;
}

bool SaveFile::GetHeaderSize(unsigned int* _pSize)
{
    if (!_pSize) return false;
    *_pSize = (unsigned int)sizeof(HeroHeader);
    return true;
}

void SaveFile::Close()
{
    if (m_pFile)
    {
        fclose(m_pFile);
        m_pFile = nullptr;
    }
    m_bOpen = false;
}

const char* SaveFile::CalcInternalPassword()
{
    return kInternalPassword;
}
