// GDefine.h - Global definitions: platform compat + bit flag macros
#pragma once
#ifndef _INC_GDEFINE_
#define _INC_GDEFINE_

#include "platform_compat.h"

// Bit flag helpers
#define TEST_FLAG(val, flag)      ((val) & (flag))
#define TEST_FLAG_BOOL(val, flag) (((val) & (flag)) != 0)
#define SET_FLAG(val, flag)       ((val) |= (flag))
#define CLR_FLAG(val, flag)       ((val) &= ~(flag))

// Game mode
enum GameMode
{
    GM_NONE   = 0,  // Not yet determined
    GM_NORMAL = 1,  // Direct game mode
    GM_LOGIN  = 2,  // Login server + game server dual mode
};
typedef GameMode GAME_MODE;

// Server object type
enum SERVER_OBJECT_TYPE
{
    SOT_NONE    = 0,
    SOT_HERO    = 1,
    SOT_MONSTER = 2,
    SOT_NPC     = 3,
};

// Player state
enum USER_STATE
{
    US_NOTHING = 0,
    US_ONLINE  = 1,
    US_OFFLINE = 2,
};

// Game object state
enum OBJECT_STATE
{
    OS_STAND  = 0,
    OS_WALK   = 1,
    OS_RUN    = 2,
    OS_ATTACK = 3,
    OS_STRUCK = 4,
    OS_DEAD   = 5,
    OS_SPELL  = 6,
    OS_APPEAR = 7,
    OS_SHOW   = 8,
    OS_STOP   = 9,
    OS_GROUND = 10,
    OS_TURN   = 11,
    OS_EXT1   = 12,
    OS_EXT2   = 13,
    OS_EXT3   = 14,
};

// Ability type (for GetRandomAbility)
enum ABILITY_TYPE
{
    AT_DC  = 0,
    AT_AC  = 1,
    AT_MAC = 2,
    AT_MC  = 3,
    AT_SC  = 4,
};

// PK mode
enum HeroPkType
{
    kHeroPkType_None  = 0,
    kHeroPkType_All   = 1,
    kHeroPkType_Peace = 2,
    kHeroPkType_Team  = 3,
    kHeroPkType_Guild = 4,
};

// MaxExpr field flag bits (monster attributes)
#define MAXEXPR_MASK_ELITE    0x01000000
#define MAXEXPR_MASK_LEADER   0x02000000
#define MAXEXPR_MASK_BOSS     0x04000000
#define MAXEXPR_MASK_DEADHIDE 0x08000000

// Bind flag in ItemAttrib::extra
#define POIS_MASK_BIND        0x02

// Flag manipulation macros
#ifndef RESET_FLAG
#  define RESET_FLAG(val, flag)  ((val) &= ~(flag))
#endif
#ifndef SET_FLAG
#  define SET_FLAG(val, flag)    ((val) |= (flag))
#endif

#endif // _INC_GDEFINE_
