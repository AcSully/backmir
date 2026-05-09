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
    MMASK_GONGSHA         = 13,
    MMASK_HONGDU          = 14,
    MMASK_KTSWORD         = 15,
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
    MMASK_GONGSHA_INDEX      = MMASK_GONGSHA - 1,
    MMASK_HONGDU_INDEX       = MMASK_HONGDU - 1,
    MMASK_KTSWORD_INDEX      = MMASK_KTSWORD - 1,
};

// Client-side mask indices (separate space, used by GameOtherPlayer rendering)
enum MagicClientMaskIndex
{
    MMASK_C_SHEILD_INDEX       = 0,
    MMASK_C_ICE_INDEX          = 1,
    MMASK_C_LVDU_INDEX         = 2,
    MMASK_C_HIDE_INDEX         = 3,
    MMASK_C_ENERGYSHIELD_INDEX = 4,
    MMASK_C_STONE_INDEX        = 5,
    MMASK_C_HONGDU_INDEX       = 6,
    MMASK_C_TOTAL,
};

// Magic effect IDs (uMagicID values used by MagicEffect / MagicSystem rendering)
enum MagicEffectID
{
    MEFF_NONE          = 0,
    MEFF_BASESWORD     = 1,
    MEFF_GONGSHA       = 2,
    MEFF_MOUNTAIN      = 3,
    MEFF_BERSERKER     = 4,
    MEFF_KTSWORD       = 5,
    MEFF_SPIRIT        = 6,
    MEFF_HEAL          = 7,
    MEFF_SUPERHEAL     = 8,
    MEFF_POISON        = 9,
    MEFF_BIGPOISON     = 10,
    MEFF_TEMPT         = 11,
    MEFF_HIDE          = 12,
    MEFF_DOOR          = 13,
    MEFF_FIREWALL      = 14,
    MEFF_SHIELD        = 15,
    MEFF_ENERGYSHIELD  = 16,
    MEFF_LIEHUO        = 17,
    MEFF_SLIEHUO       = 18,
    MEFF_CISHA         = 19,
    MEFF_BANYUE        = 20,
    MEFF_LIONROAR      = 21,
    MEFF_FIRESHOWER    = 22,
    MEFF_SKYFIRE       = 23,
    MEFF_FIRECHARM     = 24,
    MEFF_SFIREBALL     = 25,
    MEFF_THUNDER       = 26,
    MEFF_ICEPALM       = 27,
    MEFF_ICEROAR       = 28,
    MEFF_ICETHRUST     = 29,
    MEFF_DRAGONBLUSTER = 30,
    MEFF_BLOODDRAGON   = 31,
    MEFF_JINGANG       = 32,
    MEFF_KULOU         = 33,
    MEFF_SUMMON        = 34,
    MEFF_SUMMONAC      = 35,
    MEFF_SUMMONBOWMAN  = 36,
    MEFF_SUMMONTIGER   = 37,
    MEFF_SUPERSUMMON   = 38,
    MEFF_CHARMAC       = 39,
    MEFF_CHARMMC       = 40,
    MEFF_USERTOTAL     = 200,
    MEFF_TOTAL = MEFF_USERTOTAL,
};

#endif // _INC_MAGICEFFECTID_
