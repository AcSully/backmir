// [reconstructed] �ؽ��� 2026-05-06 ���� ��Դ���õ㣺
//   BMServer/GameWorld/GameDbBuffer.cpp (ItemAttrib fields, ItemFullAttrib, MonsFullAttrib,
//     HeroBaseInfo, MonsDropItemInfo, pszDefault* names, EXTRA_MASK_ENCRYPT)
//   BMServer/GameWorld/ObjectValid.h (ItemAttrib field names: id/name/lucky/curse/hide/
//     accuracy/atkSpeed/atkPalsy/atkPois/moveSpeed/weight/reqType/reqValue/sex/type/
//     maxDC/DC/maxAC/AC/maxMAC/MAC/maxSC/SC/maxMC/MC/maxHP/HP/maxMP/MP/maxEXPR/EXPR/
//     level/extra/tex/price)
//   BMServer/GameWorld/DBThread.h (GroundItem forward decl)
//   BMServer/tolua/GDefine.pkg (GroundItem struct)
//   BMClient/GameDialog/OlShopDlg.h (ItemAttrib via OfflineSellSystem.h)
#pragma once
#ifndef _INC_OBJECTDATA_
#define _INC_OBJECTDATA_

#include "GDefine.h"
#include "item_extra_suit_def.h"
#include "ByteBuffer.h"
#include <string>
#include <vector>
#include <list>

#ifdef _WIN32
#include <Windows.h>
#endif

// WanLi (stamina) table: [level-1][job] (0=warrior, 1=mage, 2=taoist)
#ifndef MAX_LEVEL
#define MAX_LEVEL 200
#endif
extern int g_nWanLiTable[MAX_LEVEL][3];
extern int g_nHPTable[MAX_LEVEL][3];
extern int g_nMPTable[MAX_LEVEL][3];
extern int g_nExprTable[MAX_LEVEL];

// -----------------------------------------------------------------------
// ItemAttrib �� core item/monster attribute record (35 columns in SQLite)
// -----------------------------------------------------------------------
#define EXTRA_MASK_ENCRYPT  0x01    // bit in ItemAttrib::extra: fields are XOR-encrypted

struct ItemAttrib
{
    unsigned int    id;
    char            name[20];
    unsigned char   lucky;
    unsigned char   curse;
    unsigned char   hide;
    unsigned char   accuracy;
    unsigned char   atkSpeed;
    unsigned char   atkPalsy;
    unsigned char   atkPois;
    unsigned char   moveSpeed;
    unsigned char   weight;
    unsigned char   reqType;
    unsigned char   reqValue;
    unsigned char   sex;
    unsigned char   type;
    unsigned short  maxDC;
    unsigned short  DC;
    unsigned short  maxAC;
    unsigned short  AC;
    unsigned short  maxMAC;
    unsigned short  MAC;
    unsigned short  maxSC;
    unsigned short  SC;
    unsigned short  maxMC;
    unsigned short  MC;
    unsigned int    maxHP;
    unsigned int    HP;
    unsigned int    maxMP;
    unsigned int    MP;
    unsigned int    maxEXPR;
    unsigned int    EXPR;
    unsigned short  level;
    unsigned char   extra;      // EXTRA_MASK_ENCRYPT etc.
    unsigned short  tex;
    unsigned int    price;
    unsigned int    tag;        // runtime item tag (unique ID for ground items)

    bool operator==(const ItemAttrib& o) const
    {
        return memcmp(this, &o, sizeof(ItemAttrib)) == 0;
    }
    
