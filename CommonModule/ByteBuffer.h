// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMClient/BackMir/BackMir.cpp (g_xBuffer, GetBuffer, GetLength, Reset, Write)
//   BMClient/Net/PacketHandler.cpp (operator>>, Write)
//   BMServer/CMainServer/CMainServer.cpp (GetBuffer, GetLength, GetHead, Reset, Write, operator<<, operator>>)
//   BMServer/GameWorld/HeroObject.cpp (operator<<, operator>>)
//
// 字节序约定：小端、紧凑写入（无对齐 padding）。
// std::string 采用 [uint16 length][bytes...] 形式。
// std::vector<char/byte> 采用 [uint32 length][bytes...] 形式。
// 包头格式：[uint32 big-endian total-length][uint32 opcode][payload]
// ByteBuffer 内部存储时 offset=0 是 length 字段本身。
#pragma once
#ifndef _INC_BYTEBUFFER_
#define _INC_BYTEBUFFER_

#include <string>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <cstdint>

class ByteBuffer
{
public:
    explicit ByteBuffer(unsigned int _uCapacity = 4096);
    ByteBuffer(const ByteBuffer& _rhs);
    ByteBuffer& operator=(const ByteBuffer& _rhs);
    ~ByteBuffer();

    // Reset read/write position to 0, does not free memory
    void SetHeadOffset(unsigned int _nOffset) { m_nHeadOffset = _nOffset; }
	void Reset();

    // Write _nLen bytes from _pData; returns bytes written (0 on overflow)
    unsigned int Write(const void* _pData, unsigned int _nLen);

    // Read _nLen bytes into _pData; returns bytes read (0 on underflow)
    unsigned int Read(void* _pData, unsigned int _nLen);

    // Pointer to internal buffer start
    const unsigned char* GetBuffer() const;
    unsigned char*       GetBuffer();

    // Pointer to current read position (alias used in server code)
    const unsigned char* GetHead() const;

    // Number of bytes written (total content length)
    unsigned int GetLength() const;

    // Remaining bytes available to read from current read position
    unsigned int GetRemain() const;

    // Hex dump of buffer contents (for debugging)
    std::string ToHexString() const;

    // Alias used in some server code
    unsigned int GetAvailableLength() const { return GetRemain(); }

    // Resize capacity (preserves content up to min(old, new))
    void Resize(unsigned int _uNewCapacity);

    // ---------------------------------------------------------------------------
    // operator<< — write primitives and structs
    // ---------------------------------------------------------------------------
    ByteBuffer& operator<<(bool v);
    ByteBuffer& operator<<(char v);
    ByteBuffer& operator<<(unsigned char v);
    ByteBuffer& operator<<(short v);
    ByteBuffer& operator<<(unsigned short v);
    ByteBuffer& operator<<(int v);
    ByteBuffer& operator<<(unsigned int v);
    ByteBuffer& operator<<(long v);
    ByteBuffer& operator<<(unsigned long v);
    ByteBuffer& operator<<(long long v);
    ByteBuffer& operator<<(unsigned long long v);
    ByteBuffer& operator<<(float v);
    ByteBuffer& operator<<(double v);

    // std::string: [uint16 len][bytes]
    ByteBuffer& operator<<(const std::string& v);

    // std::vector<char>: [uint32 len][bytes]
    ByteBuffer& operator<<(const std::vector<char>& v);
    ByteBuffer& operator<<(const std::vector<unsigned char>& v);

    // ---------------------------------------------------------------------------
    // operator>> — read primitives and structs
    // ---------------------------------------------------------------------------
    ByteBuffer& operator>>(bool& v);
    ByteBuffer& operator>>(char& v);
    ByteBuffer& operator>>(unsigned char& v);
    ByteBuffer& operator>>(short& v);
    ByteBuffer& operator>>(unsigned short& v);
    ByteBuffer& operator>>(int& v);
    ByteBuffer& operator>>(unsigned int& v);
    ByteBuffer& operator>>(long& v);
    ByteBuffer& operator>>(unsigned long& v);
    ByteBuffer& operator>>(long long& v);
    ByteBuffer& operator>>(unsigned long long& v);
    ByteBuffer& operator>>(float& v);
    ByteBuffer& operator>>(double& v);

    // std::string: [uint16 len][bytes]
    ByteBuffer& operator>>(std::string& v);

    // std::vector<char>: [uint32 len][bytes]
    ByteBuffer& operator>>(std::vector<char>& v);
    ByteBuffer& operator>>(std::vector<unsigned char>& v);

    // Fixed-size char array (reads exactly N bytes including null terminator)
    template<int N>
    ByteBuffer& operator>>(char (&arr)[N])
    {
        Read(arr, N);
        return *this;
    }
    template<int N>
    ByteBuffer& operator<<(const char (&arr)[N])
    {
        Write(arr, N);
        return *this;
    }

private:
    unsigned char* m_pBuf;
    unsigned int   m_uCapacity;
    unsigned int   m_uWritePos;  // total bytes written
    unsigned int   m_uReadPos;   // current read cursor
    unsigned int   m_nHeadOffset; // head offset for packet framing
};

// Declare trivial POD struct serialization (memcpy-based read/write)
#define BYTEBUFFER_STRUCT_OPERATOR(T) \
    inline ByteBuffer& operator<<(ByteBuffer& _buf, const T& _v) { _buf.Write(&_v, sizeof(T)); return _buf; } \
    inline ByteBuffer& operator>>(ByteBuffer& _buf, T& _v)       { _buf.Read(&_v, sizeof(T));  return _buf; }


#endif // _INC_BYTEBUFFER_
