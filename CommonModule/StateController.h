// [reconstructed] StateController manages permanent states (equipment/suit bonuses).
#pragma once
#ifndef _INC_STATECONTROLLER_
#define _INC_STATECONTROLLER_

#include <map>
#include "item_extra_suit_def.h"

#define STATE_FOREVER 0xFFFFFFFF

class StateController
{
public:
    StateController();

    void PushItem(int _nEAID, unsigned int _dwDuration, int _nValue);
    void AddItemValueIfExistsForever(int _nEAID, int _nValue);
    void ClearForever();
    int GetStateValue(int _nEAID) const;
    void Update() {}

    int GetIgnoreACAddition()      const { return GetStateValue(EAID_IGNOREAC); }
    int GetMagicItemAddition()     const { return GetStateValue(EAID_MAGICITEM); }
    int GetMovePosAddition()       const { return GetStateValue(EAID_MOVEPOS); }
    int GetHurtTransAddition()     const { return GetStateValue(EAID_HURTTRANS); }
    int GetDefStruckAddition()     const { return GetStateValue(EAID_DCDEFENSE); }
    int GetNearPalsyAddition()     const { return GetStateValue(EAID_NEARPALSY); }
    int GetFarPalsyAddtion()       const { return GetStateValue(EAID_FARPALSY); }
    int GetAddShenShouAddition()   const { return GetStateValue(EAID_SUMMONWHITETIGER); }
    int GetAddIceRoarAddition()    const { return GetStateValue(EAID_MOUNTAIN); }
    int GetAddLieHuoAddition()     const { return GetStateValue(EAID_MCDAMAGE); }
    int GetAddSkyFireAddition()    const { return GetStateValue(EAID_SCDAMAGE); }
    int GetAddTigerAddition()      const { return GetStateValue(EAID_SUMMONWHITETIGER); }
    int GetAddSLieHuoAddition()    const { return GetStateValue(EAID_DCDAMAGE); }

private:
    struct StateItem
    {
        int          nValue;
        unsigned int dwDuration;
    };
    std::map<int, StateItem> m_xItems;
};

#endif // _INC_STATECONTROLLER_
