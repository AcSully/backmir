// [reconstructed] 重建于 2026-05-06
#include "GamePacket.h"

// ---------------------------------------------------------------------------
// 辅助：写包头（opcode 写入 uOp，uLen 由发送方填充）
// ---------------------------------------------------------------------------
static void WriteHeader(ByteBuffer& buf, const PacketHeader& hdr)
{
    buf << hdr.uLen;
    buf << hdr.uOp;
}
static void ReadHeader(ByteBuffer& buf, PacketHeader& hdr)
{
    buf >> hdr.uLen;
    buf >> hdr.uOp;
}

// ---------------------------------------------------------------------------
// PkgLoginGameTypeNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgLoginGameTypeNot& p)
{
    WriteHeader(buf, p);
    buf << p.bType;
    buf << p.dwConnIdx;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgLoginGameTypeNot& p)
{
    ReadHeader(buf, p);
    buf >> p.bType;
    buf >> p.dwConnIdx;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgLoginVerifyResultAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgLoginVerifyResultAck& p)
{
    WriteHeader(buf, p);
    buf << p.bResult;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgLoginVerifyResultAck& p)
{
    ReadHeader(buf, p);
    buf >> p.bResult;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgLoginQuickMsgNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgLoginQuickMsgNot& p)
{
    WriteHeader(buf, p);
    buf << p.uMsg;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgLoginQuickMsgNot& p)
{
    ReadHeader(buf, p);
    buf >> p.uMsg;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgLoginServerAddrNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgLoginServerAddrNot& p)
{
    WriteHeader(buf, p);
    buf << p.xAddr;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgLoginServerAddrNot& p)
{
    ReadHeader(buf, p);
    buf >> p.xAddr;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgLoginServerAddrV2Not
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgLoginServerAddrV2Not& p)
{
    WriteHeader(buf, p);
    unsigned short uCount = (unsigned short)p.vecServers.size();
    buf << uCount;
    for (unsigned short i = 0; i < uCount; ++i)
        buf << p.vecServers[i];
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgLoginServerAddrV2Not& p)
{
    ReadHeader(buf, p);
    unsigned short uCount = 0;
    buf >> uCount;
    p.vecServers.resize(uCount);
    for (unsigned short i = 0; i < uCount; ++i)
        buf >> p.vecServers[i];
    return buf;
}

// ---------------------------------------------------------------------------
// PkgLoginConnIdxNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgLoginConnIdxNot& p)
{
    WriteHeader(buf, p);
    buf << p.dwLSIdx;
    buf << p.dwGSIdx;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgLoginConnIdxNot& p)
{
    ReadHeader(buf, p);
    buf >> p.dwLSIdx;
    buf >> p.dwGSIdx;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgLoginGsConnIdxNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgLoginGsConnIdxNot& p)
{
    WriteHeader(buf, p);
    buf << p.dwConnCode;
    buf << p.dwLSIdx;
    buf << p.dwGSIdx;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgLoginGsConnIdxNot& p)
{
    ReadHeader(buf, p);
    buf >> p.dwConnCode;
    buf >> p.dwLSIdx;
    buf >> p.dwGSIdx;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgLoginClientSelGSRsp
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgLoginClientSelGSRsp& p)
{
    WriteHeader(buf, p);
    buf << p.uGSServerID;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgLoginClientSelGSRsp& p)
{
    ReadHeader(buf, p);
    buf >> p.uGSServerID;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgLoginHeartBeatNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgLoginHeartBeatNot& p)
{
    WriteHeader(buf, p);
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgLoginHeartBeatNot& p)
{
    ReadHeader(buf, p);
    return buf;
}

// ---------------------------------------------------------------------------
// HeroHeader helper
// ---------------------------------------------------------------------------
static void WriteHeroHeader(ByteBuffer& buf, const HeroHeader& h)
{
    buf.Write(h.szName, sizeof(h.szName));
    buf << h.bJob;
    buf << h.bSex;
    buf << h.uLevel;
}
static void ReadHeroHeader(ByteBuffer& buf, HeroHeader& h)
{
    buf.Read(h.szName, sizeof(h.szName));
    buf >> h.bJob;
    buf >> h.bSex;
    buf >> h.uLevel;
}

