// [reconstructed] 重建于 2026-05-06
#include "SettingLoader.h"
#include "SimpleIni.h"
#include <string>
#include <map>

struct SettingLoader::Impl
{
    CSimpleIniA ini;
    std::string filePath;
};

SettingLoader* SettingLoader::s_pInstance = NULL;

SettingLoader::SettingLoader()
    : m_pImpl(new Impl())
{
    m_pImpl->ini.SetUnicode(false);
    m_pImpl->ini.SetMultiKey(false);
}

SettingLoader::~SettingLoader()
{
    delete m_pImpl;
}

SettingLoader* SettingLoader::GetInstance(bool _bReset)
{
    if (_bReset)
    {
        delete s_pInstance;
        s_pInstance = NULL;
    }
    if (!s_pInstance)
    {
        s_pInstance = new SettingLoader();
    }
    return s_pInstance;
}

bool SettingLoader::LoadSetting(const char* _pszFilePath)
{
    if (!_pszFilePath)
        return false;
    m_pImpl->filePath = _pszFilePath;
    SI_Error rc = m_pImpl->ini.LoadFile(_pszFilePath);
    return (rc >= 0);
}

bool SettingLoader::SaveToFile(const char* _pszFilePath)
{
    const char* pszPath = (_pszFilePath && _pszFilePath[0]) ? _pszFilePath : m_pImpl->filePath.c_str();
    if (!pszPath || !pszPath[0])
        return false;
    SI_Error rc = m_pImpl->ini.SaveFile(pszPath);
    return (rc >= 0);
}

void SettingLoader::Clear()
{
    m_pImpl->ini.Reset();
    m_pImpl->filePath.clear();
}

int SettingLoader::GetIntValue(const char* _pszKey) const
{
    if (!_pszKey)
        return 0;
    // All keys stored under the default (empty) section
    const char* pszVal = m_pImpl->ini.GetValue("", _pszKey, NULL);
    if (!pszVal)
        return 0;
    return atoi(pszVal);
}

void SettingLoader::WriteIntValue(const char* _pszKey, int _nValue)
{
    if (!_pszKey)
        return;
    char szBuf[32];
    snprintf(szBuf, sizeof(szBuf), "%d", _nValue);
    m_pImpl->ini.SetValue("", _pszKey, szBuf);
}
