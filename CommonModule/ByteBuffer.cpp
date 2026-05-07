// [reconstructed] 重建于 2026-05-06
#include "ByteBuffer.h"
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <algorithm>

ByteBuffer::ByteBuffer(unsigned int _uCapacity)
    : m_pBuf(NULL), m_uCapacity(0), m_uWritePos(0), m_uReadPos(0), m_nHeadOffset(0)
{
    if (_uCapacity > 0)
    {
        m_pBuf = (unsigned char*)malloc(_uCapacity);
        if (!m_pBuf)
            throw std::bad_alloc();
        m_uCapacity = _uCapacity;
    }
}

ByteBuffer::ByteBuffer(const ByteBuffer& _rhs)
    : m_pBuf(NULL), m_uCapacity(0), m_uWritePos(0), m_uReadPos(0), m_nHeadOffset(0)
{
    if (_rhs.m_uCapacity > 0)
    {
        m_pBuf = (unsigned char*)malloc(_rhs.m_uCapacity);
        if (!m_pBuf)
            throw std::bad_alloc();
        m_uCapacity = _rhs.m_uCapacity;
        m_uWritePos = _rhs.m_uWritePos;
        m_uReadPos  = _rhs.m_uReadPos;
        memcpy(m_pBuf, _rhs.m_pBuf, m_uWritePos);
    }
}

ByteBuffer& ByteBuffer::operator=(const ByteBuffer& _rhs)
{
    if (this != &_rhs)
    {
        if (_rhs.m_uCapacity > m_uCapacity)
            Resize(_rhs.m_uCapacity);
        m_uWritePos = _rhs.m_uWritePos;
        m_uReadPos  = _rhs.m_uReadPos;
        if (m_uWritePos > 0)
            memcpy(m_pBuf, _rhs.m_pBuf, m_uWritePos);
    }
    return *this;
}

ByteBuffer::~ByteBuffer()
{
    free(m_pBuf);
}

void ByteBuffer::Reset()
{
    m_uWritePos = 0;
    m_uReadPos  = 0;
}

unsigned int ByteBuffer::Write(const void* _pData, unsigned int _nLen)
{
    if (!_pData || _nLen == 0)
        return 0;
    if (m_uWritePos + _nLen > m_uCapacity)
    {
        unsigned int uNew = m_uCapacity * 2;
        if (uNew < m_uWritePos + _nLen)
            uNew = m_uWritePos + _nLen + 4096;
        Resize(uNew);
    }
    memcpy(m_pBuf + m_uWritePos, _pData, _nLen);
    m_uWritePos += _nLen;
    return _nLen;
}

unsigned int ByteBuffer::Read(void* _pData, unsigned int _nLen)
{
    if (!_pData || _nLen == 0)
        return 0;
    if (m_uReadPos + _nLen > m_uWritePos)
        return 0;
    memcpy(_pData, m_pBuf + m_uReadPos, _nLen);
    m_uReadPos += _nLen;
    return _nLen;
}

const unsigned char* ByteBuffer::GetBuffer() const { return m_pBuf; }
unsigned char*       ByteBuffer::GetBuffer()       { return m_pBuf; }
const unsigned char* ByteBuffer::GetHead() const   { return m_pBuf + m_uReadPos; }
unsigned int         ByteBuffer::GetLength() const { return m_uWritePos; }
unsigned int         ByteBuffer::GetRemain() const { return m_uWritePos - m_uReadPos; }

void ByteBuffer::Resize(unsigned int _uNewCapacity)
{
    if (_uNewCapacity <= m_uCapacity)
        return;
    unsigned char* pNew = (unsigned char*)realloc(m_pBuf, _uNewCapacity);
    if (!pNew)
        throw std::bad_alloc();
    m_pBuf      = pNew;
    m_uCapacity = _uNewCapacity;
}

// ---------------------------------------------------------------------------
// operator<< implementations
// ---------------------------------------------------------------------------
#define BB_WRITE_POD(T) \
    ByteBuffer& ByteBuffer::operator<<(T v) { Write(&v, sizeof(T)); return *this; }

BB_WRITE_POD(bool)
BB_WRITE_POD(char)
BB_WRITE_POD(unsigned char)
BB_WRITE_POD(short)
BB_WRITE_POD(unsigned short)
BB_WRITE_POD(int)
BB_WRITE_POD(unsigned int)
BB_WRITE_POD(long)
BB_WRITE_POD(unsigned long)
BB_WRITE_POD(long long)
BB_WRITE_POD(unsigned long long)
BB_WRITE_POD(float)
BB_WRITE_POD(double)

ByteBuffer& ByteBuffer::operator<<(const std::string& v)
{
    unsigned short uLen = (unsigned short)v.size();
    Write(&uLen, sizeof(uLen));
    if (uLen > 0)
        Write(v.c_str(), uLen);
    return *this;
}

ByteBuffer& ByteBuffer::operator<<(const std::vector<char>& v)
{
    unsigned int uLen = (unsigned int)v.size();
    Write(&uLen, sizeof(uLen));
    if (uLen > 0)
        Write(&v[0], uLen);
    return *this;
}

ByteBuffer& ByteBuffer::operator<<(const std::vector<unsigned char>& v)
{
    unsigned int uLen = (unsigned int)v.size();
    Write(&uLen, sizeof(uLen));
    if (uLen > 0)
        Write(&v[0], uLen);
    return *this;
}

// ---------------------------------------------------------------------------
// operator>> implementations
// ---------------------------------------------------------------------------
#define BB_READ_POD(T) \
    ByteBuffer& ByteBuffer::operator>>(T& v) { Read(&v, sizeof(T)); return *this; }

BB_READ_POD(bool)
BB_READ_POD(char)
BB_READ_POD(unsigned char)
BB_READ_POD(short)
BB_READ_POD(unsigned short)
BB_READ_POD(int)
BB_READ_POD(unsigned int)
BB_READ_POD(long)
BB_READ_POD(unsigned long)
BB_READ_POD(long long)
BB_READ_POD(unsigned long long)
BB_READ_POD(float)
BB_READ_POD(double)

ByteBuffer& ByteBuffer::operator>>(std::string& v)
{
    unsigned short uLen = 0;
    if (Read(&uLen, sizeof(uLen)) == 0)
        return *this;
    v.resize(uLen);
    if (uLen > 0)
        Read(&v[0], uLen);
    return *this;
}

ByteBuffer& ByteBuffer::operator>>(std::vector<char>& v)
{
    unsigned int uLen = 0;
    if (Read(&uLen, sizeof(uLen)) == 0)
        return *this;
    v.resize(uLen);
    if (uLen > 0)
        Read(&v[0], uLen);
    return *this;
}

ByteBuffer& ByteBuffer::operator>>(std::vector<unsigned char>& v)
{
    unsigned int uLen = 0;
    if (Read(&uLen, sizeof(uLen)) == 0)
        return *this;
    v.resize(uLen);
    if (uLen > 0)
        Read(&v[0], uLen);
    return *this;
}

std::string ByteBuffer::ToHexString() const
{
    static const char hex[] = "0123456789ABCDEF";
    std::string result;
    result.reserve(m_uWritePos * 3);
    for (unsigned int i = 0; i < m_uWritePos; ++i)
    {
        unsigned char b = m_pBuf[i];
        result += hex[(b >> 4) & 0x0F];
        result += hex[b & 0x0F];
        if (i + 1 < m_uWritePos) result += ' ';
    }
    return result;
}
