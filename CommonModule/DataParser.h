// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMClient/BackMir/BMPreConnWnd.h (DataParser m_xParserGameSvr/LoginSvr/Global)
//   BMClient/BackMir/BMPreConnWnd.cpp (SetHandlePacket, OnSocketData)
//   BMClient/Net/PacketHandler.h (class SocketDataCenter : public DataParser)
//   BMClient/Net/PacketHandler.cpp (SetHandlePacket, OnSocketData, PushData)
//
// 流式 TCP 数据分包器。
// 包帧格式：[4 bytes big-endian total-length][payload]
// total-length 包含自身 4 字节。
// 每收到一个完整包，调用回调 void __stdcall cb(const void* data, unsigned int len)。
#pragma once
#ifndef _INC_DATAPARSER_
#define _INC_DATAPARSER_

#include "platform_compat.h"

class DataParser
{
public:
    typedef void (__stdcall *HandlePacketFunc)(const void* _pData, unsigned int _nLen);

    DataParser();
    virtual ~DataParser();

    // 设置完整包回调；传 NULL 清除
    void SetHandlePacket(HandlePacketFunc _pFunc);

    // 喂入原始 TCP 流数据，内部自动分包并触发回调
    void OnSocketData(const void* _pData, unsigned int _nLen);

private:
    void TryDispatch();

    HandlePacketFunc m_pCallback;
    unsigned char*   m_pBuf;
    unsigned int     m_uBufSize;
    unsigned int     m_uDataLen;  // bytes currently buffered
};

#endif // _INC_DATAPARSER_
