// [reconstructed] 重建于 2026-05-06
#include "platform_compat.h"
#include "CollDownController.h"

CoolDownController::CoolDownController() {}

bool CoolDownController::PushItem(int _nID, unsigned int _dwDelayMS)
{
    unsigned int now = GetTickCount();
    auto it = m_xItems.find(_nID);
    if (it != m_xItems.end())
    {
        if (now < it->second.dwStartTick + it->second.dwDelayMS)
            return false;  // still cooling
    }
    CoolItem item;
    item.dwStartTick = now;
    item.dwDelayMS   = _dwDelayMS;
    m_xItems[_nID]   = item;
    return true;
}

bool CoolDownController::CanUse(int _nID, unsigned int _dwDelayMS) const
{
    unsigned int now = GetTickCount();
    auto it = m_xItems.find(_nID);
    if (it == m_xItems.end())
        return true;
    return (now >= it->second.dwStartTick + _dwDelayMS);
}

void CoolDownController::Update()
{
    unsigned int now = GetTickCount();
    auto it = m_xItems.begin();
    while (it != m_xItems.end())
    {
        if (now >= it->second.dwStartTick + it->second.dwDelayMS)
            it = m_xItems.erase(it);
        else
            ++it;
    }
}

void CoolDownController::Clear()
{
    m_xItems.clear();
}

int CoolDownController::GetCoolPercent(int _nID) const
{
    unsigned int now = GetTickCount();
    auto it = m_xItems.find(_nID);
    if (it == m_xItems.end())
        return 100;
    unsigned int elapsed = now - it->second.dwStartTick;
    if (elapsed >= it->second.dwDelayMS)
        return 100;
    return (int)(elapsed * 100 / it->second.dwDelayMS);
}
