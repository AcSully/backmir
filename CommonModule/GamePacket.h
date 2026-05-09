// [reconstructed] �ؽ��� 2026-05-06 ���� ��Դ���õ㣺
//   BMServer/tolua/GamePacket.pkg (opcode enum, struct declarations)
//   BMClient/Net/PacketHandler.cpp (packet dispatch)
//   BMServer/CMainServer/CMainServer.cpp (login/server packet structs)
//   BMServer/GameWorld/HeroObject.cpp (game packet structs)
//   BMServer/GameWorld/HeroObject_Packet.cpp (game packet structs)
//   BMClient/BackMir/BMPreConnWnd.cpp (login packet structs)
//
// ��ͷ��ʽ��ByteBuffer �ڴ沼�֣���
//   [uint32 total-length (big-endian)][uint32 opcode][payload]
// GET_PACKET_OP(buf)        : �� ByteBuffer ƫ�� 4 ��ȡ opcode����������ͨ�ţ�
// GET_PACKET_OP_CLIENT(buf) : �� ByteBuffer ƫ�� 4 ��ȡ LOWORD(opcode)���ͻ��ˡ�����������16λΪУ��ͣ�
#pragma once
#ifndef _INC_GAMEPACKET_
#define _INC_GAMEPACKET_

#include "ByteBuffer.h"
#include "platform_compat.h"
#ifdef _WIN32
#  include <windows.h>
#endif
#include <string>
#include <vector>
#include <set>
#include <list>
#include "ObjectData.h"
#include "OfflineSellSystem.h"

// ---------------------------------------------------------------------------
// ��ͷ��ȡ��
// ---------------------------------------------------------------------------
#define GET_PACKET_OP(buf)         (*(const unsigned int*)((buf).GetBuffer() + 4))
#define GET_PACKET_OP_CLIENT(buf)  (LOWORD(*(const unsigned int*)((buf).GetBuffer() + 4)))

// ---------------------------------------------------------------------------
// Opcode ö��
// ---------------------------------------------------------------------------
enum GamePacketCode
{
    GAME_PKG_HEADER = 0,

    // ϵͳ��¼��
    PKG_SYSTEM_START            = 100,
    PKG_SYSTEM_USERLOGIN_REQ,
    PKG_SYSTEM_USERLOGIN_ACK,
    PKG_SYSTEM_NEWNPC_NOT,
    PKG_SYSTEM_NEWPLAYER_NOT,
    PKG_SYSTEM_FORCE_ACTION_ACK,
    PKG_SYSTEM_USERDATA_ACK,
    PKG_SYSTEM_NEWITEM_NOT,
    PKG_SYSTEM_DELITEM_NOT,
    PKG_SYSTEM_DELNPC_NOT,
    PKG_SYSTEM_CLEARITEM_NTF,
    PKG_SYSTEM_NOTIFY_NOT,
    PKG_SYSTEM_NOTIFY_REQ,
    PKG_SYSTEM_CLIENTVERSIONERR_NTF,
    PKG_SYSTEM_HIDEDOOR_NTF,
    PKG_SYSTEM_WORLD_SAY_NOT,
    PKG_SYSTEM_EXT_USERDATA_ACK,
    PKG_SYSTEM_END,

    // ��Ϸ��
    PKG_GAME_START              = 999,
    PKG_GAME_OBJECT_ACTION_NOT,
    PKG_GAME_USER_ACTION_REQ,
    PKG_GAME_SERVERSTATUS_REQ,
    PKG_GAME_SERVERSTATUS_ACK,
    PKG_GAME_PLAYER_SAY_REQ,
    PKG_GAME_CHAT_NOT,
    PKG_GAME_PLAYER_CHANGEEQUIPMENT_REQ,
    PKG_GAME_PLAYER_CHANGEEQUIPMENT_NOT,
    PKG_GAME_PLAYER_DROPITEM_NOT,
    PKG_GAME_PLAYER_DROPITEM_REQ,
    PKG_GAME_PLAYER_SYNCITEM_REQ,
    PKG_GAME_PLAYER_GAINITEM_NTF,
    PKG_GAME_PLAYER_LOSTITEM_ACK,
    PKG_GAME_PLAYER_PICKUPITEM_REQ,
    PKG_GAME_PLAYER_CLEARITEM_NTF,
    PKG_GAME_PLAYER_CLEARBAG_NTF,
    PKG_GAME_PLAYER_SYNCATTRIB_NTF,
    PKG_GAME_PLAYER_UNDRESSITEM_REQ,
    PKG_GAME_PLAYER_UNDRESSITEM_ACK,
    PKG_GAME_PLAYER_DRESSITEM_REQ,
    PKG_GAME_PLAYER_DRESSITEM_ACK,
    PKG_GAME_PLAYER_USEITEM_REQ,
    PKG_GAME_PLAYER_USEITEM_ACK,
    PKG_GAME_PLAYER_UPDATEATTRIB_NTF,
    PKG_GAME_PLAYER_CLICKNPC_REQ,
    PKG_GAME_PLAYER_CLICKNPC_ACK,
    PKG_GAME_PLAYER_DIALOGDATA_ACK,
    PKG_GAME_PLAYER_SHOWDLG_ACK,
    PKG_GAME_PLAYER_SHOWSHOP_ACK,
    PKG_GAME_PLAYER_SHOPOP_REQ,
    PKG_GAME_PLAYER_ATTACK_REQ,
    PKG_GAME_PLAYER_STRUCK_ACK,
    PKG_GAME_PLAYER_REVIVE_REQ,
    PKG_GAME_PLAYER_REVIVE_NOT,
    PKG_GAME_PLAYER_CHANGEMAP_ACK,
    PKG_GAME_PLAYER_USERDATA_REQ,
    PKG_GAME_PLAYER_RANKLIST_REQ,
    PKG_GAME_PLAYER_RANKLIST_NOT,
    PKG_GAME_PLAYER_PRIVATECHAT_REQ,
    PKG_GAME_PLAYER_PRIVATECHAT_ACK,
    PKG_GAME_PLAYER_PRIVATECHAT_NTF,
    PKG_GAME_PLAYER_SAY_NOT,
    PKG_GAME_PLAYER_WORLD_SAY_REQ,
    PKG_GAME_PLAYER_NETDELAY_REQ,
    PKG_GAME_PLAYER_NETDELAY_ACK,
    PKG_GAME_PLAYER_SERVERDELAY_REQ,
    PKG_GAME_PLAYER_SERVERDELAY_ACK,
    PKG_GAME_PLAYER_FORGEITEM_REQ,
    PKG_GAME_PLAYER_IDENTIFYITEM_REQ,
    PKG_GAME_PLAYER_SPLITITEM_REQ,
    PKG_GAME_PLAYER_SYNCASSIST_REQ,
    PKG_GAME_PLAYER_QUITSELCHR_REQ,
    PKG_GAME_PLAYER_QUITSELCHR_RSP,
    PKG_GAME_PLAYER_LOGINEXTDATA_REQ,
    PKG_GAME_PLAYER_EXTENDATTRIB_NOT,
    PKG_GAME_PLAYER_ENABLESKILL_NOT,
    PKG_GAME_PLAYER_QUESTDATA_NTF,
    PKG_GAME_PLAYER_QUICKMSG_NTF,
    PKG_GAME_PLAYER_GSTATUS_NTF,
    PKG_GAME_PLAYER_UPDATEITEM_NTF,
    PKG_GAME_PLAYER_UPDATECOSTITEM_NTF,
    PKG_GAME_PLAYER_UPDATEWEAPONGROW_NTF,
    PKG_GAME_PLAYER_STOREDATA_ACK,
    PKG_GAME_PLAYER_STORESYNC_ACK,
    PKG_GAME_PLAYER_SHOWHELP_ACK,
    PKG_GAME_PLAYER_HIDEQUESTDLG_ACK,
    PKG_GAME_PLAYER_INTERACTIVEDIALOGCONTENT_NOT,
    PKG_GAME_PLAYER_SETEFFECT_ACK,
    PKG_GAME_PLAYER_PLAYANI_ACK,
    PKG_GAME_PLAYER_PLAYSOUND_NTF,
    PKG_GAME_PLAYER_SHOWDOORANI_ACK,
    PKG_GAME_PLAYER_CHANGEMONSLOOK_ACK,
    PKG_GAME_PLAYER_CLEARALLITEM_ACK,
    PKG_GAME_PLAYER_GETBALEITEM_ACK,
    PKG_GAME_PLAYER_OTHERPLAYEREQUIP_NTF,
    PKG_GAME_PLAYER_VERSIONVERIFY_NTF,
    PKG_GAME_PLAYER_UID_NTF,
    PKG_GAME_PLAYER_UPDATE_RANDSEED_NOT,
    PKG_GAME_PLAYER_DIFFICULTYLEVEL_REQ,
    PKG_GAME_PLAYER_DIFFICULTYLEVEL_RSP,
    PKG_GAME_PLAYER_SMELTMATERIALS_REQ,
    PKG_GAME_PLAYER_SMELTMATERIALS_RSP,
    PKG_GAME_PLAYER_OPEN_POTENTIAL_REQ,
    PKG_GAME_PLAYER_OPEN_POTENTIAL_RSP,
    PKG_GAME_PLAYER_UNBINDITEM_REQ,
    PKG_GAME_PLAYER_DECOMPOSE_REQ,
    PKG_GAME_PLAYER_CUBEITEMS_REQ,
    PKG_GAME_PLAYER_HAND_MAKE_ITEM_REQ,
    PKG_GAME_PLAYER_MERGYCOSTITEM_REQ,
    PKG_GAME_PLAYER_SPEOPERATE_REQ,
    PKG_GAME_PLAYER_MONSINFO_REQ,
    PKG_GAME_PLAYER_CHARGE_REQ,
    PKG_GAME_PLAYER_GETOLSHOPLIST_REQ,
    PKG_GAME_PLAYER_GETOLSHOPLIST_ACK,
    PKG_GAME_PLAYER_BUYOLSHOPITEM_REQ,
    PKG_GAME_PLAYER_BUYOLSHOPITEM_ACK,
    PKG_GAME_PLAYER_OFFSELLITEM_REQ,
    PKG_GAME_PLAYER_OFFGETLIST_REQ,
    PKG_GAME_PLAYER_OFFSELLLIST_NTF,
    PKG_GAME_PLAYER_OFFBUYITEM_REQ,
    PKG_GAME_PLAYER_OFFSOLDITEM_ACK,
    PKG_GAME_PLAYER_OFFTAKEBACK_REQ,
    PKG_GAME_PLAYER_OFFCHECKSOLD_REQ,
    PKG_GAME_PLAYER_CALLSLAVE_REQ,
    PKG_GAME_PLAYER_KILLSLAVE_REQ,
    PKG_GAME_PLAYER_SLAVE_STOP_REQ,
    PKG_GAME_PLAYER_FORCEACTION_ACK,
    PKG_GAME_GM_NOTIFICATION_NOT,
    PKG_GAME_GM_NOTIFICATION_REQ,
    PKG_GAME_OBJECT_ACTION_WALK_NOT,
    PKG_GAME_OBJECT_ACTION_RUN_NOT,
    PKG_GAME_OBJECT_ACTION_TURN_NOT,
    PKG_GAME_OBJECT_ACTION_ATTACK_NOT,
    PKG_GAME_OBJECT_ACTION_DEAD_NOT,
    PKG_GAME_OBJECT_ACTION_EXT_NOT,
    PKG_GAME_OBJECT_ACTIONS_NOT,
    PKG_GAME_SYNCDATA_NOT,
    PKG_GAME_LOADED,
    PKG_GAME_MONSTER_FIREDRAGON_ATTACK0_NOT,
    PKG_GAME_PLAYER_SYNCQUEST_NTF,
    PKG_GAME_PLAYER_SUIT_IGNORE_NOT,
    PKG_GAME_END,

