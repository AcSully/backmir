// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMServer/GameWorld/HeroObject.cpp (GetGrowLevelFromDWORD, GetIncGrowDWORD)
#pragma once
#ifndef _INC_ITEMGROWUTILS_
#define _INC_ITEMGROWUTILS_

// Weapon grow data is packed into a DWORD:
//   high 16 bits: grow level (0-based)
//   low  16 bits: grow exp within current level
inline int GetGrowLevelFromDWORD(unsigned int _dwData)
{
    return (int)((_dwData >> 16) & 0xFFFF);
}

// Increment grow exp by _nInc; returns updated DWORD
inline unsigned int GetIncGrowDWORD(unsigned int _dwData, int _nInc)
{
    int nLevel = (int)((_dwData >> 16) & 0xFFFF);
    int nExp   = (int)(_dwData & 0xFFFF);
    nExp += _nInc;
    // each level requires 300 exp to advance
    while (nExp >= 300)
    {
        nExp -= 300;
        ++nLevel;
    }
    if (nLevel > 0xFFFF) nLevel = 0xFFFF;
    return ((unsigned int)nLevel << 16) | ((unsigned int)(nExp & 0xFFFF));
}

// Convert raw exp value to a group number (used for weapon grow)
inline int GetIncNumberFromExpr(unsigned int _dwExp)
{
    if (_dwExp >= 10000) return 10;
    if (_dwExp >= 5000)  return 5;
    if (_dwExp >= 1000)  return 2;
    return 1;
}

#endif // _INC_ITEMGROWUTILS_