    // Getter/Setter methods for Lua bindings
    unsigned int GetLucky() const { return lucky; }
    void SetLucky(unsigned int v) { lucky = (unsigned char)v; }
    unsigned int GetHide() const { return hide; }
    void SetHide(unsigned int v) { hide = (unsigned char)v; }
    unsigned int GetAccuracy() const { return accuracy; }
    void SetAccuracy(unsigned int v) { accuracy = (unsigned char)v; }
    unsigned int GetAtkSpeed() const { return atkSpeed; }
    void SetAtkSpeed(unsigned int v) { atkSpeed = (unsigned char)v; }
    unsigned int GetAtkPalsy() const { return atkPalsy; }
    void SetAtkPalsy(unsigned int v) { atkPalsy = (unsigned char)v; }
    unsigned int GetAtkPois() const { return atkPois; }
    void SetAtkPois(unsigned int v) { atkPois = (unsigned char)v; }
    unsigned int GetMoveSpeed() const { return moveSpeed; }
    void SetMoveSpeed(unsigned int v) { moveSpeed = (unsigned char)v; }
    unsigned int GetWeight() const { return weight; }
    void SetWeight(unsigned int v) { weight = (unsigned char)v; }
    unsigned int GetReqType() const { return reqType; }
    void SetReqType(unsigned int v) { reqType = (unsigned char)v; }
    unsigned int GetReqValue() const { return reqValue; }
    void SetReqValue(unsigned int v) { reqValue = (unsigned char)v; }
    unsigned int GetSex() const { return sex; }
    void SetSex(unsigned int v) { sex = (unsigned char)v; }
    unsigned int GetType() const { return type; }
    void SetType(unsigned int v) { type = (unsigned char)v; }
    unsigned int GetMaxDC() const { return maxDC; }
    void SetMaxDC(unsigned int v) { maxDC = (unsigned short)v; }
    unsigned int GetDC() const { return DC; }
    void SetDC(unsigned int v) { DC = (unsigned short)v; }
    unsigned int GetMaxAC() const { return maxAC; }
    void SetMaxAC(unsigned int v) { maxAC = (unsigned short)v; }
    unsigned int GetAC() const { return AC; }
    void SetAC(unsigned int v) { AC = (unsigned short)v; }
    unsigned int GetMaxMAC() const { return maxMAC; }
    void SetMaxMAC(unsigned int v) { maxMAC = (unsigned short)v; }
    unsigned int GetMAC() const { return MAC; }
    void SetMAC(unsigned int v) { MAC = (unsigned short)v; }
    unsigned int GetMaxSC() const { return maxSC; }
    void SetMaxSC(unsigned int v) { maxSC = (unsigned short)v; }
    unsigned int GetSC() const { return SC; }
    void SetSC(unsigned int v) { SC = (unsigned short)v; }
    unsigned int GetMaxMC() const { return maxMC; }
    void SetMaxMC(unsigned int v) { maxMC = (unsigned short)v; }
    unsigned int GetMC() const { return MC; }
    void SetMC(unsigned int v) { MC = (unsigned short)v; }
    unsigned int GetMaxHP() const { return maxHP; }
    void SetMaxHP(unsigned int v) { maxHP = v; }
    unsigned int GetHP() const { return HP; }
    void SetHP(unsigned int v) { HP = v; }
    unsigned int GetMaxMP() const { return maxMP; }
    void SetMaxMP(unsigned int v) { maxMP = v; }
    unsigned int GetMP() const { return MP; }
    void SetMP(unsigned int v) { MP = v; }
    unsigned int GetMaxExpr() const { return maxEXPR; }
    void SetMaxExpr(unsigned int v) { maxEXPR = v; }
    unsigned int GetExpr() const { return EXPR; }
    void SetExpr(unsigned int v) { EXPR = v; }
    unsigned int GetLevel() const { return level; }
    void SetLevel(unsigned int v) { level = (unsigned short)v; }
    unsigned int GetTex() const { return tex; }
    void SetTex(unsigned int v) { tex = (unsigned short)v; }
    unsigned int GetPrice() const { return price; }
    void SetPrice(unsigned int v) { price = v; }

    bool operator!=(const ItemAttrib& o) const { return !(*this == o); }
};