    GAME_PKG_END,
};

// ---------------------------------------------------------------------------
// ��¼������ <-> �ͻ��� �� opcode���ɰ� ByteBuffer Э�飩
// ---------------------------------------------------------------------------
enum LoginPacketCode
{
    PKG_LOGIN_START                 = 10000,
    PKG_LOGIN_GAMETYPE_NOT,         // LS/GS -> Client: ����������֪ͨ
    PKG_LOGIN_VERIFYRESULT_ACK,     // LS -> Client: ��֤���
    PKG_LOGIN_QUICKMSG_NOT,         // LS -> Client: ������Ϣ
    PKG_LOGIN_SERVERADDR_NOT,       // LS -> Client: ��Ϸ��������ַ��v1��
    PKG_LOGIN_SERVERADDRV2_RSP,     // LS -> Client: ��Ϸ�������б���v2��
    PKG_LOGIN_HEADDATA_NOT,         // LS -> Client: ��ɫͷ�����ݣ��ɰ棩
    PKG_LOGIN_ADDGAMEROLE_REQ,      // Client -> LS: ������ɫ���󣨾ɰ棩
    PKG_LOGIN_ADDGAMEROLE_ACK,      // LS -> Client: ������ɫ������ɰ棩
    PKG_LOGIN_DELGAMEROLE_REQ,      // Client -> LS: ɾ����ɫ���󣨾ɰ棩
    PKG_LOGIN_DELGAMEROLE_ACK,      // LS -> Client: ɾ����ɫ������ɰ棩
    PKG_LOGIN_STARTGAME_REQ,        // Client -> LS: ������Ϸ���󣨾ɰ棩
    PKG_LOGIN_CLIENTVERIFY_REQ,     // Client -> LS: �˺���֤���� v1
    PKG_LOGIN_CLIENTVERIFYV2_REQ,   // Client -> LS: �˺���֤���� v2
    PKG_LOGIN_HEARTBEAT_NOT,        // Client -> LS: ������

    // GS <-> LS �ڲ���
    PKG_LOGIN_CONNINDEX_NOT         = 10100,  // Client -> GS: ��������֪ͨ���ɰ棩
    PKG_LOGIN_SENDHUMDATA_NOT,      // LS -> GS: ���ͽ�ɫ����
    PKG_LOGIN_SENDHUMEXTDATA_NOT,   // LS -> GS: ���ͽ�ɫ��չ����
    PKG_LOGIN_ROLEDATAFROMGS_NOT,   // GS -> LS: ��ɫ���ݻ�д
    PKG_LOGIN_EXTROLEDATAFROMGS_NOT,// GS -> LS: ��ɫ��չ���ݻ�д
    PKG_LOGIN_HUMRANKLIST_NOT,      // LS -> GS: ���а�����
    PKG_LOGIN_CHECKBUYSHOPITEM_ACK, // LS -> GS: �����̳���Ʒ���
    PKG_LOGIN_CONSUMEDONATE_ACK,    // LS -> GS: ���Ѿ������
    PKG_LOGIN_SCHEDULE_ACTIVE_RSP,  // LS -> GS: ��ʱ���񴥷�
    PKG_LOGIN_SERVERVERIFYV2_REQ,   // GS -> LS: ��������֤ v2
    PKG_LOGIN_END,
};

// ---------------------------------------------------------------------------
// ��¼����ö��
// ---------------------------------------------------------------------------
enum PlayerLoginGameTypeNot
{
    PLGTN_GAMESERVER  = 1,
    PLGTN_LOGINSERVER = 2,
};

// ---------------------------------------------------------------------------
// ��ɫͷ��Ϣ �� defined in ObjectData.h; forward-declared here
// ---------------------------------------------------------------------------
// (HeroHeader is defined in ObjectData.h which is included later in this file)

// ---------------------------------------------------------------------------
// ��ͷ�ṹ
// PacketHeader: ��������ͨ�Ű�ͷ
// LoginHeader:  ��Ϸ���������ͻ��˰�ͷ���� PacketHeader ��ͬ���֣�
// ---------------------------------------------------------------------------
struct PacketHeader
{
    unsigned int uLen;  // ���ܳ��ȣ���������
    unsigned int uOp;   // opcode����������ͨ��ʱ��16λΪУ��ͣ�
    unsigned int uTargetId;  // target object ID (used by some packets)
};

typedef PacketHeader LoginHeader;

// ---------------------------------------------------------------------------
// ByteBuffer ���л�������
// ---------------------------------------------------------------------------
#define DECLARE_WRITE(pkg)      ByteBuffer& operator<<(ByteBuffer& _buf, const pkg& _pkg)
#define DECLARE_READ(pkg)       ByteBuffer& operator>>(ByteBuffer& _buf, pkg& _pkg)
#define DECLARE_READWRITE(pkg)  DECLARE_WRITE(pkg); DECLARE_READ(pkg)

// ---------------------------------------------------------------------------
// ��¼������ <-> �ͻ��� ���ṹ���ɰ� ByteBuffer Э�飩
// ---------------------------------------------------------------------------

// GS/LS -> Client: ����������֪ͨ
struct PkgLoginGameTypeNot : public PacketHeader
{
    BYTE         bType;      // PLGTN_GAMESERVER or PLGTN_LOGINSERVER
    unsigned int dwConnIdx;  // ����������LS ���䣩
};
DECLARE_READWRITE(PkgLoginGameTypeNot);

// LS -> Client: ��֤���
struct PkgLoginVerifyResultAck : public PacketHeader
{
    BYTE bResult;
};
DECLARE_READWRITE(PkgLoginVerifyResultAck);

// LS -> Client: ������Ϣ
struct PkgLoginQuickMsgNot : public PacketHeader
{
    unsigned int uMsg;
};
DECLARE_READWRITE(PkgLoginQuickMsgNot);

