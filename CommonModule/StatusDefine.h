// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMServer/GameWorld/HeroObject.cpp (QMSG_*, GSTATUS_*)
//   BMServer/GameWorld/MonsterObject.cpp (QMSG_DOUBLEDROPINFO)
//   BMClient/GameScene/GamePlayer.cpp (GSTATUS_*)
#pragma once
#ifndef _INC_STATUSDEFINE_
#define _INC_STATUSDEFINE_

// ---------------------------------------------------------------------------
// 快速消息 ID（SendQuickMessage 参数）
// ---------------------------------------------------------------------------
enum QuickMsgID
{
    QMSG_NOBAGROOM          = 1,
    QMSG_NOENOUGHMONEY      = 2,
    QMSG_NOENOUGHITEM       = 3,
    QMSG_CANNOTSELLQUEST    = 4,
    QMSG_REVIVEINTERVAL     = 5,
    QMSG_TRANSFERINTERVAL   = 6,
    QMSG_CANNOTTRANSFER     = 7,
    QMSG_INVALIDHUNDUNITEMS = 8,
    QMSG_SKILLLEVELLOW      = 9,
    QMSG_ATTACKMODE         = 10,
    QMSG_DOUBLEDROPINFO     = 11,
    QMSG_IDENTIFYOK         = 12,
    QMSG_IDENTIFYFULL       = 13,
    QMSG_NOIDENTIFYSCROLL   = 14,
    QMSG_OFFSELLOK          = 15,
    QMSG_OFFNOTSOLD         = 16,
    QMSG_UNBINDOK           = 17,
    QMSG_UNBINDFAILED       = 18,
    QMSG_DIFFICULTYLEVEL    = 19,
};

// ---------------------------------------------------------------------------
// 全局状态 ID（GSTATUS_NTF 包中使用）
// ---------------------------------------------------------------------------
enum GStatusID
{
    GSTATUS_DOUBLEDROP    = 200,
    GSTATUS_POISON        = 201,
    GSTATUS_CHARMAC       = 202,
    GSTATUS_SHIELD        = 203,
    GSTATUS_ENERGYSHIELD  = 204,
    GSTATUS_JINGANG       = 205,
    GSTATUS_SUITSAMELEVEL = 206,
    GSTATUS_NTF           = 207,
};

// ---------------------------------------------------------------------------
// 状态信息结构（客户端显示用）
// ---------------------------------------------------------------------------
struct StatusInfo
{
    int          nStatusID;
    int          nParam;
    unsigned int dwExpireTime;
};

#endif // _INC_STATUSDEFINE_