// ---------------------------------------------------------------------------
// PkgLoginSendHumDataNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgLoginSendHumDataNot& p)
{
    WriteHeader(buf, p);
    buf << p.dwPlayerIndex;
    buf << p.dwLSIndex;
    buf << p.dwUID;
    buf << p.dwConnCode;
    WriteHeroHeader(buf, p.stHeader);
    buf << p.xData;
    buf << p.xExtendInfo;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgLoginSendHumDataNot& p)
{
    ReadHeader(buf, p);
    buf >> p.dwPlayerIndex;
    buf >> p.dwLSIndex;
    buf >> p.dwUID;
    buf >> p.dwConnCode;
    ReadHeroHeader(buf, p.stHeader);
    buf >> p.xData;
    buf >> p.xExtendInfo;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgLoginSendHumExtDataNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgLoginSendHumExtDataNot& p)
{
    WriteHeader(buf, p);
    buf << p.dwPlayerIndex;
    buf << p.dwLSIndex;
    buf << p.dwUID;
    buf << p.dwConnCode;
    buf << p.cExtIndex;
    buf << p.xData;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgLoginSendHumExtDataNot& p)
{
    ReadHeader(buf, p);
    buf >> p.dwPlayerIndex;
    buf >> p.dwLSIndex;
    buf >> p.dwUID;
    buf >> p.dwConnCode;
    buf >> p.cExtIndex;
    buf >> p.xData;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgLoginHumRankListNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgLoginHumRankListNot& p)
{
    WriteHeader(buf, p);
    buf << p.xData;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgLoginHumRankListNot& p)
{
    ReadHeader(buf, p);
    buf >> p.xData;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgLoginCheckBuyShopItemAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgLoginCheckBuyShopItemAck& p)
{
    WriteHeader(buf, p);
    buf << p.cRet;
    buf << p.nItemId;
    buf << p.nQueryId;
    buf << p.nUid;
    buf << p.nGsId;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgLoginCheckBuyShopItemAck& p)
{
    ReadHeader(buf, p);
    buf >> p.cRet;
    buf >> p.nItemId;
    buf >> p.nQueryId;
    buf >> p.nUid;
    buf >> p.nGsId;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgLoginCheckBuyShopItemReq
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgLoginCheckBuyShopItemReq& p)
{
    WriteHeader(buf, p);
    buf << p.nItemId;
    buf << p.nCost;
    buf << p.nGsId;
    buf << p.nUid;
    buf << p.nQueryId;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgLoginCheckBuyShopItemReq& p)
{
    ReadHeader(buf, p);
    buf >> p.nItemId;
    buf >> p.nCost;
    buf >> p.nGsId;
    buf >> p.nUid;
    buf >> p.nQueryId;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgLoginConsumeDonateAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgLoginConsumeDonateAck& p)
{
    WriteHeader(buf, p);
    buf << p.cRet;
    buf << p.nItemId;
    buf << p.nUid;
    buf << p.nGsId;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgLoginConsumeDonateAck& p)
{
    ReadHeader(buf, p);
    buf >> p.cRet;
    buf >> p.nItemId;
    buf >> p.nUid;
    buf >> p.nGsId;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgLoginConsumeDonateReq
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgLoginConsumeDonateReq& p)
{
    WriteHeader(buf, p);
    buf << p.nCost;
    buf << p.nGsId;
    buf << p.nItemId;
    buf << p.nUid;
    buf << p.xName;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgLoginConsumeDonateReq& p)
{
    ReadHeader(buf, p);
    buf >> p.nCost;
    buf >> p.nGsId;
    buf >> p.nItemId;
    buf >> p.nUid;
    buf >> p.xName;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgLoginScheduleActiveRsp
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgLoginScheduleActiveRsp& p)
{
    WriteHeader(buf, p);
    buf << p.nEventId;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgLoginScheduleActiveRsp& p)
{
    ReadHeader(buf, p);
    buf >> p.nEventId;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgLoginRegisterScheduleReq
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgLoginRegisterScheduleReq& p)
{
    WriteHeader(buf, p);
    buf << p.nEventId;
    buf << p.xCronExpr;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgLoginRegisterScheduleReq& p)
{
    ReadHeader(buf, p);
    buf >> p.nEventId;
    buf >> p.xCronExpr;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgLoginGSRoleUpdateNtf
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgLoginGSRoleUpdateNtf& p)
{
    WriteHeader(buf, p);
    buf << p.nUID;
    buf << p.xName;
    buf << p.sType;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgLoginGSRoleUpdateNtf& p)
{
    ReadHeader(buf, p);
    buf >> p.nUID;
    buf >> p.xName;
    buf >> p.sType;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgLoginUpdateHumRankReq
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgLoginUpdateHumRankReq& p)
{
    WriteHeader(buf, p);
    buf << p.nUid;
    buf << p.cJob;
    buf << p.nLevel;
    buf << p.xName;
    buf << p.nPower;
    buf << p.nServerId;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgLoginUpdateHumRankReq& p)
{
    ReadHeader(buf, p);
    buf >> p.nUid;
    buf >> p.cJob;
    buf >> p.nLevel;
    buf >> p.xName;
    buf >> p.nPower;
    buf >> p.nServerId;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgUserLoginAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgUserLoginAck& p)
{
    WriteHeader(buf, p);
    buf << p.bOk;
    buf << p.nId;
    buf << p.uVersion;
    buf << p.xMsg;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgUserLoginAck& p)
{
    ReadHeader(buf, p);
    buf >> p.bOk;
    buf >> p.nId;
    buf >> p.uVersion;
    buf >> p.xMsg;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgUserLoginReq
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgUserLoginReq& p)
{
    WriteHeader(buf, p);
    WriteHeroHeader(buf, p.stHeader);
    buf << p.xData;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgUserLoginReq& p)
{
    ReadHeader(buf, p);
    ReadHeroHeader(buf, p.stHeader);
    buf >> p.xData;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgForceActionAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgForceActionAck& p)
{
    WriteHeader(buf, p);
    buf << p.nAction;
    buf << p.nParam;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgForceActionAck& p)
{
    ReadHeader(buf, p);
    buf >> p.nAction;
    buf >> p.nParam;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgNewPlayerNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgNewPlayerNot& p)
{
    WriteHeader(buf, p);
    buf << p.dwID;
    buf.Write(p.szName, sizeof(p.szName));
    buf << p.wPosX << p.wPosY << p.bDir << p.bJob << p.bSex << p.uLevel;
    buf << p.dwLook1 << p.dwLook2;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgNewPlayerNot& p)
{
    ReadHeader(buf, p);
    buf >> p.dwID;
    buf.Read(p.szName, sizeof(p.szName));
    buf >> p.wPosX >> p.wPosY >> p.bDir >> p.bJob >> p.bSex >> p.uLevel;
    buf >> p.dwLook1 >> p.dwLook2;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgNewNPCNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgNewNPCNot& p)
{
    WriteHeader(buf, p);
    buf << p.dwID;
    buf.Write(p.szName, sizeof(p.szName));
    buf << p.wPosX << p.wPosY << p.bDir << p.nTemplateID;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgNewNPCNot& p)
{
    ReadHeader(buf, p);
    buf >> p.dwID;
    buf.Read(p.szName, sizeof(p.szName));
    buf >> p.wPosX >> p.wPosY >> p.bDir >> p.nTemplateID;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgDelNPCNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgDelNPCNot& p)
{
    WriteHeader(buf, p);
    buf << p.dwID;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgDelNPCNot& p)
{
    ReadHeader(buf, p);
    buf >> p.dwID;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgChatNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgChatNot& p)
{
    WriteHeader(buf, p);
    buf << p.xSender << p.xMsg << p.nChannel;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgChatNot& p)
{
    ReadHeader(buf, p);
    buf >> p.xSender >> p.xMsg >> p.nChannel;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgGmNotificationNot / Req
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgGmNotificationNot& p)
{
    WriteHeader(buf, p); buf << p.xMsg; return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgGmNotificationNot& p)
{
    ReadHeader(buf, p); buf >> p.xMsg; return buf;
}
ByteBuffer& operator<<(ByteBuffer& buf, const PkgGmNotificationReq& p)
{
    WriteHeader(buf, p); buf << p.xMsg; return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgGmNotificationReq& p)
{
    ReadHeader(buf, p); buf >> p.xMsg; return buf;
}

