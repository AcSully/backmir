// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   仅 BMServer/BackMirServer13.vcxproj 与 BMClient/BackMir13.vcxproj 引用，
//   未在 .cpp 中找到具体调用——推测由 CommonModule 内的 GamePacket / SaveFile
//   等使用，或仅是预留。
//
// 提供 ItemAttrib / SkillAttrib 等游戏侧结构体的 ByteBuffer 序列化重载。
// 当前文件提供前置 hooks，待 Phase 1 验收时由编译错误反向补全。
#pragma once
#ifndef _INC_GAMESTRUCTSERIALIZE_
#define _INC_GAMESTRUCTSERIALIZE_

#include "ByteBuffer.h"

// 调用点未发现具体使用；保留头文件仅为编译依赖。
// 若发现 GamePacket.cpp 中需要序列化某个结构体而本头未提供重载，
// 在此追加：
//
//   ByteBuffer& operator<<(ByteBuffer& buf, const ItemAttrib& v);
//   ByteBuffer& operator>>(ByteBuffer& buf, ItemAttrib& v);

#endif // _INC_GAMESTRUCTSERIALIZE_
