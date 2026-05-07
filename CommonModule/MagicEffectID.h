// MagicEffectID.h - Magic effect IDs and status flags
#pragma once
#ifndef _INC_MAGICEFFECTID_
#define _INC_MAGICEFFECTID_

// Magic mask IDs (buff/debuff state flags)
enum MagicMaskID
{
    MMASK_SHIELD          = 1,
    MMASK_ICE             = 2,
    MMASK_LVDU            = 3,
    MMASK_LIEHUO          = 4,
    MMASK_SLIEHUO         = 5,
    MMASK_HIDE            = 6,
    MMASK_ENERGYSHIELD    = 7,
    MMASK_CHARMAC         = 8,
    MMASK_DECDC           = 9,
    MMASK_CISHA           = 10,
    MMASK_BANYEU          = 11,
    MMASK_STONE           = 12,
    MMASK_SERVER_TOTAL,
    MMASK_TOTAL = MMASK_SERVER_TOTAL,
};

// Timer array indices (1:1 with MagicMaskID)
enum MagicMaskIndex
{
    MMASK_SHIELD_INDEX       = MMASK_SHIELD - 1,
    MMASK_ICE_INDEX          = MMASK_ICE - 1,
    MMASK_LVDU_INDEX         = MMASK_LVDU - 1,
    MMASK_LIEHUO_INDEX       = MMASK_LIEHUO - 1,
    MMASK_SLIEHUO_INDEX      = MMASK_SLIEHUO - 1,
    MMASK_HIDE_INDEX         = MMASK_HIDE - 1,
    MMASK_ENERGYSHIELD_INDEX = MMASK_ENERGYSHIELD - 1,
    MMASK_CHARMAC_INDEX      = MMASK_CHARMAC - 1,
    MMASK_DECDC_INDEX        = MMASK_DECDC - 1,
    MMASK_STONE_INDEX        = MMASK_STONE - 1,
};

#endif // _INC_MAGICEFFECTID_
