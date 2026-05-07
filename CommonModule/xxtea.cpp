// xxtea.cpp - XXTEA encryption implementation (stub)
// Full implementation available at: https://github.com/nicehash/xxtea
#include "xxtea.h"
#include <string.h>

#define DELTA 0x9e3779b9
#define MX (((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (key[(p&3)^e] ^ z)))

static void xxtea_encrypt_uint32(uint32_t* v, int n, uint32_t const* key)
{
    uint32_t y, z, sum, *p, e;
    int q;
    if (n < 1) return;
    q = 6 + 52 / n;
    sum = 0;
    z = v[n - 1];
    do {
        sum += DELTA;
        e = (sum >> 2) & 3;
        for (p = v; p < v + n - 1; p++) {
            y = p[1];
            z = p[0] += MX;
        }
        y = v[0];
        z = v[n - 1] += MX;
    } while (--q);
}

static void xxtea_decrypt_uint32(uint32_t* v, int n, uint32_t const* key)
{
    uint32_t y, z, sum, *p, e;
    int q;
    if (n < 1) return;
    q = 6 + 52 / n;
    sum = q * DELTA;
    y = v[0];
    do {
        e = (sum >> 2) & 3;
        for (p = v + n - 1; p > v; p--) {
            z = p[-1];
            y = p[0] -= MX;
        }
        z = v[n - 1];
        y = v[0] -= MX;
        sum -= DELTA;
    } while (--q);
}

void* xxtea_encrypt(const void* data, size_t len, const void* key, size_t* out_len)
{
    if (!data || !key || !out_len) return NULL;
    size_t n = (len + 3) / 4;
    if (n < 1) return NULL;
    uint32_t* v = (uint32_t*)malloc(n * 4);
    if (!v) return NULL;
    memcpy(v, data, len);
    memset((char*)v + len, 0, n * 4 - len);
    xxtea_encrypt_uint32(v, (int)n, (const uint32_t*)key);
    *out_len = n * 4;
    return v;
}

void* xxtea_decrypt(const void* data, size_t len, const void* key, size_t* out_len)
{
    if (!data || !key || !out_len) return NULL;
    size_t n = len / 4;
    if (n < 1) return NULL;
    uint32_t* v = (uint32_t*)malloc(n * 4);
    if (!v) return NULL;
    memcpy(v, data, len);
    xxtea_decrypt_uint32(v, (int)n, (const uint32_t*)key);
    *out_len = n * 4;
    return v;
}
