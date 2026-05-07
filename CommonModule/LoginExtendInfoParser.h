// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMServer/CMainServer/CMainServer.cpp:1564-1645
//   BMServer/CMainServer/CMainServer_Deprecated.cpp:37-209
//
// 用于解析登录服务器下发的玩家扩展数据（捐赠值、礼包列表等）。
// 输入：原始字节缓冲（cJSON 文本或自定义二进制）。
// 调用顺序：构造(NULL) -> SetContent(buf) -> Parse() -> Get*().
#pragma once
#ifndef _INC_LOGINEXTENDINFOPARSER_
#define _INC_LOGINEXTENDINFOPARSER_

#include <vector>

class LoginExtendInfoParser
{
public:
    explicit LoginExtendInfoParser(const char* _pContent);
    ~LoginExtendInfoParser();

    void SetContent(const char* _pContent);
    bool Parse();

    int  GetDonateMoney() const { return m_nDonateMoney; }
    int  GetDonateLeft()  const { return m_nDonateLeft; }
    int  GetGiftCount()   const { return (int)m_vecGiftIds.size(); }
    int  GetGiftID(int _i) const
    {
        return (_i >= 0 && _i < (int)m_vecGiftIds.size()) ? m_vecGiftIds[_i] : 0;
    }

private:
    const char*       m_pContent;
    int               m_nDonateMoney;
    int               m_nDonateLeft;
    std::vector<int>  m_vecGiftIds;
};

#endif // _INC_LOGINEXTENDINFOPARSER_
