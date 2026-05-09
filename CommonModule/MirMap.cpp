// [reconstructed] 重建于 2026-05-06
// 实现给出最小可用的 .map 解析骨架。具体的 14 字节/格布局依
// 实际 .map 文件版本（不同私服改动较大）调整。
#include "MirMap.h"
#include "fileopt.h"
#include <cstring>

namespace
{
    constexpr int kHeaderSize     = 52;
    constexpr int kBytesPerCell   = 14;
    // 本服 .map 单元格的可走标志位（推测；调用方可在 CanWalk 中调整）
    constexpr unsigned char kCellFlagCanWalk = 0x01;
}

MirMap::MirMap() : m_nWidth(0), m_nHeight(0) {}
MirMap::~MirMap() { Unload(); }

bool MirMap::Load(const std::string& _path)
{
    Unload();
    std::vector<char> raw;
    if (!fileopt::ReadFileToBuffer(_path, raw)) return false;
    if (raw.size() < (size_t)kHeaderSize) return false;

    // 头：宽度 [2..4]、高度 [4..6]（little-endian short）
    auto rd16 = [&](int _off) -> int {
        unsigned short v = 0;
        std::memcpy(&v, raw.data() + _off, 2);
        return (int)v;
    };
    m_nWidth  = rd16(0);
    m_nHeight = rd16(2);
    if (m_nWidth <= 0 || m_nHeight <= 0) { Unload(); return false; }

    size_t need = (size_t)kHeaderSize + (size_t)m_nWidth * m_nHeight * kBytesPerCell;
    if (raw.size() < need) { Unload(); return false; }

    m_vecCells.resize((size_t)m_nWidth * m_nHeight, 0);
    const char* p = raw.data() + kHeaderSize;
    for (size_t i = 0, n = m_vecCells.size(); i < n; ++i)
    {
        m_vecCells[i] = p[0];   // 取每格首字节作为标志位
        p += kBytesPerCell;
    }
    return true;
}

void MirMap::Unload()
{
    m_nWidth = m_nHeight = 0;
    m_vecCells.clear();
}

bool MirMap::CanWalk(int _x, int _y) const
{
    if (_x < 0 || _y < 0 || _x >= m_nWidth || _y >= m_nHeight) return false;
    unsigned char f = (unsigned char)m_vecCells[(size_t)_y * m_nWidth + _x];
    return (f & kCellFlagCanWalk) != 0;
}

bool MirMap::CanFly(int _x, int _y) const
{
    return CanWalk(_x, _y);  // 默认与 CanWalk 一致
}