// LS -> Client: ��Ϸ��������ַ��v1��
struct PkgLoginServerAddrNot : public PacketHeader
{
    std::string xAddr;  // "ip:port"
};
DECLARE_READWRITE(PkgLoginServerAddrNot);

// LS -> Client: ��Ϸ�������б���v2��
struct PkgLoginServerAddrV2Not : public PacketHeader
{
    std::vector<std::string> vecServers;  // "serverid_addr_name"
};
DECLARE_READWRITE(PkgLoginServerAddrV2Not);

// Client -> GS: ��������֪ͨ���ɰ棩
struct PkgLoginConnIdxNot : public PacketHeader
{
    unsigned int dwLSIdx;
    unsigned int dwGSIdx;
};
DECLARE_READWRITE(PkgLoginConnIdxNot);

// GS -> LS: ��������֪ͨ���������룩
struct PkgLoginGsConnIdxNot : public PacketHeader
{
    unsigned int dwConnCode;
    unsigned int dwLSIdx;
    unsigned int dwGSIdx;
};
DECLARE_READWRITE(PkgLoginGsConnIdxNot);

// Client -> GS: ѡ���������Ӧ
struct PkgLoginClientSelGSRsp : public PacketHeader
{
    short uGSServerID;
};
DECLARE_READWRITE(PkgLoginClientSelGSRsp);

// Client -> LS: ������
struct PkgLoginHeartBeatNot : public PacketHeader
{
};
DECLARE_READWRITE(PkgLoginHeartBeatNot);

// ---------------------------------------------------------------------------
// GS <-> LS �ڲ����ṹ
// ---------------------------------------------------------------------------

// LS -> GS: ���ͽ�ɫ����
struct PkgLoginSendHumDataNot : public PacketHeader
{
    unsigned int    dwPlayerIndex;  // GS ������ ID
    unsigned int    dwLSIndex;      // LS ������ ID
    unsigned int    dwUID;
    unsigned int    dwConnCode;
    HeroHeader      stHeader;
    std::vector<char> xData;
    std::string     xExtendInfo;    // JSON ��չ����
};
DECLARE_READWRITE(PkgLoginSendHumDataNot);

// LS -> GS: ���ͽ�ɫ��չ����
struct PkgLoginSendHumExtDataNot : public PacketHeader
{
    unsigned int    dwPlayerIndex;
    unsigned int    dwLSIndex;
    unsigned int    dwUID;
    unsigned int    dwConnCode;
    char            cExtIndex;
    std::vector<char> xData;
};
DECLARE_READWRITE(PkgLoginSendHumExtDataNot);

// LS -> GS: ���а�����
struct PkgLoginHumRankListNot : public PacketHeader
{
    std::string xData;  // JSON ���л����а�
};
DECLARE_READWRITE(PkgLoginHumRankListNot);

// LS -> GS: �����̳���Ʒ���
struct PkgLoginCheckBuyShopItemAck : public PacketHeader
{
    char cRet;
    int  nItemId;
    int  nQueryId;
    int  nUid;
    int  nGsId;
};
DECLARE_READWRITE(PkgLoginCheckBuyShopItemAck);

// GS -> LS: �����̳���Ʒ����
struct PkgLoginCheckBuyShopItemReq : public PacketHeader
{
    int nItemId;
    int nCost;
    int nGsId;
    int nUid;
    int nQueryId;
};
DECLARE_READWRITE(PkgLoginCheckBuyShopItemReq);

// LS -> GS: ���Ѿ������
struct PkgLoginConsumeDonateAck : public PacketHeader
{
    char cRet;
    int  nItemId;
    int  nUid;
    int  nGsId;
    int  nDonateLeft;
};
DECLARE_READWRITE(PkgLoginConsumeDonateAck);

// GS -> LS: ���Ѿ�������
struct PkgLoginConsumeDonateReq : public PacketHeader
{
    int         nCost;
    int         nGsId;
    int         nItemId;
    int         nUid;
    std::string xName;
};
DECLARE_READWRITE(PkgLoginConsumeDonateReq);

// LS -> GS: ��ʱ���񴥷�
struct PkgLoginScheduleActiveRsp : public PacketHeader
{
    int nEventId;
};
DECLARE_READWRITE(PkgLoginScheduleActiveRsp);

// GS -> LS: ע�ᶨʱ������ע�͵��������ṹ��
struct PkgLoginRegisterScheduleReq : public PacketHeader
{
    int         nEventId;
    std::string xCronExpr;
};
DECLARE_READWRITE(PkgLoginRegisterScheduleReq);

// GS -> LS: ��ɫ״̬����֪ͨ
enum RoleUpdateType { RoleUpdateTypeLogout = 0, RoleUpdateTypeLogin = 1 };
struct PkgLoginGSRoleUpdateNtf : public PacketHeader
{
    int         nUID;
    std::string xName;
    int         sType;  // RoleUpdateType
};
DECLARE_READWRITE(PkgLoginGSRoleUpdateNtf);

// GS -> LS: �������а����󣨾ɰ� ByteBuffer��
struct PkgLoginUpdateHumRankReq : public PacketHeader
{
    int         nUid;
    char        cJob;
    int         nLevel;
    std::string xName;
    int         nPower;
    int         nServerId;
};
DECLARE_READWRITE(PkgLoginUpdateHumRankReq);

// ---------------------------------------------------------------------------
// ϵͳ���ṹ
// ---------------------------------------------------------------------------

// GS -> Client: �û���¼���
struct PkgUserLoginAck : public PacketHeader
{
    bool         bOk;
    int          nId;       // ���� ID
    unsigned int uVersion;
    std::vector<char> xMsg; // ѹ����Ľ�ɫ����
};
DECLARE_READWRITE(PkgUserLoginAck);

// Client -> GS: �û���¼����
struct PkgUserLoginReq : public PacketHeader
{
    HeroHeader        stHeader;
    std::vector<char> xData;
};
DECLARE_READWRITE(PkgUserLoginReq);

// GS -> Client: ǿ�ƶ������
struct PkgForceActionAck : public PacketHeader
{
    int nAction;
    int nParam;
    int nType;
};
DECLARE_READWRITE(PkgForceActionAck);

// GS -> Client: �����֪ͨ
struct PkgNewPlayerNot : public PacketHeader
{
    unsigned int dwID;
    char         szName[20];
    WORD         wPosX;
    WORD         wPosY;
    BYTE         bDir;
    BYTE         bJob;
    BYTE         bSex;
    WORD         uLevel;
    DWORD        dwLook1;
    DWORD        dwLook2;
    DWORD        dwSpeLook1;
    bool                    bNew;
    UserData                stData;
    std::vector<int>        xSkillInfo;
    unsigned int            uHandlerID;
};
DECLARE_READWRITE(PkgNewPlayerNot);

// GS -> Client: �� NPC ֪ͨ
struct PkgNewNPCNot : public PacketHeader
{
    unsigned int uHandlerID;   // object handler ID
    unsigned int uMonsID;      // monster/NPC attrib ID
    unsigned int uPosition;    // MAKELONG(posX, posY)
    unsigned int uParam;       // HP or other param
    unsigned int uFlag;        // elite/leader flags (MaxExpr)
    // legacy fields
    unsigned int dwID;
    char         szName[20];
    WORD         wPosX;
    WORD         wPosY;
    BYTE         bDir;
    int          nTemplateID;
};
DECLARE_READWRITE(PkgNewNPCNot);

// GS -> Client: ɾ�� NPC
struct PkgDelNPCNot : public PacketHeader
{
    unsigned int dwID;
    unsigned int uTargetId;
};
DECLARE_READWRITE(PkgDelNPCNot);

// GS -> Client: ����֪ͨ
struct PkgChatNot : public PacketHeader
{
    unsigned int uTargetId;
    std::string  xSender;
    std::string  xMsg;
    int          nChannel;
    unsigned int uExtra;
};
DECLARE_READWRITE(PkgChatNot);

// GS -> Client: GM ֪ͨ
struct PkgGmNotificationNot : public PacketHeader
{
    std::string xMsg;
};
DECLARE_READWRITE(PkgGmNotificationNot);

// Client -> GS: GM ֪ͨ����
struct PkgGmNotificationReq : public PacketHeader
{
    std::string xMsg;
};
DECLARE_READWRITE(PkgGmNotificationReq);

// GS -> Client: ϵͳ֪ͨ
struct PkgSystemNotifyNot : public PacketHeader
{
    std::string  xMsg;
    int          nType;
    unsigned int dwTimes;
    unsigned int dwColor;
};
DECLARE_READWRITE(PkgSystemNotifyNot);

// Client -> GS: ϵͳ֪ͨ����
struct PkgSystemNotifyReq : public PacketHeader
{
    std::string xMsg;
    unsigned int dwTimes;
    unsigned int dwColor;
};
DECLARE_READWRITE(PkgSystemNotifyReq);

