// [reconstructed] 重建于 2026-05-06
// 实现使用 cJSON 解析；输入格式约定（来自 loginsvr.proto MPlayerLoginHumDataNtf.jsondata）：
//   { "donate_money": int, "donate_left": int, "gift_ids": [int, int, ...] }
// 历史格式可能不同；此处选 JSON 是为了和 cJSON 已就位的依赖匹配。
#include "LoginExtendInfoParser.h"
#include "cJSON.h"
#include <cstring>

LoginExtendInfoParser::LoginExtendInfoParser(const char* _pContent)
    : m_pContent(_pContent)
    , m_nDonateMoney(0)
    , m_nDonateLeft(0)
{
}

LoginExtendInfoParser::~LoginExtendInfoParser()
{
}

void LoginExtendInfoParser::SetContent(const char* _pContent)
{
    m_pContent = _pContent;
    m_nDonateMoney = 0;
    m_nDonateLeft  = 0;
    m_vecGiftIds.clear();
}

bool LoginExtendInfoParser::Parse()
{
    if (!m_pContent || std::strlen(m_pContent) == 0)
        return false;

    cJSON* pRoot = cJSON_Parse(m_pContent);
    if (!pRoot) return false;

    cJSON* pDM = cJSON_GetObjectItem(pRoot, "donate_money");
    if (pDM && pDM->type == cJSON_Number)
        m_nDonateMoney = (int)pDM->valueint;

    cJSON* pDL = cJSON_GetObjectItem(pRoot, "donate_left");
    if (pDL && pDL->type == cJSON_Number)
        m_nDonateLeft = (int)pDL->valueint;

    cJSON* pGifts = cJSON_GetObjectItem(pRoot, "gift_ids");
    if (pGifts && pGifts->type == cJSON_Array)
    {
        int n = cJSON_GetArraySize(pGifts);
        m_vecGiftIds.reserve(n);
        for (int i = 0; i < n; ++i)
        {
            cJSON* pIt = cJSON_GetArrayItem(pGifts, i);
            if (pIt && pIt->type == cJSON_Number)
                m_vecGiftIds.push_back((int)pIt->valueint);
        }
    }

    cJSON_Delete(pRoot);
    return true;
}
