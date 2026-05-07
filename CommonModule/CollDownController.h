// CollDownController.h - Cooldown controller
// Records last-use timestamp per ID, checks if cooldown has expired.
#pragma once
#ifndef _INC_COLLDOWNCONTROLLER_
#define _INC_COLLDOWNCONTROLLER_

#ifdef _WIN32
#include <windows.h>
#endif
#include <map>

class CoolDownController
{
public:
    CoolDownController();

    // Record cooldown start for _nID with _dwDelayMS duration.
    // Returns false if still cooling down.
    bool PushItem(int _nID, unsigned int _dwDelayMS);

    // Check if _nID can be used (cooldown expired)
    bool CanUse(int _nID, unsigned int _dwDelayMS) const;

    // Update (remove expired cooldowns)
    void Update();

    // Clear all cooldowns
    void Clear();

private:
    struct CoolItem
    {
        unsigned int dwStartTick;
        unsigned int dwDelayMS;
    };
    std::map<int, CoolItem> m_xItems;
};

#endif // _INC_COLLDOWNCONTROLLER_