// GS -> Client: �ͻ��˰汾����
struct PkgSystemClientVersionErrNtf : public PacketHeader
{
    int nVersion;
    std::string xServerVersion;
};
DECLARE_READWRITE(PkgSystemClientVersionErrNtf);

// GS -> Client: ������֪ͨ
struct PkgSystemHideDoorNtf : public PacketHeader
{
    WORD wPosX;
    WORD wPosY;
    BYTE bHide;
};
DECLARE_READWRITE(PkgSystemHideDoorNtf);

// GS -> Client: ���纰��֪ͨ
struct PkgSystemWorldSayNot : public PacketHeader
{
    std::string xName;
    std::string xMsg;
    unsigned int uReserved;
};
DECLARE_READWRITE(PkgSystemWorldSayNot);

// GS -> Client: �û����ݣ���ɫ�浵��
struct PkgSystemUserDataAck : public PacketHeader
{
    std::vector<char> xData;
};
DECLARE_READWRITE(PkgSystemUserDataAck);

// GS -> Client: �û���չ����
struct PkgSystemExtUserDataAck : public PacketHeader
{
    char              cIndex;
    int               nExtIndex;  // alias for cIndex (int form)
    std::vector<char> xData;
};
DECLARE_READWRITE(PkgSystemExtUserDataAck);

// ---------------------------------------------------------------------------
// ��Ϸ���ṹ�����֣������õ㲹�䣩
// ---------------------------------------------------------------------------

// Client -> GS: �û���������
struct PkgUserActionReq : public PacketHeader
{
    unsigned int uUserId;
    BYTE         bAction;
    BYTE         uAction;    // alias
    WORD         wPosX;
    WORD         wPosY;
    BYTE         bDir;
    DWORD        dwParam;
    DWORD        uParam0;    // alias
    DWORD        uParam1;
    DWORD        uParam2;
    DWORD        uParam3;
    unsigned int uTargetId;
};
DECLARE_READWRITE(PkgUserActionReq);

// GS -> Client: ������֪ͨ
struct PkgObjectActionNot : public PacketHeader
{
    unsigned int dwID;
    unsigned int uTargetId;  // alias for dwID
    BYTE         bType;
    unsigned int uUserId;    // attacker/source ID
    BYTE         bAction;
    BYTE         uAction;    // alias for bAction
    WORD         wPosX;
    WORD         wPosY;
    BYTE         bDir;
    DWORD        dwParam;
    DWORD        uParam0;    // alias for dwParam
    DWORD        uParam1;
    DWORD        uParam2;
    DWORD        uParam3;
};
DECLARE_READWRITE(PkgObjectActionNot);

// GS -> Client: ��ҵ�¼��չ��������
struct PkgPlayerLoginExtDataReq : public PacketHeader
{
    char              cIndex;
    std::vector<char> xData;
};
DECLARE_READWRITE(PkgPlayerLoginExtDataReq);

// GS -> Client: ����������֪ͨ��BroadcastQueue �ۺϷ��ͣ�
struct PkgObjectActionWalkNot : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int uUserId;
    WORD         wPosX;     // current position
    WORD         wPosY;
    BYTE         bDir;
    DWORD        dwPos;     // next position: MAKELONG(nextX, nextY)
};
DECLARE_READWRITE(PkgObjectActionWalkNot);

struct PkgObjectActionRunNot : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int uUserId;
    WORD         wPosX;
    WORD         wPosY;
    BYTE         bDir;
    DWORD        dwPos;
};
DECLARE_READWRITE(PkgObjectActionRunNot);

struct PkgObjectActionTurnNot : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int uUserId;
    WORD         wPosX;
    WORD         wPosY;
    BYTE         bDir;
};
DECLARE_READWRITE(PkgObjectActionTurnNot);

struct PkgObjectActionAttackNot : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int uUserId;
    WORD         wPosX;
    WORD         wPosY;
    BYTE         bDir;
};
DECLARE_READWRITE(PkgObjectActionAttackNot);
BYTEBUFFER_STRUCT_OPERATOR(PkgObjectActionAttackNot);

struct PkgObjectActionDeadNot : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int uUserId;
    WORD         wPosX;
    WORD         wPosY;
    BYTE         bDir;
};
DECLARE_READWRITE(PkgObjectActionDeadNot);
BYTEBUFFER_STRUCT_OPERATOR(PkgObjectActionDeadNot);

struct PkgObjectActionExtNot : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int uUserId;
    WORD         wPosX;
    WORD         wPosY;
    BYTE         bDir;
    char         cExtAction;
};
DECLARE_READWRITE(PkgObjectActionExtNot);
BYTEBUFFER_STRUCT_OPERATOR(PkgObjectActionExtNot);

// GS -> Client: �ۺ϶�������ѹ����� vecActions �ֽ�����
struct PkgGameObjectActionsNot : public PacketHeader
{
    unsigned int       uUserId;    // compression flag in bit 0
    std::vector<char>  vecActions;
};
DECLARE_READWRITE(PkgGameObjectActionsNot);
// ---------------------------------------------------------------------------

struct PkgServerStatusReq : public PacketHeader { unsigned int uSign; };
DECLARE_READWRITE(PkgServerStatusReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgServerStatusReq);
// Stub packet types �� fields reconstructed from call sites in HeroObject_Packet.cpp
// ---------------------------------------------------------------------------
struct PkgGameLoadedAck          : public PacketHeader { unsigned int uUserId; };
DECLARE_READWRITE(PkgGameLoadedAck);
BYTEBUFFER_STRUCT_OPERATOR(PkgGameLoadedAck);
struct PkgPlayerAttackReq        : public PacketHeader { unsigned int uTargetId; BYTE bMagicID; };
DECLARE_READWRITE(PkgPlayerAttackReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerAttackReq);
struct PkgPlayerBuyOlShopItemReq : public PacketHeader { unsigned int uUserId; int nItemId; int nQueryID; int cCount; };
DECLARE_READWRITE(PkgPlayerBuyOlShopItemReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerBuyOlShopItemReq);
struct PkgPlayerCallSlaveReq     : public PacketHeader { unsigned int uUserId; int nSlaveType; };
DECLARE_READWRITE(PkgPlayerCallSlaveReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerCallSlaveReq);
struct PkgPlayerChangeEquipReq   : public PacketHeader { ItemAttrib stItem; };
DECLARE_READWRITE(PkgPlayerChangeEquipReq);
struct PkgPlayerChargeReq        : public PacketHeader { unsigned int uUserId; std::string xOrderId; };
DECLARE_READWRITE(PkgPlayerChargeReq);
struct PkgPlayerClickNPCReq      : public PacketHeader { unsigned int uNPCId; unsigned int uTargetId; unsigned int uUserId; unsigned int dwButtonID; };
DECLARE_READWRITE(PkgPlayerClickNPCReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerClickNPCReq);
struct PkgPlayerCubeItemsReq     : public PacketHeader { unsigned int uUserId; std::vector<int> xTags; };
DECLARE_READWRITE(PkgPlayerCubeItemsReq);
struct PkgPlayerDecomposeReq     : public PacketHeader { unsigned int uUserId; unsigned int dwItemTag; };
DECLARE_READWRITE(PkgPlayerDecomposeReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerDecomposeReq);
struct PkgPlayerDifficultyLevelReq : public PacketHeader { char cLevel; };
DECLARE_READWRITE(PkgPlayerDifficultyLevelReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerDifficultyLevelReq);
struct PkgPlayerDressItemReq     : public PacketHeader { unsigned int uUserId; unsigned char bPos; unsigned int dwTag; };
DECLARE_READWRITE(PkgPlayerDressItemReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerDressItemReq);
struct PkgPlayerDropItemReq      : public PacketHeader { unsigned int uUserId; unsigned int dwId; int nCount; };
DECLARE_READWRITE(PkgPlayerDropItemReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerDropItemReq);
struct PkgPlayerForgeItemReq     : public PacketHeader { unsigned int uUserId; std::vector<int> xItems; };
DECLARE_READWRITE(PkgPlayerForgeItemReq);
struct PkgPlayerGetOlShopListReq : public PacketHeader { unsigned int uUserId; };
DECLARE_READWRITE(PkgPlayerGetOlShopListReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerGetOlShopListReq);
struct PkgPlayerGStatusNtf       : public PacketHeader {
    unsigned int uTargetId;
    int nStatus;
    std::vector<int> xStatus;
    std::vector<unsigned int> xTimes;
};
struct PkgPlayerHandMakeItemReq  : public PacketHeader { unsigned int uUserId; int nItemId; };
DECLARE_READWRITE(PkgPlayerHandMakeItemReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerHandMakeItemReq);
struct PkgPlayerIdentifyItemReq  : public PacketHeader { unsigned int dwTag; };
DECLARE_READWRITE(PkgPlayerIdentifyItemReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerIdentifyItemReq);
// Interactive dialog item types
enum InteractiveDialogItemType
{
    kInteractiveDialogItem_Button = 1,
    kInteractiveDialogItem_Text   = 2,
};

