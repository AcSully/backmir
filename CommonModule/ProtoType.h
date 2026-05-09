// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMClient/BackMir/BMPreConnWnd.cpp
//   BMClient/LoginScene/SelChrDlg.cpp
//   BMClient/LoginScene/NewHumDlg.cpp
//   BMClient/LoginScene/DeleteConfirmDlg.cpp
//   BMClient/BackMir/HandleLoginMsg.cpp
//   BMServer/CMainServer/CMainServer.cpp
//   BMServer/GameWorld/GameScene.cpp
//   BMServer/GameWorld/GameSceneManager.cpp
//   BMServer/GameWorld/HeroObject.cpp
//
// 全局协议类型标志：记录当前连接使用 ByteBuffer 还是 Protobuf 协议。
// GetProtoType / SetProtoType 是进程级自由函数，非线程安全。
#pragma once
#ifndef _INC_PROTOTYPE_
#define _INC_PROTOTYPE_

enum ProtoType
{
    ProtoType_ByteBuffer = 0,   // 旧版手写二进制协议
    ProtoType_Protobuf   = 1,   // protobuf 协议
};

ProtoType GetProtoType();
void      SetProtoType(ProtoType _eType);

#endif // _INC_PROTOTYPE_
