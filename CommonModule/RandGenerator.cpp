// [reconstructed] 重建于 2026-05-06
#include "RandGenerator.h"

RandGenerator::RandGenerator() : m_nSeed(1), m_nPrevSeed(1) {}

void RandGenerator::SetSeed(long _nSeed)
{
    m_nSeed = _nSeed;
    m_nPrevSeed = _nSeed;
}

long RandGenerator::GetSeed() const { return m_nSeed; }

// LCG: same constants as glibc rand()
static long lcg_next(long seed)
{
    return (seed * 1103515245L + 12345L) & 0x7fffffffL;
}

int RandGenerator::Rand(int _nMin, int _nMax)
{
    m_nPrevSeed = m_nSeed;
    m_nSeed = lcg_next(m_nSeed);
    if (_nMax <= _nMin) return _nMin;
    return _nMin + (int)(m_nSeed % (_nMax - _nMin + 1));
}

int RandGenerator::GetPrevRand(int _nMin, int _nMax)
{
    long prev = lcg_next(m_nPrevSeed);
    if (_nMax <= _nMin) return _nMin;
    return _nMin + (int)(prev % (_nMax - _nMin + 1));
}