struct InteractiveDialogItem
{
    int          nX;
    int          nY;
    unsigned int uType;
    unsigned int uId;
    std::string  xText;
};

struct PkgPlayerInteractiveDialogContentNot : public PacketHeader {
    unsigned int                      uTargetId;
    int                               nNpcId;
    std::vector<InteractiveDialogItem> xItems;
    std::vector<char>                 xData;
};
struct PkgPlayerKillSlaveReq     : public PacketHeader { unsigned int uUserId; };
DECLARE_READWRITE(PkgPlayerKillSlaveReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerKillSlaveReq);
struct PkgPlayerMergyCostItemReq : public PacketHeader { unsigned int uUserId; unsigned int dwDestTag; unsigned int dwSrcTag; };
DECLARE_READWRITE(PkgPlayerMergyCostItemReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerMergyCostItemReq);
struct PkgPlayerMonsInfoReq      : public PacketHeader { unsigned int uUserId; unsigned int uMonsId; unsigned int uTargetId; };
DECLARE_READWRITE(PkgPlayerMonsInfoReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerMonsInfoReq);
struct PkgPlayerNetDelayReq      : public PacketHeader { unsigned int uUserId; unsigned int dwSendSequence; };
DECLARE_READWRITE(PkgPlayerNetDelayReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerNetDelayReq);
struct PkgPlayerOffBuyItemReq    : public PacketHeader { unsigned int uUserId; int nItemIndex; int nQueryID; unsigned int dwItemID; };
DECLARE_READWRITE(PkgPlayerOffBuyItemReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerOffBuyItemReq);
struct PkgPlayerOffCheckSoldReq  : public PacketHeader { unsigned int uUserId; };
DECLARE_READWRITE(PkgPlayerOffCheckSoldReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerOffCheckSoldReq);
struct PkgPlayerOffGetListReq    : public PacketHeader { unsigned int uUserId; int nPage; };
DECLARE_READWRITE(PkgPlayerOffGetListReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerOffGetListReq);
struct PkgPlayerOffSellItemReq   : public PacketHeader { unsigned int uUserId; unsigned int dwTag; unsigned int dwMoney; unsigned int dwGold; };
DECLARE_READWRITE(PkgPlayerOffSellItemReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerOffSellItemReq);
struct PkgPlayerOffTakeBackReq   : public PacketHeader { unsigned int uUserId; int nItemIndex; };
DECLARE_READWRITE(PkgPlayerOffTakeBackReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerOffTakeBackReq);
struct PkgPlayerOpenPotentialReq : public PacketHeader { unsigned int uUserId; int nItemId; int nStoneId; };
DECLARE_READWRITE(PkgPlayerOpenPotentialReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerOpenPotentialReq);
struct PkgPlayerPickUpItemReq    : public PacketHeader { unsigned int uUserId; unsigned int uItemTag; unsigned int dwTag; };
DECLARE_READWRITE(PkgPlayerPickUpItemReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerPickUpItemReq);
struct PkgPlayerPrivateChatReq   : public PacketHeader { unsigned int uUserId; std::string xPeerName; std::string xMsg; };
DECLARE_READWRITE(PkgPlayerPrivateChatReq);
struct PkgPlayerQuitSelChrReq    : public PacketHeader {};
DECLARE_READWRITE(PkgPlayerQuitSelChrReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerQuitSelChrReq);
struct PkgPlayerRankListReq      : public PacketHeader { int nType; };
DECLARE_READWRITE(PkgPlayerRankListReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerRankListReq);
struct PkgPlayerReviveReq        : public PacketHeader { unsigned int uUserId; unsigned char bMode; };
DECLARE_READWRITE(PkgPlayerReviveReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerReviveReq);
struct PkgPlayerSayReq           : public PacketHeader { unsigned int uUserId; unsigned int uType; std::string xName; std::string xWords; };
DECLARE_READWRITE(PkgPlayerSayReq);
struct PkgPlayerServerDelayAck   : public PacketHeader { int nSeq; unsigned int dwTimeStamp; };
DECLARE_READWRITE(PkgPlayerServerDelayAck);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerServerDelayAck);
struct PkgPlayerShopOpReq        : public PacketHeader { unsigned int uUserId; unsigned char bOp; unsigned int dwData; unsigned int uTargetId; unsigned char bNumber; };
DECLARE_READWRITE(PkgPlayerShopOpReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerShopOpReq);
struct PkgPlayerSlaveStopReq     : public PacketHeader { unsigned int uUserId; };
DECLARE_READWRITE(PkgPlayerSlaveStopReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerSlaveStopReq);
struct PkgPlayerSmeltMaterialsReq : public PacketHeader { unsigned int uUserId; int nType; std::vector<int> xItemsTag; };
DECLARE_READWRITE(PkgPlayerSmeltMaterialsReq);
struct PkgPlayerSpeOperateReq    : public PacketHeader { unsigned int uUserId; unsigned int dwOp; unsigned int dwParam; };
DECLARE_READWRITE(PkgPlayerSpeOperateReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerSpeOperateReq);
struct PkgPlayerSplitItemReq     : public PacketHeader { unsigned int uUserId; unsigned int dwTag; char cSum; };
DECLARE_READWRITE(PkgPlayerSplitItemReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerSplitItemReq);
struct PkgPlayerSyncAssistReq    : public PacketHeader { unsigned char bNum; };
DECLARE_READWRITE(PkgPlayerSyncAssistReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerSyncAssistReq);
struct PkgPlayerSyncAttribNtf    : public PacketHeader { ItemAttrib stAttrib; };
DECLARE_READWRITE(PkgPlayerSyncAttribNtf);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerSyncAttribNtf);
struct PkgPlayerUnbindItemReq    : public PacketHeader { unsigned int dwTag; };
DECLARE_READWRITE(PkgPlayerUnbindItemReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerUnbindItemReq);
struct PkgPlayerUndressItemReq   : public PacketHeader { unsigned int uUserId; unsigned char bPos; unsigned int dwTag; };
DECLARE_READWRITE(PkgPlayerUndressItemReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerUndressItemReq);
struct PkgPlayerUseItemReq       : public PacketHeader { unsigned int uUserId; int nItemIndex; unsigned int dwTag; };
DECLARE_READWRITE(PkgPlayerUseItemReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerUseItemReq);
struct PkgPlayerUserDataReq      : public PacketHeader { unsigned int uUserId; };
DECLARE_READWRITE(PkgPlayerUserDataReq);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerUserDataReq);
struct PkgPlayerWorldSayReq      : public PacketHeader { unsigned int uUserId; std::string xMsg; unsigned int uReserved; };
DECLARE_READWRITE(PkgPlayerWorldSayReq);
struct PkgPlayerWorldSayNot      : public PacketHeader { std::string xMsg; };
DECLARE_READWRITE(PkgPlayerWorldSayNot);

// ---------------------------------------------------------------------------
// GM command operation codes
// ---------------------------------------------------------------------------
enum CmdOpCode
{
    CMD_OP_MOVE = 1,
    CMD_OP_GMOVE,
    CMD_OP_FLY,
    CMD_OP_MAKE,
    CMD_OP_MAKESUPERITEM,
    CMD_OP_GIVE,
    CMD_OP_SGIVE,
    CMD_OP_RESETWORLDWEIGHT,
    CMD_OP_RESETSCENEWEIGHT,
    CMD_OP_SETWORLDWEIGHT,
    CMD_OP_SETSCENEWEIGHT,
    CMD_OP_SHOWWORLDWEIGHT,
    CMD_OP_SHOWSCENEWEIGHT,
    CMD_OP_LEVELUP,
    CMD_OP_MONSTER,
    CMD_OP_EMONSTER,
    CMD_OP_LMONSTER,
    CMD_OP_GET,
    CMD_OP_SGET,
    CMD_OP_SETWINGEFF,
    CMD_OP_SETCLOTHEFF,
    CMD_OP_SETWEAPONEFF,
    CMD_OP_SETHAIREFF,
    CMD_OP_SENDSUPERITEMMSG,
    CMD_OP_EXPRMULTI,
    CMD_OP_DROPMULTI,
    CMD_OP_NORESET,
    CMD_OP_ADDOLSHOPITEM,
    CMD_OP_DELOLSHOPITEM,
    CMD_OP_SETQUEST,
    CMD_OP_SCHEDULEACTIVE,
    CMD_OP_GMHIDE,
    CMD_OP_CREATETEAM,
    CMD_OP_JOINTEAM,
    CMD_OP_ADDTEAMMATE,
    CMD_OP_KICKTEAMMATE,
    CMD_OP_QUITTEAM,
    CMD_OP_VIEWEQUIP,
    CMD_OP_CHANGEATTACKMODE,
    CMD_OP_SETMOVESPEED,
    CMD_OP_SETATTACKSPEED,
};

