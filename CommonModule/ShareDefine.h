// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMClient/BackMir/BackMir.h (GAME_MODE, GM_*, SCENE_*, PAGE_*, TIMER_*, WM_SOCKMSG)
//   BMClient/BackMir/BMPreConnWnd.cpp (TIMER_*, GM_*)
//   BMServer/CMainServer/CMainServer.cpp (GM_*, WM_*)
//   BMClient/GameScene/GameResourceManager.h (RES_*, g_szResFile)
//   BMClient/Net/PacketHandler.h (HERO_MAINBAG_SIZE_CUR, PLAYER_ITEM_*)
//   BMServer/GameWorld/ObjectEngine.h (PLAYER_ITEM_*, ITEM_NO, ITEM_COST)
#pragma once
#ifndef _INC_SHAREDEFINE_
#define _INC_SHAREDEFINE_

// ---------------------------------------------------------------------------
// 游戏模式 — 定义在 GDefine.h，此处不重复定义
// ---------------------------------------------------------------------------
#include "GDefine.h"

// ---------------------------------------------------------------------------
// 场景/页面枚举
// ---------------------------------------------------------------------------
#ifndef SCENE_LOGIN
#define SCENE_LOGIN  0
#endif
#ifndef SCENE_NORMAL
#define SCENE_NORMAL 1
#endif

enum PageType
{
    PAGE_LOGIN  = 0,
    PAGE_SELCHR = 1,
};

// ---------------------------------------------------------------------------
// 客户端定时器 ID
// ---------------------------------------------------------------------------
#ifndef TIMER_CONNECTSVR
#define TIMER_CONNECTSVR          1
#endif
#ifndef TIMER_CONNTIMEOUT
#define TIMER_CONNTIMEOUT         2
#endif
#ifndef TIMER_CLOSEGAME
#define TIMER_CLOSEGAME           3
#endif
#ifndef TIMER_LOADDATA
#define TIMER_LOADDATA            4
#endif
#ifndef TIMER_RUNGAME
#define TIMER_RUNGAME             5
#endif
#ifndef TIMER_FTYPETIMEOUT
#define TIMER_FTYPETIMEOUT        6
#endif
#ifndef TIMER_VERIFYTIMEOUT
#define TIMER_VERIFYTIMEOUT       7
#endif
#ifndef TIMER_STYPETIMEOUT
#define TIMER_STYPETIMEOUT        8
#endif
#ifndef TIMER_SEND_LOGIN_HEARTBEAT
#define TIMER_SEND_LOGIN_HEARTBEAT 9
#endif

// ---------------------------------------------------------------------------
// 自定义 Windows 消息
// ---------------------------------------------------------------------------
#ifndef WM_SOCKMSG
#define WM_SOCKMSG          (WM_USER + 100)
#endif
#define WM_PLAYERRANKLIST   (WM_USER + 101)
#define WM_CHECKBUYOLSHOPITEM (WM_USER + 102)
#define WM_CONSUMEDONATE    (WM_USER + 103)
#define WM_SCHEDULEACTIVE   (WM_USER + 104)

// ---------------------------------------------------------------------------
// Resource file enum (client) -- defined in GameResourceUtil.h as GAME_RES
// ---------------------------------------------------------------------------
// ResFileIndex / RES_ITEMS etc. are defined in BMClient/GameScene/GameResourceUtil.h
// Do not redefine here to avoid conflicts.

// ---------------------------------------------------------------------------
// 角色背包/装备槽常量
// ---------------------------------------------------------------------------
#define HERO_MAINBAG_SIZE_CUR   40
#define HERO_ASSISTBAG_SIZE_CUR 20
#define HERO_CLIENT_ASSIST_SIZE HERO_ASSISTBAG_SIZE_CUR
#define HERO_BODY_SIZE          12
#define HERO_BAG_SIZE_CUR       HERO_MAINBAG_SIZE_CUR