// ---------------------------------------------------------------------------
// PkgSystemNotifyNot / Req
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgSystemNotifyNot& p)
{
    WriteHeader(buf, p); buf << p.xMsg << p.nType; return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgSystemNotifyNot& p)
{
    ReadHeader(buf, p); buf >> p.xMsg >> p.nType; return buf;
}
ByteBuffer& operator<<(ByteBuffer& buf, const PkgSystemNotifyReq& p)
{
    WriteHeader(buf, p); buf << p.xMsg << p.dwTimes << p.dwColor; return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgSystemNotifyReq& p)
{
    ReadHeader(buf, p); buf >> p.xMsg >> p.dwTimes >> p.dwColor; return buf;
}

// ---------------------------------------------------------------------------
// PkgSystemClientVersionErrNtf
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgSystemClientVersionErrNtf& p)
{
    WriteHeader(buf, p); buf << p.nVersion; return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgSystemClientVersionErrNtf& p)
{
    ReadHeader(buf, p); buf >> p.nVersion; return buf;
}

// ---------------------------------------------------------------------------
// PkgSystemHideDoorNtf
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgSystemHideDoorNtf& p)
{
    WriteHeader(buf, p); buf << p.wPosX << p.wPosY << p.bHide; return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgSystemHideDoorNtf& p)
{
    ReadHeader(buf, p); buf >> p.wPosX >> p.wPosY >> p.bHide; return buf;
}

