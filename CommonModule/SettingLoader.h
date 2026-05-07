// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMClient/BackMir/BackMir.cpp (LoadSetting, SaveToFile, GetIntValue, WriteIntValue)
//   BMServer/GameWorld/GameWorld.cpp (GetInstance, LoadSetting, GetIntValue)
//   BMServer/CMainServer/CMainServer.cpp (GetInstance, Clear, GetIntValue)
//
// INI 格式配置文件读写。使用 SimpleIni 作为后端。
// GetInstance(true) 重置单例（用于服务器热重载）。
#pragma once
#ifndef _INC_SETTINGLOADER_
#define _INC_SETTINGLOADER_

#include <string>

class SettingLoader
{
public:
    // 获取单例；_bReset=true 时销毁旧实例并创建新实例
    static SettingLoader* GetInstance(bool _bReset = false);

    // 从 INI 文件加载配置
    bool LoadSetting(const char* _pszFilePath);

    // 将当前配置写回文件
    bool SaveToFile(const char* _pszFilePath);

    // 清空所有配置项
    void Clear();

    // 读取整型值，键不存在时返回 0
    int GetIntValue(const char* _pszKey) const;

    // 写入整型值
    void WriteIntValue(const char* _pszKey, int _nValue);

private:
    SettingLoader();
    ~SettingLoader();

    struct Impl;
    Impl* m_pImpl;

    static SettingLoader* s_pInstance;
};

#endif // _INC_SETTINGLOADER_
