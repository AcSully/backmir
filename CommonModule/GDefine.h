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

// Action codes (aliases for OBJECT_STATE, used in packet uAction fields)
#define ACTION_NONE     OS_STAND
#define ACTION_STAND    OS_STAND
#define ACTION_WALK     OS_WALK
#define ACTION_RUN      OS_RUN
#define ACTION_ATTACK   OS_ATTACK
#define ACTION_STRUCK   OS_STRUCK
#define ACTION_DEAD     OS_DEAD
#define ACTION_SPELL    OS_SPELL
#define ACTION_APPEAR   OS_APPEAR
#define ACTION_SHOW     OS_SHOW
#define ACTION_STOP     OS_STOP
#define ACTION_GROUND   OS_GROUND
#define ACTION_TURN     OS_TURN
#define ACTION_EXT1     0x0104
#define ACTION_EXT2     0x0105
#define ACTION_EXT3     0x0106
#define ACTION_EXT4     0x0107
#define ACTION_CREATE   0x0108
#define ACTION_STATUS   0x0109
#define ACTION_FLY      0x010A

// Struck mask flags
#define STRUCK_MASK_WEAPON   0x01
#define STRUCK_MASK_CRITICAL 0x02

// Debug break stub
#ifndef DEBUG_BREAK
#  define DEBUG_BREAK
#endif

// Difficulty levels
enum DifficultyLevel
{
    kDifficultyNormal = 0,
    kDifficultyEasy   = 1,
    kDifficultyNovice = 2,
    kDifficultyTotal,
};

// item level upgrade quality index (high byte of stored level)
inline int GetItemUpgrade(int _nLevel) { return (_nLevel >> 8) & 0xFF; }

// Make item upgrade value (pack level and upgrade into a single value)
inline int MakeItemUpgrade(int _preLevel, int _upgradeValue) { return (_preLevel & 0xFF) | ((_upgradeValue & 0xFF) << 8); }

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
    kHeroPkType_Total,
};

// Update types (for status update packets)
#define UPDATE_HP        0
#define UPDATE_MP        1
#define UPDATE_MONEY     2
#define UPDATE_MAGIC     3
#define UPDATE_MASTER    4
#define UPDATE_SLAVELV   5
#define UPDATE_MOVESPD   6

// Sound types
#define PLAYSOUND_OBJECTSOUND 1

// Shop types
#define SHOP_DONATE      1
#define SHOP_IDENTIFY    2
#define SHOP_IDENTIFY_LOW 3
#define SHOP_UNBIND      4

// Monster type IDs
#define MONSTER_KULOU           1
#define MONSTER_SHENSHOU        2
#define MONSTER_WOMAJIAOZHU     3
#define MONSTER_CHULONGSHEN     4
#define MONSTER_HUOYANWOMA      5

// Monster multipliers
#define MONS_ELITE_MULTI   2
#define MONS_LEADER_MULTI  3

// Random seed types
#define RANDSEED_NORMALATK 1

// Quest constants
#define MAX_QUEST_NUMBER   100

// Object action types
#define ObjectActionWalk  1
#define ObjectActionRun   2
#define ObjectActionTurn  3

// Requirement types
#define REQ_SEX  5

// Force action types
#define FORCE_KICK_OUT 1

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
