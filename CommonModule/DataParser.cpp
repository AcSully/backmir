// [reconstructed] 重建于 2026-05-06
#include "DataParser.h"
#include <cstdlib>
#include <cstring>
#ifdef _WIN32
#  include <winsock2.h>
#else
#  include <arpa/inet.h>   // ntohl
#endif

static const unsigned int DATAPARSER_INIT_BUF = 65536;
static const unsigned int DATAPARSER_MAX_PKT  = 8 * 1024 * 1024;

DataParser::DataParser()
    : m_pCallback(NULL)
    , m_pBuf((unsigned char*)malloc(DATAPARSER_INIT_BUF))
    , m_uBufSize(DATAPARSER_INIT_BUF)
    , m_uDataLen(0)
{
}

DataParser::~DataParser()
{
    free(m_pBuf);
}

void DataParser::SetHandlePacket(HandlePacketFunc _pFunc)
{
    m_pCallback = _pFunc;
}

void DataParser::OnSocketData(const void* _pData, unsigned int _nLen)
{
    if (!_pData || _nLen == 0)
        return;

    // Grow buffer if needed
    if (m_uDataLen + _nLen > m_uBufSize)
    {
        unsigned int uNew = m_uBufSize * 2;
        if (uNew < m_uDataLen + _nLen)
            uNew = m_uDataLen + _nLen + 4096;
        unsigned char* pNew = (unsigned char*)realloc(m_pBuf, uNew);
        if (!pNew)
            return;
        m_pBuf     = pNew;
        m_uBufSize = uNew;
    }

    memcpy(m_pBuf + m_uDataLen, _pData, _nLen);
    m_uDataLen += _nLen;

    TryDispatch();
}

void DataParser::TryDispatch()
{
    while (m_uDataLen >= 4)
    {
        // First 4 bytes: big-endian total packet length (includes the 4-byte length field)
        unsigned int uPktLen = ntohl(*(unsigned int*)m_pBuf);

        if (uPktLen < 4 || uPktLen > DATAPARSER_MAX_PKT)
        {
            // Corrupt stream — discard all buffered data
            m_uDataLen = 0;
            return;
        }

        if (m_uDataLen < uPktLen)
            break;  // wait for more data

        if (m_pCallback)
            m_pCallback(m_pBuf, uPktLen);

        // Shift remaining data to front
        unsigned int uRemain = m_uDataLen - uPktLen;
        if (uRemain > 0)
            memmove(m_pBuf, m_pBuf + uPktLen, uRemain);
        m_uDataLen = uRemain;
    }
}
