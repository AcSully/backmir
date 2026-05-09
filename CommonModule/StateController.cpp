// [reconstructed] 重建于 2026-05-06
#include "StateController.h"

StateController::StateController() {}

void StateController::PushItem(int _nEAID, unsigned int _dwDuration, int _nValue)
{
    StateItem item;
    item.nValue     = _nValue;
    item.dwDuration = _dwDuration;
    m_xItems[_nEAID] = item;
}

void StateController::AddItemValueIfExistsForever(int _nEAID, int _nValue)
{
    auto it = m_xItems.find(_nEAID);
    if (it != m_xItems.end() && it->second.dwDuration == STATE_FOREVER)
        it->second.nValue += _nValue;
}

void StateController::ClearForever()
{
    auto it = m_xItems.begin();
    while (it != m_xItems.end())
    {
        if (it->second.dwDuration == STATE_FOREVER)
            it = m_xItems.erase(it);
        else
            ++it;
    }
}

int StateController::GetStateValue(int _nEAID) const
{
    auto it = m_xItems.find(_nEAID);
    return (it != m_xItems.end()) ? it->second.nValue : 0;
}
