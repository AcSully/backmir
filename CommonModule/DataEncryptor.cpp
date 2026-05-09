// [reconstructed] 重建于 2026-05-06
#include "DataEncryptor.h"

unsigned short DataEncryptor::GetCheckSum(unsigned int _dwOpCode,
                                          const char*  _pData,
                                          unsigned int _dwLen)
{
    unsigned int sum = _dwOpCode;
    if (_pData)
    {
        for (unsigned int i = 0; i < _dwLen; ++i)
            sum += (unsigned char)_pData[i];
    }
    return (unsigned short)(sum & 0xFFFF);
}

unsigned int DataEncryptor::EncryptGMCode(unsigned int _dwCode)
{
    return _dwCode ^ 0xDEADBEEF;
}

unsigned int DataEncryptor::DecryptGMCode(unsigned int _dwCode)
{
    return _dwCode ^ 0xDEADBEEF;
}
