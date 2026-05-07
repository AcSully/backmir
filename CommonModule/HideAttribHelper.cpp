// HideAttribHelper.cpp - Equipment hide attribute encoding implementation
#include "HideAttribHelper.h"

namespace
{
    const unsigned int kAllMask    = 0x0000000Fu;
    const unsigned int kActiveMask = 0x000000F0u;
    const int          kActiveShift = 4;

    inline int slotShift(int _i) { return 8 + _i * 8; }
    const unsigned int kSlotMask = 0xFFu;
    const unsigned int kSlotTypeMask  = 0x0Fu;
    const unsigned int kSlotValueMask = 0xF0u;
    const int          kSlotValueShift = 4;
}

int HideAttribHelper::GetAllAttribCount(unsigned int _uCode)
{
    return (int)(_uCode & kAllMask);
}

int HideAttribHelper::GetActiveAttribCount(unsigned int _uCode)
{
    return (int)((_uCode & kActiveMask) >> kActiveShift);
}

int HideAttribHelper::GetActiveAttribType(int _i, unsigned int _uCode)
{
    if (_i < 0 || _i > 2) return 0;
    return (int)((_uCode >> slotShift(_i)) & kSlotTypeMask);
}

int HideAttribHelper::GetActiveAttribValue(int _i, unsigned int _uCode)
{
    if (_i < 0 || _i > 2) return 0;
    return (int)(((_uCode >> slotShift(_i)) & kSlotValueMask) >> kSlotValueShift);
}

void HideAttribHelper::SetAllAttribCount(unsigned int& _uCode, int _v)
{
    _uCode = (_uCode & ~kAllMask) | ((unsigned int)_v & kAllMask);
}

void HideAttribHelper::SetActiveAttribCount(unsigned int& _uCode, int _v)
{
    _uCode = (_uCode & ~kActiveMask) | (((unsigned int)_v << kActiveShift) & kActiveMask);
}

void HideAttribHelper::SetActiveAttribType(unsigned int& _uCode, int _i, int _type)
{
    if (_i < 0 || _i > 2) return;
    int sh = slotShift(_i);
    _uCode = (_uCode & ~(kSlotTypeMask << sh)) |
             (((unsigned int)_type & kSlotTypeMask) << sh);
}

void HideAttribHelper::SetActiveAttribValue(unsigned int& _uCode, int _i, int _value)
{
    if (_i < 0 || _i > 2) return;
    int sh = slotShift(_i);
    _uCode = (_uCode & ~(kSlotValueMask << sh)) |
             ((((unsigned int)_value << kSlotValueShift) & kSlotValueMask) << sh);
}