// ---------------------------------------------------------------------------
// PkgSystemWorldSayNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgSystemWorldSayNot& p)
{
    WriteHeader(buf, p); buf << p.xName << p.xMsg << p.uReserved; return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgSystemWorldSayNot& p)
{
    ReadHeader(buf, p); buf >> p.xName >> p.xMsg >> p.uReserved; return buf;
}

// ---------------------------------------------------------------------------
// PkgSystemUserDataAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgSystemUserDataAck& p)
{
    WriteHeader(buf, p); buf << p.xData; return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgSystemUserDataAck& p)
{
    ReadHeader(buf, p); buf >> p.xData; return buf;
}

// ---------------------------------------------------------------------------
// PkgSystemExtUserDataAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgSystemExtUserDataAck& p)
{
    WriteHeader(buf, p); buf << p.cIndex << p.xData; return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgSystemExtUserDataAck& p)
{
    ReadHeader(buf, p); buf >> p.cIndex >> p.xData; return buf;
}

// ---------------------------------------------------------------------------
// PkgUserActionReq
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgUserActionReq& p)
{
    WriteHeader(buf, p);
    buf << p.bAction << p.wPosX << p.wPosY << p.bDir << p.dwParam;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgUserActionReq& p)
{
    ReadHeader(buf, p);
    buf >> p.bAction >> p.wPosX >> p.wPosY >> p.bDir >> p.dwParam;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgObjectActionNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgObjectActionNot& p)
{
    WriteHeader(buf, p);
    buf << p.dwID << p.bAction << p.wPosX << p.wPosY << p.bDir << p.dwParam;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgObjectActionNot& p)
{
    ReadHeader(buf, p);
    buf >> p.dwID >> p.bAction >> p.wPosX >> p.wPosY >> p.bDir >> p.dwParam;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerLoginExtDataReq
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerLoginExtDataReq& p)
{
    WriteHeader(buf, p); buf << p.cIndex << p.xData; return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerLoginExtDataReq& p)
{
    ReadHeader(buf, p); buf >> p.cIndex >> p.xData; return buf;
}

