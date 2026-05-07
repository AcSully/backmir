// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMClient/Net/PacketHandler.cpp (BACKMIR_VERSION)
//   BMClient/BackMir/BackMir.cpp (BACKMIR_CURVERSION, BACKMIR_VERSION_CHNAME)
//   BMServer/CMainServer/CMainServer.cpp (BACKMIR_VERSION208..210)
#pragma once
#ifndef _INC_VERSION_
#define _INC_VERSION_

// 当前协议版本号（整数，用于网络握手校验）
#define BACKMIR_VERSION     210

// 历史版本号（用于存档兼容性判断）
#define BACKMIR_VERSION200  200
#define BACKMIR_VERSION201  201
#define BACKMIR_VERSION202  202
#define BACKMIR_VERSION203  203
#define BACKMIR_VERSION204  204
#define BACKMIR_VERSION205  205
#define BACKMIR_VERSION206  206
#define BACKMIR_VERSION207  207
#define BACKMIR_VERSION208  208
#define BACKMIR_VERSION209  209
#define BACKMIR_VERSION210  210

// 当前版本字符串（显示用）
#define BACKMIR_CURVERSION      "2.10"
#define BACKMIR_VERSION_CHNAME  "BackMIR"

#endif // _INC_VERSION_
