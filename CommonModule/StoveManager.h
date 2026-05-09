// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMServer/tolua/BackMirServer.pkg:5 ($#include)
//   BMServer/tolua/BackMirServer.pkg:30 ($pfile "StoveManager.pkg")
//   BMServer/tolua/StoveManager.pkg (LifeSkillType enum)
//   BMServer/tolua/luaServer.cpp:20 (#include)
//   BMServer/tolua/luaServer.cpp:2590 (LifeSkillType cast)
//   BMServer/tolua/luaServer.cpp:8771-8776 (kLifeSkill_* constants)
//   HeroObject::UpdateLifeSkillLevel(LifeSkillType, int) — luaServer.cpp:2596
//   BMServer/CMainServer/CMainServer.cpp:380 (StoveManager::GetInstance(true))
#pragma once
#ifndef _INC_STOVEMANAGER_
#define _INC_STOVEMANAGER_

#include "stove_def.h"
#include <vector>
#include <map>

// Stove attrib type IDs (used in StoveAttribInfo::dwAttribs LOWORD)
enum StoveAttribType
{
    kStoveAttrib_EnhanceDefence     = 1,
    kStoveAttrib_EnhanceAttack      = 2,
    kStoveAttrib_CriticalAttack     = 3,
    kStoveAttrib_CriticalLimit      = 4,
    kStoveAttrib_NormalAttackSpeed  = 5,
    kStoveAttrib_SuckHP             = 6,
    kStoveAttrib_SummonWhiteTiger   = 7,
    kStoveAttrib_NearPalsy          = 8,
    kStoveAttrib_Mountain           = 9,
    kStoveAttrib_PoisRecover        = 10,
    kStoveAttrib_StoneRecover       = 11,
    kStoveAttrib_AddHPSecond        = 12,
    kStoveAttrib_AddMPSecond        = 13,
};

// Get string name for stove attribute type
inline const char* GetStoveAttribName(StoveAttribType _eType)
{
    switch(_eType)
    {
    case kStoveAttrib_EnhanceDefence:    return "Defense";
    case kStoveAttrib_EnhanceAttack:     return "Attack";
    case kStoveAttrib_CriticalAttack:    return "Critical";
    case kStoveAttrib_CriticalLimit:     return "CriticalLimit";
    case kStoveAttrib_NormalAttackSpeed: return "AttackSpeed";
    case kStoveAttrib_SuckHP:            return "SuckHP";
    case kStoveAttrib_SummonWhiteTiger:  return "SummonTiger";
    case kStoveAttrib_NearPalsy:         return "NearPalsy";
    case kStoveAttrib_Mountain:          return "Mountain";
    case kStoveAttrib_PoisRecover:       return "PoisRecover";
    case kStoveAttrib_StoneRecover:      return "StoneRecover";
    case kStoveAttrib_AddHPSecond:       return "AddHP";
    case kStoveAttrib_AddMPSecond:       return "AddMP";
    default:                             return "Unknown";
    }
}

// One stove (potential) attrib record
struct StoveAttribInfo
{
    int          nAttribCount;
    unsigned int dwAttribs[16]; // LOWORD=type, HIWORD=value
    unsigned int dwActiveItemType;
    int          nLevel;
    int          nAttribId;
    char         szName[32];    // display name
};

// Life-skill (crafting) types exposed to Lua
enum LifeSkillType
{
    kLifeSkill_SmeltOre   = 0,
    kLifeSkill_SmeltWood  = 1,
    kLifeSkill_SmeltCloth = 2,
    kLifeSkill_SmeltGem   = 3,
    kLifeSkill_SmeltEquip = 4,
    kLifeSkill_Total      = 5,
};

struct LifeSkillInfo
{
    int          nMaxLevel;
    unsigned int uExp[10];
};

struct MakeEquipInfo
{
    int nItemId;
    int nMaterialCount;
    int nMaterialsId[8];
    int nMaterialsCount[8];
    int nNeedMoney;
    int nNeedLevel;
    int nExp;
};

typedef std::map<int, MakeEquipInfo> MakeEquipInfoMap;

typedef std::vector<StoveAttribInfo> StoveAttribVector;

class StoveManager
{
public:
    static StoveManager* GetInstance(bool _bDestroy = false)
    {
        static StoveManager* s_pIns = nullptr;
        if (_bDestroy) { delete s_pIns; s_pIns = nullptr; return nullptr; }
        if (!s_pIns) s_pIns = new StoveManager;
        return s_pIns;
    }

    bool Init(struct lua_State*) { return true; }
    const StoveAttribInfo* GetStoveAttrib(int /*_nIndex*/) { return nullptr; }
    const LifeSkillInfo* GetLifeSkillInfo(LifeSkillType /*_eType*/) { return nullptr; }
    const MakeEquipInfo* GetMakeEquipInfo(int /*_nItemId*/) { return nullptr; }
    const MakeEquipInfoMap& GetMakeEquipInfoMap() { static MakeEquipInfoMap s_map; return s_map; }
    const StoveAttribVector& GetStoveAttribVector() { static StoveAttribVector s_vec; return s_vec; }
};

#endif // _INC_STOVEMANAGER_
