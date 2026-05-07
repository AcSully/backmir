// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMServer/GameWorld/HeroObject.cpp:2847+ (std::list<const ItemExtraAttribList*>)
//   BMServer/GameWorld/GameDbBuffer.{h,cpp} (std::map<int, ItemExtraAttribList*>)
//   BMClient/GameScene/GameInfoManager.{h,cpp} (同上)
//   BMClient/GameScene/GamePlayer.cpp (std::list<const ItemExtraAttribList*>)
//   BMClient/GameDialog/GameDisplayDlg.cpp:1475 (ItemExtraAttribItem extraAttrib;
//                                                 .nAttribID, .nAttribValue)
//   BMClient/GameDialog/GameIntroDlg.cpp:882, 1041, 1657, 2541
//   BMClient/GameDialog/GameOtherHumDlg.cpp:1000, 1802
//   BMClient/GameDialog/GameDlgBase.h:562 (const ItemExtraAttribList*)
//
// 调用点字段一致：
//   ItemExtraAttribItem.nAttribID  -> int (取值 EAID_AC/EAID_MAC/EAID_DC/EAID_MC/EAID_SC/...)
//   ItemExtraAttribItem.nAttribValue -> int (HIWORD/LOWORD 拆分高低位)
//
// EAID_* 枚举名称在 GameDialog/GameDisplayDlg.cpp:1491-1495 出现，
// 完整集合需进一步从 LuaDataLoader::LoadSuitAttrib 读取的 lua 表反推；
// 此处先列出可见的成员，未来发现新值时追加。
#pragma once
#ifndef _INC_ITEM_EXTRA_SUIT_DEF_
#define _INC_ITEM_EXTRA_SUIT_DEF_

#include <vector>

// 装备额外属性 ID（完整集合来自 StateController.h 调用点）
enum ExtraAttribID
{
    EAID_NONE         = 0,
    EAID_AC           = 1,
    EAID_MAC          = 2,
    EAID_DC           = 3,
    EAID_MC           = 4,
    EAID_SC           = 5,
    EAID_ACCURACY     = 6,
    EAID_LUCKY        = 7,
    EAID_ATKSPEED     = 8,
    EAID_MOVESPEED    = 9,
    EAID_ADDHPSECOND  = 10,
    EAID_ADDMPSECOND  = 11,
    EAID_CRITICAL     = 12,
    EAID_CRITICALPEC  = 13,
    EAID_CRITICALLIMIT= 14,
    EAID_IGNOREAC     = 15,
    EAID_MAGICITEM    = 16,
    EAID_MAGICDEFENSE = 17,
    EAID_DCDEFENSE    = 18,
    EAID_DCDAMAGE     = 19,
    EAID_MCDAMAGE     = 20,
    EAID_SCDAMAGE     = 21,
    EAID_DCHIDE       = 22,
    EAID_MAGICHIDE    = 23,
    EAID_IGNOREMCDAM  = 24,
    EAID_IGNOREDCDAM  = 25,
    EAID_SUCKDAMAGE   = 26,
    EAID_STEALHP      = 27,
    EAID_HURTTRANS    = 28,
    EAID_MOVEPOS      = 29,
    EAID_REVIVE       = 30,
    EAID_NEARPALSY    = 31,
    EAID_FARPALSY     = 32,
    EAID_POISRECOVER  = 33,
    EAID_STONERECOVER = 34,
    EAID_MOUNTAIN     = 35,
    EAID_SUMMONWHITETIGER = 36,
};

// 单条额外属性
struct ItemExtraAttribItem
{
    int nAttribID;     // ExtraAttribID（或更广泛的 lua-defined ID）
    int nAttribValue;  // 数值；部分 ID 用 HIWORD/LOWORD 编码上下界
};

#define MAX_EXTRAATTIRB     4   // max activation tiers per suit
#define MAX_SUIT_EQUIP_ID   10  // max equip slots per suit

// 一套装备的额外属性集合（按套装 ID 索引）
struct ItemExtraAttribList
{
    int  nSuitID;                           // suit set ID (matches ItemAttrib::atkPalsy)
    char szSuitChName[32];
    int  nSuitEquipID[MAX_SUIT_EQUIP_ID];   // item IDs that belong to this suit
    int  nActiveSum[MAX_EXTRAATTIRB];       // activation thresholds (e.g. 2,4,6,8 pieces)
    int  nActiveAttribSum[MAX_EXTRAATTIRB]; // how many stExtraAttrib entries are active at each tier
    ItemExtraAttribItem stExtraAttrib[MAX_EXTRAATTIRB * 8]; // flat attrib array
    std::vector<ItemExtraAttribItem> items; // legacy alias (same data, kept for client compat)
};

#endif // _INC_ITEM_EXTRA_SUIT_DEF_
