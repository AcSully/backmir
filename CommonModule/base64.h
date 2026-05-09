// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMClient/Net/PacketHandler.cpp (Base64::Encode)
//   BMServer/GameWorld/HeroObject.cpp (Base64::Encode)
//
// Base64 编解码，用于角色名等字符串的文件名安全编码。
#pragma once
#ifndef _INC_BASE64_
#define _INC_BASE64_

#include <string>

class Base64
{
public:
    // 将 _src 编码为 Base64，结果写入 *_pDst，返回 true
    static bool Encode(const std::string& _src, std::string* _pDst);

    // 将 Base64 字符串 _src 解码，结果写入 *_pDst，返回 true
    static bool Decode(const std::string& _src, std::string* _pDst);
};

#endif // _INC_BASE64_