// ---------------------------------------------------------------------------
// Shop operation codes
// ---------------------------------------------------------------------------
#define SHOP_BUY        0
#define SHOP_SELLSHOP   3
#define SHOP_STORAGE    1
#define SHOP_SELL       2
#define SHOP_STORE      1
#define SHOP_FETCH      4
#define SHOP_BIGSTORE_STORE  5
#define SHOP_BIGSTORE_FETCH  6

// ---------------------------------------------------------------------------
// Force action types
// ---------------------------------------------------------------------------
#define FORCE_POSITION  1

// ---------------------------------------------------------------------------
// Expression masks
// ---------------------------------------------------------------------------
#define EXPR_MASK_NOSELL  0x00000001

// ---------------------------------------------------------------------------
// Quick message types
// ---------------------------------------------------------------------------
#define QUICKMSG_MULTI    100

// ---------------------------------------------------------------------------
// Sell item types
// ---------------------------------------------------------------------------
#define SELL_ITEM_MULTI   1

// ---------------------------------------------------------------------------
// Upgrade stone
// ---------------------------------------------------------------------------
#define UPGRADESTONE_MAX_LEVEL  7

// ---------------------------------------------------------------------------
// Store sync types
// ---------------------------------------------------------------------------
#define STORESYNC_ADDSTORE      1
#define STORESYNC_BIG_ADDSTORE  2
#define STORESYNC_REMOVESTORE   3
#define STORESYNC_BIG_REMOVESTORE 4

// ---------------------------------------------------------------------------
// Dialog types (add to existing DlgType enum)
// ---------------------------------------------------------------------------
#define DLG_REVIVE      3

#define INTERVAL_REVIVE (15 * 1000)

#define SyncDataUpgradeExpr 1

// ---------------------------------------------------------------------------
// Status defines (QMSG_*, GSTATUS_*)
// ---------------------------------------------------------------------------
#include "StatusDefine.h"

// ---------------------------------------------------------------------------
// Global stone table declarations
// ---------------------------------------------------------------------------
extern int g_nDCStoneTable[];
extern int g_nSCStoneTable[];
extern int g_nMCStoneTable[];

// ---------------------------------------------------------------------------
// Additional packet types
// ---------------------------------------------------------------------------

// GS -> Client: change equip notification
struct PkgPlayerChangeEquipNot : public PacketHeader
{
    unsigned int uTargetId;
    ItemAttrib   stItem;
};
DECLARE_READWRITE(PkgPlayerChangeEquipNot);

// GS -> Client: player say notification
struct PkgPlayerSayNot : public PacketHeader
{
    unsigned int uTargetId;
    std::string  xMsg;
    unsigned int uColor;
};
DECLARE_READWRITE(PkgPlayerSayNot);

// GS -> Client: other player equip notification
struct PkgPlayerOtherPlayerEquipNtf : public PacketHeader
{
    unsigned int      uTargetId;
    std::vector<char> xData;
};
DECLARE_READWRITE(PkgPlayerOtherPlayerEquipNtf);

// GS -> Client: net delay ack
struct PkgPlayerNetDelayAck : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int dwSendSequence;
};
DECLARE_READWRITE(PkgPlayerNetDelayAck);

// GS -> Client: offline sell list notification
struct PkgPlayerOffSellListNtf : public PacketHeader
{
    unsigned int   uTargetId;
    char           bPage;
    SellItemVector xItems;
};
DECLARE_READWRITE(PkgPlayerOffSellListNtf);

// GS -> Client: private chat notification
struct PkgPlayerPrivateChatNtf : public PacketHeader
{
    unsigned int uTargetId;
    std::string  xSender;
    std::string  xMsg;
};
DECLARE_READWRITE(PkgPlayerPrivateChatNtf);

// GS -> Client: private chat ack
struct PkgPlayerPrivateChatAck : public PacketHeader
{
    unsigned int uTargetId;
    char         bOnline;
    std::string  xPeerName;
};
DECLARE_READWRITE(PkgPlayerPrivateChatAck);

// GS -> Client: rank list notification
struct PkgPlayerRankListNot : public PacketHeader
{
    unsigned int uTargetId;
    std::string  xData;
};
DECLARE_READWRITE(PkgPlayerRankListNot);

// GS -> Client: ol shop list ack
struct PkgPlayerGetOlShopListAck : public PacketHeader
{
    unsigned int          uTargetId;
    std::vector<int> xItemsId;
};
DECLARE_READWRITE(PkgPlayerGetOlShopListAck);

// GS -> Client: buy ol shop item ack
struct PkgPlayerBuyOlShopItemAck : public PacketHeader
{
    unsigned int uTargetId;
    int          nItemId;
    int          nRet;
};
DECLARE_READWRITE(PkgPlayerBuyOlShopItemAck);

// GS -> Client: smelt materials response
struct PkgPlayerSmeltMaterialsRsp : public PacketHeader
{
    unsigned int uTargetId;
    int          nCode;
};
DECLARE_READWRITE(PkgPlayerSmeltMaterialsRsp);

// GS -> Client: open potential response
struct PkgPlayerOpenPotentialRsp : public PacketHeader
{
    unsigned int uTargetId;
    int          nCode;
};
DECLARE_READWRITE(PkgPlayerOpenPotentialRsp);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerOpenPotentialRsp);

// GS -> Client: charge response
struct PkgPlayerChargeRsp : public PacketHeader
{
    unsigned int uTargetId;
    int          nResult;
};
DECLARE_READWRITE(PkgPlayerChargeRsp);

// GS -> Client: difficulty level response
struct PkgPlayerDifficultyLevelRsp : public PacketHeader
{
    unsigned int uTargetId;
    int          nRet;
};
DECLARE_READWRITE(PkgPlayerDifficultyLevelRsp);

// GS -> Client: offline sold item ack
struct PkgPlayerOffSoldItemAck : public PacketHeader
{
    unsigned int uTargetId;
    std::string  xItemName;
    std::string  xBuyerName;
    unsigned int dwMoney;
    unsigned int dwGold;
};
DECLARE_READWRITE(PkgPlayerOffSoldItemAck);

// GS -> Client: sync data notification
struct PkgGameSyncDataNot : public PacketHeader
{
    unsigned int      uTargetId;
    int               nType;
    std::vector<int>  vecVals;
};
DECLARE_READWRITE(PkgGameSyncDataNot);

// GS -> Client: player revive notification
struct PkgPlayerReviveNot : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int uHp;
    unsigned char bMode;
};
DECLARE_READWRITE(PkgPlayerReviveNot);

// GS -> Client: version verify notification
struct PkgPlayerVersionVerifyNtf : public PacketHeader
{
    unsigned int      uTargetId;
    std::string       xVersion;
};
DECLARE_READWRITE(PkgPlayerVersionVerifyNtf);

// GS -> Client: quest data notification
struct PkgPlayerQuestDataNtf : public PacketHeader
{
    unsigned int      uTargetId;
    std::vector<char> xData;
};
DECLARE_READWRITE(PkgPlayerQuestDataNtf);

// GS -> Client: store sync ack
struct PkgPlayerStoreSyncAck : public PacketHeader
{
    unsigned int uTargetId;
    char         bType;
    unsigned int dwTag;
};
DECLARE_READWRITE(PkgPlayerStoreSyncAck);

// GS -> Client: show help ack
struct PkgPlayerShowHelpAck : public PacketHeader
{
    unsigned int uTargetId;
    int          nHelpID;
};
DECLARE_READWRITE(PkgPlayerShowHelpAck);

// GS -> Client: force action ack
struct PkgPlayerForceActionAck : public PacketHeader
{
    unsigned int uTargetId;
    char         bType;
    unsigned int dwData;
};
DECLARE_READWRITE(PkgPlayerForceActionAck);

// GS -> Client: dress item ack
struct PkgPlayerDressItemAck : public PacketHeader
{
    unsigned int uTargetId;
    char         bRet;
    unsigned char bPos;
    unsigned int dwTag;
    unsigned int dwTex;
    unsigned int uUserId;
    unsigned int dwFlag;
};
DECLARE_READWRITE(PkgPlayerDressItemAck);

struct PkgPlayerUndressItemAck : public PacketHeader
{
    unsigned int uTargetId;
    char         bRet;
    unsigned char bPos;
    unsigned int dwTag;
};
DECLARE_READWRITE(PkgPlayerUndressItemAck);