// ---------------------------------------------------------------------------
// PkgObjectActionWalkNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgObjectActionWalkNot& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.uUserId << p.wPosX << p.wPosY << p.bDir << p.dwPos;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgObjectActionWalkNot& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.uUserId >> p.wPosX >> p.wPosY >> p.bDir >> p.dwPos;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgObjectActionRunNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgObjectActionRunNot& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.uUserId << p.wPosX << p.wPosY << p.bDir << p.dwPos;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgObjectActionRunNot& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.uUserId >> p.wPosX >> p.wPosY >> p.bDir >> p.dwPos;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgObjectActionTurnNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgObjectActionTurnNot& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.uUserId << p.wPosX << p.wPosY << p.bDir;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgObjectActionTurnNot& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.uUserId >> p.wPosX >> p.wPosY >> p.bDir;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgGameSyncDataNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgGameSyncDataNot& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.nType;
    unsigned int n = (unsigned int)p.vecVals.size();
    buf << n;
    for (unsigned int i = 0; i < n; ++i) buf << p.vecVals[i];
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgGameSyncDataNot& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.nType;
    unsigned int n = 0; buf >> n;
    p.vecVals.resize(n);
    for (unsigned int i = 0; i < n; ++i) buf >> p.vecVals[i];
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerBuyOlShopItemAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerBuyOlShopItemAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.nItemId << p.nRet;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerBuyOlShopItemAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.nItemId >> p.nRet;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerChangeEquipNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerChangeEquipNot& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId;
    buf.Write(&p.stItem, sizeof(ItemAttrib));
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerChangeEquipNot& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId;
    buf.Read(&p.stItem, sizeof(ItemAttrib));
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerChangeMapAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerChangeMapAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.dwMapID << p.wPosX << p.wPosY;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerChangeMapAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.dwMapID >> p.wPosX >> p.wPosY;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerChangeMonsLookAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerChangeMonsLookAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.uMonsId << p.uLook << p.dwChg;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerChangeMonsLookAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.uMonsId >> p.uLook >> p.dwChg;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerChargeRsp
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerChargeRsp& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.nResult;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerChargeRsp& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.nResult;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerChargeReq
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerChargeReq& p)
{
    WriteHeader(buf, p);
    buf << p.xOrderId;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerChargeReq& p)
{
    ReadHeader(buf, p);
    buf >> p.xOrderId;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerClearBagNtf
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerClearBagNtf& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.dwTag;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerClearBagNtf& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.dwTag;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerClickNPCAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerClickNPCAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.uNPCId << p.uUserId << p.dwNPCID << p.dwParam << p.nResult;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerClickNPCAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.uNPCId >> p.uUserId >> p.dwNPCID >> p.dwParam >> p.nResult;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerCubeItemsReq
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerCubeItemsReq& p)
{
    WriteHeader(buf, p);
    unsigned int n = (unsigned int)p.xTags.size();
    buf << n;
    for (unsigned int i = 0; i < n; ++i) buf << p.xTags[i];
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerCubeItemsReq& p)
{
    ReadHeader(buf, p);
    unsigned int n = 0; buf >> n;
    p.xTags.resize(n);
    for (unsigned int i = 0; i < n; ++i) buf >> p.xTags[i];
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerDialogDataAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerDialogDataAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.nType << p.xData;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerDialogDataAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.nType >> p.xData;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerDressItemAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerDressItemAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.bRet << p.bPos << p.dwTag << p.dwTex << p.uUserId << p.dwFlag;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerDressItemAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.bRet >> p.bPos >> p.dwTag >> p.dwTex >> p.uUserId >> p.dwFlag;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerEnableSkillNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerEnableSkillNot& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.nSkillId << p.bLevel << p.bEnabled;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerEnableSkillNot& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.nSkillId >> p.bLevel >> p.bEnabled;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerForceActionAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerForceActionAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.bType << p.dwData;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerForceActionAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.bType >> p.dwData;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerForgeItemReq
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerForgeItemReq& p)
{
    WriteHeader(buf, p);
    unsigned int n = (unsigned int)p.xItems.size();
    buf << n;
    for (unsigned int i = 0; i < n; ++i) buf << p.xItems[i];
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerForgeItemReq& p)
{
    ReadHeader(buf, p);
    unsigned int n = 0; buf >> n;
    p.xItems.resize(n);
    for (unsigned int i = 0; i < n; ++i) buf >> p.xItems[i];
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerGainItemNtf
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerGainItemNtf& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId;
    buf.Write(&p.stItem, sizeof(ItemAttrib));
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerGainItemNtf& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId;
    buf.Read(&p.stItem, sizeof(ItemAttrib));
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerGetBaleItemAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerGetBaleItemAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.dwTagBeg << p.dwID;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerGetBaleItemAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.dwTagBeg >> p.dwID;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerGetOlShopListAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerGetOlShopListAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId;
    unsigned int n = (unsigned int)p.xItemsId.size();
    buf << n;
    for (unsigned int i = 0; i < n; ++i) buf << p.xItemsId[i];
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerGetOlShopListAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId;
    unsigned int n = 0; buf >> n;
    p.xItemsId.resize(n);
    for (unsigned int i = 0; i < n; ++i) buf >> p.xItemsId[i];
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerLostItemAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerLostItemAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.dwTag;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerLostItemAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.dwTag;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerOffSellListNtf
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerOffSellListNtf& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.bPage;
    unsigned int n = (unsigned int)p.xItems.size();
    buf << n;
    for (unsigned int i = 0; i < n; ++i) buf.Write(&p.xItems[i], sizeof(SellItem));
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerOffSellListNtf& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.bPage;
    unsigned int n = 0; buf >> n;
    p.xItems.resize(n);
    for (unsigned int i = 0; i < n; ++i) buf.Read(&p.xItems[i], sizeof(SellItem));
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerOffSoldItemAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerOffSoldItemAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.xItemName << p.xBuyerName << p.dwMoney << p.dwGold;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerOffSoldItemAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.xItemName >> p.xBuyerName >> p.dwMoney >> p.dwGold;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerPlayAniAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerPlayAniAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.uUserId << p.wAniID;
    unsigned int n = (unsigned int)p.xPos.size();
    buf << n;
    for (std::list<unsigned int>::const_iterator it = p.xPos.begin(); it != p.xPos.end(); ++it) buf << *it;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerPlayAniAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.uUserId >> p.wAniID;
    unsigned int n = 0; buf >> n;
    p.xPos.clear();
    for (unsigned int i = 0; i < n; ++i) { unsigned int v = 0; buf >> v; p.xPos.push_back(v); }
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerPrivateChatAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerPrivateChatAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.bOnline << p.xPeerName;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerPrivateChatAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.bOnline >> p.xPeerName;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerPrivateChatNtf
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerPrivateChatNtf& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.xSender << p.xMsg;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerPrivateChatNtf& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.xSender >> p.xMsg;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerPrivateChatReq
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerPrivateChatReq& p)
{
    WriteHeader(buf, p);
    buf << p.xPeerName << p.xMsg;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerPrivateChatReq& p)
{
    ReadHeader(buf, p);
    buf >> p.xPeerName >> p.xMsg;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerQuestDataNtf
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerQuestDataNtf& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.xData;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerQuestDataNtf& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.xData;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerQuickMsgNtf
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerQuickMsgNtf& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.nMsgID << p.nParam;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerQuickMsgNtf& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.nMsgID >> p.nParam;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerRankListNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerRankListNot& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.xData;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerRankListNot& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.xData;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerReviveNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerReviveNot& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.uHp << p.bMode;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerReviveNot& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.uHp >> p.bMode;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerSayNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerSayNot& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.xMsg << p.uColor;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerSayNot& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.xMsg >> p.uColor;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerSayReq
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerSayReq& p)
{
    WriteHeader(buf, p);
    buf << p.uType << p.xWords;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerSayReq& p)
{
    ReadHeader(buf, p);
    buf >> p.uType >> p.xWords;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerServerDelayReq
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerServerDelayReq& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.nSeq << p.dwTimeStamp << p.uTick;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerServerDelayReq& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.nSeq >> p.dwTimeStamp >> p.uTick;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerSetEffectAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerSetEffectAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.dwMgcID << p.dwParam << p.bShow << p.dwTime;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerSetEffectAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.dwMgcID >> p.dwParam >> p.bShow >> p.dwTime;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerShowDlgAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerShowDlgAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.bType;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerShowDlgAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.bType;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerShowDoorAniAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerShowDoorAniAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.uUserId << p.wMgcID << p.dwPos << p.wPosX << p.wPosY;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerShowDoorAniAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.uUserId >> p.wMgcID >> p.dwPos >> p.wPosX >> p.wPosY;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerShowHelpAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerShowHelpAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.nHelpID;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerShowHelpAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.nHelpID;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerShowShopAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerShowShopAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.nShopType << p.bType << p.uUserId;
    unsigned int n = (unsigned int)p.xItems.size();
    buf << n;
    for (unsigned int i = 0; i < n; ++i) buf << p.xItems[i];
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerShowShopAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.nShopType >> p.bType >> p.uUserId;
    unsigned int n = 0; buf >> n;
    p.xItems.resize(n);
    for (unsigned int i = 0; i < n; ++i) buf >> p.xItems[i];
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerSmeltMaterialsReq
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerSmeltMaterialsReq& p)
{
    WriteHeader(buf, p);
    buf << p.nType;
    unsigned int n = (unsigned int)p.xItemsTag.size();
    buf << n;
    for (unsigned int i = 0; i < n; ++i) buf << p.xItemsTag[i];
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerSmeltMaterialsReq& p)
{
    ReadHeader(buf, p);
    buf >> p.nType;
    unsigned int n = 0; buf >> n;
    p.xItemsTag.resize(n);
    for (unsigned int i = 0; i < n; ++i) buf >> p.xItemsTag[i];
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerSmeltMaterialsRsp
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerSmeltMaterialsRsp& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.nCode;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerSmeltMaterialsRsp& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.nCode;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerStoreDataAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerStoreDataAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.xData;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerStoreDataAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.xData;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerStoreSyncAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerStoreSyncAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.bType << p.dwTag;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerStoreSyncAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.bType >> p.dwTag;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerStruckAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerStruckAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.nDamage << p.bType;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerStruckAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.nDamage >> p.bType;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerSyncQuestNtf
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerSyncQuestNtf& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.bStage << p.bCounter << p.bStep << p.xData;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerSyncQuestNtf& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.bStage >> p.bCounter >> p.bStep >> p.xData;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerUndressItemAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerUndressItemAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.bRet << p.bPos << p.dwTag;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerUndressItemAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.bRet >> p.bPos >> p.dwTag;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerUpdateAttribNtf
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerUpdateAttribNtf& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.bType << p.uAction << p.dwParam;
    buf << p.uParam0 << p.uParam1 << p.uParam2 << p.uParam3 << p.dwExtra;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerUpdateAttribNtf& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.bType >> p.uAction >> p.dwParam;
    buf >> p.uParam0 >> p.uParam1 >> p.uParam2 >> p.uParam3 >> p.dwExtra;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerUpdateCostNtf
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerUpdateCostNtf& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.dwTag << p.nCount << p.bSelfUse << p.bBind;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerUpdateCostNtf& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.dwTag >> p.nCount >> p.bSelfUse >> p.bBind;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerUpdateItemNtf
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerUpdateItemNtf& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.nBagIndex;
    buf.Write(&p.stItem, sizeof(ItemAttrib));
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerUpdateItemNtf& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.nBagIndex;
    buf.Read(&p.stItem, sizeof(ItemAttrib));
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerUpdateRandSeedNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerUpdateRandSeedNot& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.nType << p.dwSeed << p.uSeedType << p.uSeed;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerUpdateRandSeedNot& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.nType >> p.dwSeed >> p.uSeedType >> p.uSeed;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerUpdateWeaponGrowNtf
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerUpdateWeaponGrowNtf& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.dwTag << p.dwData << p.dwGrowData << p.nLevel;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerUpdateWeaponGrowNtf& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.dwTag >> p.dwData >> p.dwGrowData >> p.nLevel;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerUseItemAck
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerUseItemAck& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.dwUsage << p.dwTag;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerUseItemAck& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.dwUsage >> p.dwTag;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerVersionVerifyNtf
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerVersionVerifyNtf& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.xVersion;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerVersionVerifyNtf& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.xVersion;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerVipNot
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerVipNot& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.dwID << p.nVipLevel;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerVipNot& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.dwID >> p.nVipLevel;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgSystemClearGroundItemNtf
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgSystemClearGroundItemNtf& p)
{
    WriteHeader(buf, p);
    buf << p.uTargetId << p.dwTag;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgSystemClearGroundItemNtf& p)
{
    ReadHeader(buf, p);
    buf >> p.uTargetId >> p.dwTag;
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerChangeEquipReq
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerChangeEquipReq& p)
{
    WriteHeader(buf, p);
    buf.Write(&p.stItem, sizeof(ItemAttrib));
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerChangeEquipReq& p)
{
    ReadHeader(buf, p);
    buf.Read(&p.stItem, sizeof(ItemAttrib));
    return buf;
}

// ---------------------------------------------------------------------------
// PkgPlayerWorldSayReq
// ---------------------------------------------------------------------------
ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerWorldSayReq& p)
{
    WriteHeader(buf, p);
    buf << p.xMsg << p.uReserved;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerWorldSayReq& p)
{
    ReadHeader(buf, p);
    buf >> p.xMsg >> p.uReserved;
    return buf;
}

ByteBuffer& operator<<(ByteBuffer& buf, const PkgPlayerWorldSayNot& p)
{
    WriteHeader(buf, p);
    buf << p.xMsg;
    return buf;
}
ByteBuffer& operator>>(ByteBuffer& buf, PkgPlayerWorldSayNot& p)
{
    ReadHeader(buf, p);
    buf >> p.xMsg;
    return buf;
}
