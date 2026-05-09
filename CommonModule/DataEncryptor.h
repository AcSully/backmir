// DataEncryptor.h - Packet checksum and GM code encryption
#pragma once
#ifndef _INC_DATAENCRYPTOR_
#define _INC_DATAENCRYPTOR_

class DataEncryptor
{
public:
    // Calculate 16-bit checksum for opcode + payload
    static unsigned short GetCheckSum(unsigned int _dwOpCode,
                                      const char*   _pData,
                                      unsigned int  _dwLen);

    // GM code encryption (simple obfuscation)
    static unsigned int EncryptGMCode(unsigned int _dwCode);

    // GM code decryption
    static unsigned int DecryptGMCode(unsigned int _dwCode);
};

#endif // _INC_DATAENCRYPTOR_