// GS -> Client: player suit ignore notification
struct PkgGamePlayerSuitIgnoreNot : public PacketHeader
{
    unsigned int   uTargetId;
    std::set<int>  setSuitIgnore;
};
inline ByteBuffer& operator<<(ByteBuffer& _buf, const PkgGamePlayerSuitIgnoreNot& _pkg)
{
    _buf.Write(&_pkg, sizeof(PacketHeader));
    _buf << _pkg.uTargetId;
    unsigned int n = (unsigned int)_pkg.setSuitIgnore.size();
    _buf << n;
    for (auto it = _pkg.setSuitIgnore.begin(); it != _pkg.setSuitIgnore.end(); ++it)
    {
        int v = *it;
        _buf << v;
    }
    return _buf;
}
inline ByteBuffer& operator>>(ByteBuffer& _buf, PkgGamePlayerSuitIgnoreNot& _pkg)
{
    _buf >> _pkg.uTargetId;
    unsigned int n = 0; _buf >> n;
    for (unsigned int i = 0; i < n; ++i)
    {
        int v = 0; _buf >> v;
        _pkg.setSuitIgnore.insert(v);
    }
    return _buf;
};

// GS -> Client: attrib update notification
struct PkgPlayerUpdateAttribNtf : public PacketHeader
{
    unsigned int uTargetId;
    BYTE         bType;
    BYTE         uAction;
    unsigned int dwParam;
    unsigned int uParam0;
    unsigned int uParam1;
    unsigned int uParam2;
    unsigned int uParam3;
    unsigned int dwExtra;  // extra param (e.g. exp value for UPDATE_EXP)
};
DECLARE_READWRITE(PkgPlayerUpdateAttribNtf);

// GS -> Client: new ground item notification
struct PkgSystemNewItemNot : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int dwTag;
    unsigned int dwID;
    unsigned int dwPos;
    unsigned int uUserId;
    unsigned int dwItemHideAttrib;
};
DECLARE_READWRITE(PkgSystemNewItemNot);

// GS -> Client: remove ground item notification
struct PkgSystemDelItemNot : public PacketHeader
{
    unsigned int dwTag;
};
DECLARE_READWRITE(PkgSystemDelItemNot);

// GS -> Client: door animation
struct PkgPlayerShowDoorAniAck : public PacketHeader
{
    unsigned int   uTargetId;
    unsigned int   uUserId;
    unsigned short wMgcID;
    unsigned int   dwPos;
    WORD           wPosX;
    WORD           wPosY;
};
DECLARE_READWRITE(PkgPlayerShowDoorAniAck);

// GS -> Client: player UID notification
struct PkgPlayerUIDNtf : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int uUID;
};
DECLARE_READWRITE(PkgPlayerUIDNtf);

// GS -> Client: play animation
struct PkgPlayerPlayAniAck : public PacketHeader
{
    unsigned int         uTargetId;
    unsigned int         uUserId;
    unsigned short       wAniID;
    std::list<unsigned int> xPos;
};
DECLARE_READWRITE(PkgPlayerPlayAniAck);

// GS -> Client: quit character select response
struct PkgPlayerQuitSelChrRsp : public PacketHeader
{
    unsigned int uTargetId;
};
DECLARE_READWRITE(PkgPlayerQuitSelChrRsp);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerQuitSelChrRsp);

// GS -> Client: set effect
struct PkgPlayerSetEffectAck : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int dwMgcID;
    unsigned int dwParam;
    bool         bShow;
    unsigned int dwTime;
    int          bInt;
};
DECLARE_READWRITE(PkgPlayerSetEffectAck);

// GS -> Client: struck notification
struct PkgPlayerStruckAck : public PacketHeader
{
    unsigned int uTargetId;
    int          nDamage;
    BYTE         bType;
};
DECLARE_READWRITE(PkgPlayerStruckAck);

// GS -> Client: clear ground item
struct PkgSystemClearGroundItemNtf : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int dwTag;
};
DECLARE_READWRITE(PkgSystemClearGroundItemNtf);

// GS -> Client: extend attrib notification
enum ExtendAttribType
{
    kExtendAttrib_Hair             = 1,
    kExtendAttrib_Wing             = 2,
    kExtendAttrib_ClothLook        = 3,
    kExtendAttrib_WeaponLook       = 4,
    kExtendAttrib_NameFrame        = 5,
    kExtendAttrib_ChatFrame        = 6,
    kExtendAttrib_ChatColor        = 7,
    kExtendAttrib_SmeltOreLevel    = 8,
    kExtendAttrib_SmeltOreExp      = 9,
    kExtendAttrib_SmeltWoodLevel   = 10,
    kExtendAttrib_SmeltWoodExp     = 11,
    kExtendAttrib_SmeltClothLevel  = 12,
    kExtendAttrib_SmeltClothExp    = 13,
    kExtendAttrib_SmeltGemLevel    = 14,
    kExtendAttrib_SmeltGemExp      = 15,
    kExtendAttrib_MakeEquipLevel   = 16,
    kExtendAttrib_MakeEquipExp     = 17,
};

struct ExtendAttribItem
{
    unsigned int uType;
    int          nValue;
};
typedef std::vector<ExtendAttribItem> ExtendAttribItemVector;
struct PkgPlayerExtendAttribNot : public PacketHeader
{
    unsigned int          uTargetId;
    ExtendAttribItemVector xAttrib;
    std::vector<char>     xData;  // legacy raw form
};
DECLARE_READWRITE(PkgPlayerExtendAttribNot);

// GS -> Client: drop item notification
struct PkgPlayerDropItemNot : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int dwID;
    unsigned int dwTag;
    unsigned short wCoordX;
    unsigned short wCoordY;
};
DECLARE_READWRITE(PkgPlayerDropItemNot);

// GS -> Client: VIP level notification
struct PkgPlayerVipNot : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int dwID;
    int          nVipLevel;
};
DECLARE_READWRITE(PkgPlayerVipNot);

// GS -> Client: clear item notification
struct PkgPlayerClearItemNtf : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int dwTag;
};
DECLARE_READWRITE(PkgPlayerClearItemNtf);

// GS -> Client: player gained item
struct PkgPlayerGainItemNtf : public PacketHeader
{
    unsigned int uTargetId;
    ItemAttrib   stItem;
};
DECLARE_READWRITE(PkgPlayerGainItemNtf);

// GS -> Client: bale item received
struct PkgPlayerGetBaleItemAck : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int dwTagBeg;
    unsigned int dwID;
};
DECLARE_READWRITE(PkgPlayerGetBaleItemAck);

// ---------------------------------------------------------------------------
// Additional packet types reconstructed from HeroObject.cpp call sites
// ---------------------------------------------------------------------------

// GS -> Client: enable skill notification
struct PkgPlayerEnableSkillNot : public PacketHeader
{
    unsigned int uTargetId;
    int          nSkillId;
    BYTE         bLevel;
    bool         bEnabled;
};
DECLARE_READWRITE(PkgPlayerEnableSkillNot);

// GS -> Client: lost item ack
struct PkgPlayerLostItemAck : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int dwTag;
};
DECLARE_READWRITE(PkgPlayerLostItemAck);

// GS -> Client: update item notification (item in bag changed)
struct PkgPlayerUpdateItemNtf : public PacketHeader
{
    unsigned int uTargetId;
    int          nBagIndex;
    ItemAttrib   stItem;
};
DECLARE_READWRITE(PkgPlayerUpdateItemNtf);

// GS -> Client: update cost item notification (consumable count changed)
struct PkgPlayerUpdateCostNtf : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int dwTag;
    int          nCount;
    int          nNumber;   // alias for nCount
    bool         bSelfUse;
    unsigned char bBind;
};
DECLARE_READWRITE(PkgPlayerUpdateCostNtf);

// GS -> Client: change map ack
struct PkgPlayerChangeMapAck : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int dwMapID;
    WORD         wMapID;   // alias
    WORD         wPosX;
    WORD         wPosY;
};
DECLARE_READWRITE(PkgPlayerChangeMapAck);

// GS -> Client: sync quest notification
struct PkgPlayerSyncQuestNtf : public PacketHeader
{
    unsigned int      uTargetId;
    char              bStage;
    char              bCounter;
    char              bStep;
    std::vector<char> xData;
};
DECLARE_READWRITE(PkgPlayerSyncQuestNtf);

// GS -> Client: quick message notification
struct PkgPlayerQuickMsgNtf : public PacketHeader
{
    unsigned int uTargetId;
    int          nMsgID;
    int          nParam;
};
DECLARE_READWRITE(PkgPlayerQuickMsgNtf);

// GS -> Client: weapon grow update notification
struct PkgPlayerUpdateWeaponGrowNtf : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int dwTag;
    unsigned int dwData;
    unsigned int dwGrowData;
    int          nLevel;
};
DECLARE_READWRITE(PkgPlayerUpdateWeaponGrowNtf);

// GS -> Client: clear all items ack
struct PkgPlayerClearAllItemAck : public PacketHeader
{
    unsigned int uTargetId;
};
DECLARE_READWRITE(PkgPlayerClearAllItemAck);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerClearAllItemAck);