BYTEBUFFER_STRUCT_OPERATOR(ItemAttrib);

typedef std::vector<ItemAttrib> ItemList;

// Magic effect types
enum MAGICEFFECT_TYPE
{
	ME_NONE = 0,
	ME_GONGSHA = 7,
	ME_CISHA = 16,
	ME_BANYUE = 23,
	ME_LIEHUO = 43,
	ME_HONGDU,
	ME_LVDU,
	ME_TOTAL,
};

#define MAGICEFFECT_TOTAL 4

// Client-side magic effect table size - defined as enum in MagicEffectID.h

// Equipment requirement error codes
#ifndef REQ_ERR_LEVEL
#define REQ_ERR_LEVEL		1
#define REQ_ERR_DC			2
#define REQ_ERR_MC			3
#define REQ_ERR_SC			4
#define REQ_ERR_SEX			5
#define REQ_ERR_NOTHING		100
#define REQ_ERR_ISTEP		101
#define REQ_ERR_UNKNOWREQ	102
#endif

struct RenderInfo
{
    BYTE wil;
    BYTE id;
    BYTE drts;
    BYTE index;
    USHORT standbegin;
    USHORT standframe;
    USHORT standtotal;
    USHORT walkbegin;
    USHORT walkframe;
    USHORT walktotal;
    USHORT atkbegin;
    USHORT atkframe;
    USHORT atktotal;
    USHORT hurtbegin;
    USHORT hurtframe;
    USHORT hurttotal;
    USHORT deadbegin;
    USHORT deadframe;
    USHORT deadtotal;
    USHORT magicbegin;
    USHORT magicframe;
    USHORT magictotal;
    USHORT atkeftbegin;
    USHORT atkeftframe;
    USHORT atkefttotal;
    USHORT showbegin;
    USHORT showframe;
    USHORT sndindex;
};

// -----------------------------------------------------------------------
// GroundItem �� item lying on the ground in a scene
// -----------------------------------------------------------------------
struct GroundItem
{
    ItemAttrib  stAttrib;
    int         nPosX;
    int         nPosY;
    unsigned int dwTag;
    int         nOwner;     // hero uid that may pick it up first
    unsigned short wPosX;   // alias used by client renderer
    unsigned short wPosY;   // alias used by client renderer
    bool        bVisible;   // client-side visibility flag

    void SetPosX(int _x) { nPosX = _x; wPosX = (unsigned short)_x; }
    void SetPosY(int _y) { nPosY = _y; wPosY = (unsigned short)_y; }
    ItemAttrib* GetItemAttrib() { return &stAttrib; }
};

typedef std::list<GroundItem*> GROUNDITEMS;

// Player equipment visual attributes
struct PlayerEquipAttrib
{
    int nWeapon;
    int nCloth;
    int nNeck;
    int nBrac[2];
    int nRing[2];
    int nHelm;
    int nMedal;
    int nGem;
    int nShoe;
    int nBelt;
    int nHairStyle;
};

// Player texture index table
struct PlayerTexIndexTable
{
    USHORT wHum;
    USHORT wHair;
    USHORT wWeapon;
};

// Map cell object container
class GameObject;
class MagicElement;
#define MAX_CELL_OBJECTS    5
struct MemMapObject
{
    GameObject*     pObjects[MAX_CELL_OBJECTS];
    GroundItem*     pItems[MAX_CELL_OBJECTS];
    MagicElement*   pMagics[MAX_CELL_OBJECTS];
};

// -----------------------------------------------------------------------
// MonsDropItemInfo  -  one entry in a monster's drop table
// -----------------------------------------------------------------------
struct MonsDropItemInfo
{
    int         nItemId;
    std::string strItemName;    // temporary during load; cleared after id resolved
    int         nDropRate;      // per-mille or percent, lua-defined
    int         nMinCount;
    int         nMaxCount;
};
typedef std::vector<MonsDropItemInfo> MonsDropItemInfoVec;