enum PlayerItemType
{
    PLAYER_ITEM_CLOTH    = 0,
    PLAYER_ITEM_WEAPON   = 1,
    PLAYER_ITEM_HELMET   = 2,
    PLAYER_ITEM_NECKLACE = 3,
    PLAYER_ITEM_BRACELAT = 4,
    PLAYER_ITEM_BRACELAT1 = 4,
    PLAYER_ITEM_BRACELAT2 = 4,
    PLAYER_ITEM_RING     = 5,
    PLAYER_ITEM_RING1    = 5,   // alias
    PLAYER_ITEM_RING2    = 5,   // alias (single ring slot in this version)
    PLAYER_ITEM_SHOE     = 6,
    PLAYER_ITEM_BELT     = 7,
    PLAYER_ITEM_CHARM    = 8,
    PLAYER_ITEM_GEM      = 9,
    PLAYER_ITEM_MEDAL    = 10,
    PLAYER_ITEM_TOTAL,
};
typedef PlayerItemType PLAYER_ITEM_TYPE;

// ---------------------------------------------------------------------------
// 物品类型
// ---------------------------------------------------------------------------
enum ItemType
{
    ITEM_NO       = 0,   // 空槽
    ITEM_COST     = 1,   // 消耗品
    ITEM_EQUIP    = 2,   // 通用装备占位
    ITEM_QUEST    = 3,   // 任务物品
    ITEM_BALE     = 4,   // 礼包
    ITEM_WEAPON   = 5,   // 武器
    ITEM_CLOTH    = 6,   // 衣服
    ITEM_HELMET   = 7,   // 头盔
    ITEM_NECKLACE = 8,   // 项链
    ITEM_BRACELAT = 9,   // 手镯
    ITEM_RING     = 10,  // 戒指
    ITEM_SHOE     = 11,  // 鞋
    ITEM_BELT     = 12,  // 腰带
    ITEM_CHARM    = 13,  // 护身符
    ITEM_GEM      = 14,  // 宝石
    ITEM_MEDAL    = 15,  // 勋章
    ITEM_BOOK     = 16,  // 技能书
    ITEM_OTHER    = 17,  // 其它
};

// Get item type description name
inline const char* GetItemDescribeName(const ItemAttrib* pItem)
{
    if (!pItem) return "Unknown";
    switch (pItem->type)
    {
    case ITEM_NO:       return "Empty";
    case ITEM_COST:     return "Consumable";
    case ITEM_EQUIP:    return "Equipment";
    case ITEM_QUEST:    return "Quest";
    case ITEM_BALE:     return "Gift";
    case ITEM_WEAPON:   return "Weapon";
    case ITEM_CLOTH:    return "Armor";
    case ITEM_HELMET:   return "Helmet";
    case ITEM_NECKLACE: return "Necklace";
    case ITEM_BRACELAT: return "Bracelet";
    case ITEM_RING:     return "Ring";
    case ITEM_SHOE:     return "Shoe";
    case ITEM_BELT:     return "Belt";
    case ITEM_CHARM:    return "Charm";
    case ITEM_GEM:      return "Gem";
    case ITEM_MEDAL:    return "Medal";
    case ITEM_BOOK:     return "Book";
    case ITEM_OTHER:    return "Other";
    default:            return "Unknown";
    }
}

// ---------------------------------------------------------------------------
// 装备需求类型 (ItemAttrib::reqType) — defined in ObjectData.h as macros
// ---------------------------------------------------------------------------
#ifndef REQ_LEVEL
#define REQ_LEVEL 1
#define REQ_DC    2
#define REQ_MC    3
#define REQ_SC    4
#endif

// 装备需求错误码 — defined in ObjectData.h as macros; skip enum to avoid conflict

// ---------------------------------------------------------------------------
// 杂项常量
// ---------------------------------------------------------------------------
#define OFFLINE_TIME        (5 * 60 * 1000)  // 5 minutes in ms
#define MAX_MONEY           2000000000
#define USER_MAGIC_NUM      50               // max magic slots per hero

// Update attrib notification types (extended)
#define UPDATE_LEVEL        6
#define UPDATE_EXP          7
#define UPDATE_DONATELFET   8

#endif // _INC_SHAREDEFINE_