// ByteBuffer serialization for ExtendAttribItem
inline ByteBuffer& operator<<(ByteBuffer& _buf, const ExtendAttribItem& _v)
{
    _buf << _v.uType << _v.nValue;
    return _buf;
}
inline ByteBuffer& operator>>(ByteBuffer& _buf, ExtendAttribItem& _v)
{
    _buf >> _v.uType >> _v.nValue;
    return _buf;
}
inline ByteBuffer& operator<<(ByteBuffer& _buf, const ExtendAttribItemVector& _vec)
{
    unsigned int n = (unsigned int)_vec.size();
    _buf << n;
    for (unsigned int i = 0; i < n; ++i) _buf << _vec[i];
    return _buf;
}
inline ByteBuffer& operator>>(ByteBuffer& _buf, ExtendAttribItemVector& _vec)
{
    unsigned int n = 0; _buf >> n;
    _vec.resize(n);
    for (unsigned int i = 0; i < n; ++i) _buf >> _vec[i];
    return _buf;
}

// ByteBuffer serialization for PkgPlayerExtendAttribNot
inline ByteBuffer& operator<<(ByteBuffer& _buf, const PkgPlayerExtendAttribNot& _pkg)
{
    _buf.Write(&_pkg, sizeof(PacketHeader));
    _buf << _pkg.uTargetId;
    unsigned int n = (unsigned int)_pkg.xAttrib.size();
    _buf << n;
    for (unsigned int i = 0; i < n; ++i) _buf << _pkg.xAttrib[i];
    return _buf;
}
inline ByteBuffer& operator>>(ByteBuffer& _buf, PkgPlayerExtendAttribNot& _pkg)
{
    _buf >> _pkg.uTargetId;
    unsigned int n = 0; _buf >> n;
    _pkg.xAttrib.resize(n);
    for (unsigned int i = 0; i < n; ++i) _buf >> _pkg.xAttrib[i];
    return _buf;
}

// ByteBuffer serialization for PkgPlayerInteractiveDialogContentNot
inline ByteBuffer& operator<<(ByteBuffer& _buf, const InteractiveDialogItem& _v)
{
    _buf << _v.nX << _v.nY << _v.uType << _v.uId << _v.xText;
    return _buf;
}
inline ByteBuffer& operator>>(ByteBuffer& _buf, InteractiveDialogItem& _v)
{
    _buf >> _v.nX >> _v.nY >> _v.uType >> _v.uId >> _v.xText;
    return _buf;
}
inline ByteBuffer& operator<<(ByteBuffer& _buf, const PkgPlayerInteractiveDialogContentNot& _pkg)
{
    _buf.Write(&_pkg, sizeof(PacketHeader));
    _buf << _pkg.uTargetId << _pkg.nNpcId;
    unsigned int n = (unsigned int)_pkg.xItems.size();
    _buf << n;
    for (unsigned int i = 0; i < n; ++i) _buf << _pkg.xItems[i];
    return _buf;
}
inline ByteBuffer& operator>>(ByteBuffer& _buf, PkgPlayerInteractiveDialogContentNot& _pkg)
{
    _buf >> _pkg.uTargetId >> _pkg.nNpcId;
    unsigned int n = 0; _buf >> n;
    _pkg.xItems.resize(n);
    for (unsigned int i = 0; i < n; ++i) _buf >> _pkg.xItems[i];
    return _buf;
}

// ByteBuffer serialization for PkgPlayerGStatusNtf (vector fields)
inline ByteBuffer& operator<<(ByteBuffer& _buf, const PkgPlayerGStatusNtf& _pkg)
{
    _buf.Write(&_pkg, sizeof(PacketHeader));
    _buf << _pkg.uTargetId;
    _buf << _pkg.nStatus;
    unsigned int n = (unsigned int)_pkg.xStatus.size();
    _buf << n;
    for (unsigned int i = 0; i < n; ++i) _buf << _pkg.xStatus[i];
    n = (unsigned int)_pkg.xTimes.size();
    _buf << n;
    for (unsigned int i = 0; i < n; ++i) _buf << _pkg.xTimes[i];
    return _buf;
}
inline ByteBuffer& operator>>(ByteBuffer& _buf, PkgPlayerGStatusNtf& _pkg)
{
    _buf >> _pkg.uTargetId >> _pkg.nStatus;
    unsigned int n = 0;
    _buf >> n; _pkg.xStatus.resize(n);
    for (unsigned int i = 0; i < n; ++i) _buf >> _pkg.xStatus[i];
    _buf >> n; _pkg.xTimes.resize(n);
    for (unsigned int i = 0; i < n; ++i) _buf >> _pkg.xTimes[i];
    return _buf;
}

// ---------------------------------------------------------------------------
// Additional packet types reconstructed from HeroObject.cpp / HeroObject_Packet.cpp
// ---------------------------------------------------------------------------

// Dialog type constants
enum DlgType
{
    DLG_CUBE      = 1,
    DLG_WORLDCHAT = 2,
};

// GS -> Client: show dialog ack
struct PkgPlayerShowDlgAck : public PacketHeader
{
    unsigned int uTargetId;
    BYTE         bType;
};
DECLARE_READWRITE(PkgPlayerShowDlgAck);

// GS -> Client: use item ack
struct PkgPlayerUseItemAck : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int dwUsage;
    unsigned int dwTag;
};
DECLARE_READWRITE(PkgPlayerUseItemAck);

// GS -> Client: click NPC ack
struct PkgPlayerClickNPCAck : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int uNPCId;
    unsigned int uUserId;
    unsigned int dwNPCID;
    unsigned int dwParam;
    int          nResult;
};
DECLARE_READWRITE(PkgPlayerClickNPCAck);

// GS -> Client: dialog data ack
struct PkgPlayerDialogDataAck : public PacketHeader
{
    unsigned int      uTargetId;
    int               nType;
    std::vector<char> xData;
};
DECLARE_READWRITE(PkgPlayerDialogDataAck);

// GS -> Client: hide quest dialog ack
struct PkgPlayerHideQuestDlgAck : public PacketHeader
{
    unsigned int uTargetId;
};
DECLARE_READWRITE(PkgPlayerHideQuestDlgAck);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerHideQuestDlgAck);

// GS -> Client: show shop ack
struct PkgPlayerShowShopAck : public PacketHeader
{
    unsigned int         uTargetId;
    int                  nShopType;
    char                 bType;
    unsigned int         uUserId;
    std::vector<int>     xItems;
};
DECLARE_READWRITE(PkgPlayerShowShopAck);

// GS -> Client: store data ack
struct PkgPlayerStoreDataAck : public PacketHeader
{
    unsigned int      uTargetId;
    std::vector<char> xData;
};
DECLARE_READWRITE(PkgPlayerStoreDataAck);

// GS -> Client: update random seed notification
struct PkgPlayerUpdateRandSeedNot : public PacketHeader
{
    unsigned int uTargetId;
    int          nType;
    unsigned int dwSeed;
    unsigned int uSeedType;
    unsigned int uSeed;
};
DECLARE_READWRITE(PkgPlayerUpdateRandSeedNot);

// GS -> Client: change monster look ack
struct PkgPlayerChangeMonsLookAck : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int uMonsId;
    unsigned int uLook;
    unsigned int dwChg;
};
DECLARE_READWRITE(PkgPlayerChangeMonsLookAck);

// GS -> Client: clear bag notification
struct PkgPlayerClearBagNtf : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int dwTag;
};
DECLARE_READWRITE(PkgPlayerClearBagNtf);

// Client -> GS: server delay request
struct PkgPlayerServerDelayReq : public PacketHeader
{
    unsigned int uTargetId;
    int          nSeq;
    unsigned int dwTimeStamp;
    unsigned int uTick;
};
DECLARE_READWRITE(PkgPlayerServerDelayReq);

#endif // _INC_GAMEPACKET_

struct PkgMonsterFireDragonAttack0Not : public PacketHeader
{
    unsigned int uTargetId;
    unsigned int uUserId;
    unsigned int uParam0;
    unsigned int uParam1;
    unsigned int dwPos;
    unsigned int dwExplosionPos;
    int          nDrt;
    unsigned int dwLastTime;
};
DECLARE_READWRITE(PkgMonsterFireDragonAttack0Not);
BYTEBUFFER_STRUCT_OPERATOR(PkgMonsterFireDragonAttack0Not);

struct PkgPlayerPlaySoundNtf : public PacketHeader
{
    unsigned int uTargetId;
    int          nSoundType;
    int          nSoundId;
    int          bType;
    unsigned int dwData;
};
DECLARE_READWRITE(PkgPlayerPlaySoundNtf);
BYTEBUFFER_STRUCT_OPERATOR(PkgPlayerPlaySoundNtf);
