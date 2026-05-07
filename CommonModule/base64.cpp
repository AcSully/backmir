// [reconstructed] 重建于 2026-05-06
#include "base64.h"
#include <cstring>

static const char kBase64Chars[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

bool Base64::Encode(const std::string& _src, std::string* _pDst)
{
    if (!_pDst) return false;
    _pDst->clear();
    const unsigned char* p = (const unsigned char*)_src.data();
    size_t n = _src.size();
    for (size_t i = 0; i < n; i += 3)
    {
        unsigned int b = (unsigned int)p[i] << 16;
        if (i + 1 < n) b |= (unsigned int)p[i+1] << 8;
        if (i + 2 < n) b |= (unsigned int)p[i+2];
        _pDst->push_back(kBase64Chars[(b >> 18) & 0x3F]);
        _pDst->push_back(kBase64Chars[(b >> 12) & 0x3F]);
        _pDst->push_back((i + 1 < n) ? kBase64Chars[(b >> 6) & 0x3F] : '=');
        _pDst->push_back((i + 2 < n) ? kBase64Chars[b & 0x3F] : '=');
    }
    return true;
}

bool Base64::Decode(const std::string& _src, std::string* _pDst)
{
    if (!_pDst) return false;
    _pDst->clear();
    static unsigned char tbl[256];
    static bool init = false;
    if (!init) {
        memset(tbl, 0xFF, sizeof(tbl));
        for (int i = 0; i < 64; ++i)
            tbl[(unsigned char)kBase64Chars[i]] = (unsigned char)i;
        init = true;
    }
    size_t n = _src.size();
    for (size_t i = 0; i + 3 < n; i += 4)
    {
        unsigned char a = tbl[(unsigned char)_src[i]];
        unsigned char b = tbl[(unsigned char)_src[i+1]];
        unsigned char c = tbl[(unsigned char)_src[i+2]];
        unsigned char d = tbl[(unsigned char)_src[i+3]];
        if (a == 0xFF || b == 0xFF) break;
        _pDst->push_back((char)((a << 2) | (b >> 4)));
        if (_src[i+2] != '=') _pDst->push_back((char)((b << 4) | (c >> 2)));
        if (_src[i+3] != '=') _pDst->push_back((char)((c << 6) | d));
    }
    return true;
}