// -----------------------------------------------------------------------
// ItemFullAttrib �� item record as loaded from lua config
// -----------------------------------------------------------------------
struct ItemFullAttrib
{
    ItemAttrib  baseAttrib;
    int         nGrade;         // item grade/tier (used by GetItemGradeInFullAttrib)
    int         nSuitID;        // suit set ID (0 = none)
    char        szSuitChName[32];
    std::string strDesc;        // item description text (loaded from lua config)
};

// -----------------------------------------------------------------------
// MonsFullAttrib �� monster record as loaded from lua config
// -----------------------------------------------------------------------
struct MonsFullAttrib
{
    ItemAttrib          baseAttrib;
    MonsDropItemInfoVec xDropItems;
};

// -----------------------------------------------------------------------
// HeroBaseInfo �� per-level base stats for each job class
// -----------------------------------------------------------------------
struct HeroBaseInfo
{
    int nHP[3];     // indexed by job: 0=warrior 1=mage 2=taoist
    int nMP[3];
    int nWanli[3];
    int nExpr;

    int GetHP(int job)    const { return nHP[job]; }
    int GetMP(int job)    const { return nMP[job]; }
    int GetWanli(int job) const { return nWanli[job]; }
    int GetExpr()         const { return nExpr; }
};

// -----------------------------------------------------------------------
// Lua table name constants (used by LuaDataLoader calls in GameDbBuffer.cpp)
// -----------------------------------------------------------------------
static const char* pszDefaultItemFullAttribTableName  = "config_items";
static const char* pszDefaultMonsFullAttribTableName  = "config_monsters";
static const char* pszDefaultSuitAttribTableName      = "config_suitAttrib";
static const char* pszDefaultHeroBaseAttirbTableName  = "config_heroBaseAttrib";

// -----------------------------------------------------------------------
// UserData �� per-object runtime state (position, map, game/server state)
// -----------------------------------------------------------------------
struct UserData
{
    ItemAttrib      stAttrib;
    unsigned short  wCoordX;
    unsigned short  wCoordY;
    unsigned short  wMapID;
    USER_STATE      eServerState;
    OBJECT_STATE    eGameState;
    int             nDrt;
    BYTE            bJob;           // character job class (0=warrior 1=mage 2=taoist)
    unsigned int    dwLastWalkTime;

    void Reset()
    {
        wCoordX = wCoordY = wMapID = 0;
        eServerState = US_NOTHING;
        eGameState   = OS_STAND;
        nDrt = 0;
        bJob = 0;
        dwLastWalkTime = 0;
    }
};

// -----------------------------------------------------------------------
// HeroHeader �� character selection screen summary record
// -----------------------------------------------------------------------
struct HeroHeader
{
    char         szName[20];
    BYTE         bJob;
    BYTE         bSex;
    unsigned int uLevel;
    unsigned int uOp;       // operation flags
};
BYTEBUFFER_STRUCT_OPERATOR(HeroHeader);

// -----------------------------------------------------------------------
// ExtendHeroAttrib �� hero cosmetic / life-skill extended attributes
// -----------------------------------------------------------------------
struct ExtendHeroAttrib
{
    unsigned int uHair;
    unsigned int uWing;
    unsigned int uClothLook;
    unsigned int uWeaponLook;
    unsigned int uNameFrame;
    unsigned int uChatFrame;
    unsigned int uChatColor;
    unsigned int uSmeltOreLevel;
    unsigned int uSmeltOreExp;
    unsigned int uSmeltWoodLevel;
    unsigned int uSmeltWoodExp;
    unsigned int uSmeltClothLevel;
    unsigned int uSmeltClothExp;
    unsigned int uSmeltGemLevel;
    unsigned int uSmeltGemExp;
    unsigned int uMakeEquipLevel;
    unsigned int uMakeEquipExp;
};

#endif // _INC_OBJECTDATA_
