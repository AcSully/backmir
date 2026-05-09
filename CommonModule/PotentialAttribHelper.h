// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMServer/GameWorld/HeroObject.cpp
//   BMServer/GameWorld/HeroObject_Packet.cpp
//
// Potential attrib data is packed into a DWORD (ItemAttrib::MP):
//   bits 0-7  : potential index (which attrib type is active)
//   bits 8-15 : potential offset (sub-index within type)
//   bits 16-31: potential time (remaining duration in ticks)
#pragma once
#ifndef _INC_POTENTIALATTRIBHELPER_
#define _INC_POTENTIALATTRIBHELPER_

#define MAX_POTENTIAL_TIME 100

class PotentialAttribHelper
{
public:
    static int  GetPotentialIndex(unsigned int _dwData)  { return (int)(_dwData & 0xFF); }
    static int  GetPotentialOffset(unsigned int _dwData) { return (int)((_dwData >> 8) & 0xFF); }
    static int  GetPotentialTime(unsigned int _dwData)   { return (int)((_dwData >> 16) & 0xFFFF); }

    static void SetPotentialIndex(unsigned int& _dwData, int _v)
    {
        _dwData = (_dwData & ~0xFF) | ((unsigned int)_v & 0xFF);
    }
    static void SetPotentialTime(unsigned int& _dwData, int _v)
    {
        _dwData = (_dwData & 0x0000FFFF) | (((unsigned int)_v & 0xFFFF) << 16);
    }

    // Validation test
    static bool Test()
    {
        unsigned int dwData = 0;
        SetPotentialIndex(dwData, 5);
        SetPotentialTime(dwData, 100);
        return GetPotentialIndex(dwData) == 5 && GetPotentialTime(dwData) == 100;
    }
};

#endif // _INC_POTENTIALATTRIBHELPER_
