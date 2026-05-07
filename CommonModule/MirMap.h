// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   仅 BMServer/BackMirServer13.vcxproj 引用 ..\CommonModule\MirMap.{cpp,h}
//   BMClient 自有 BMClient/Common/MirMap.{cpp,h}（包含渲染相关 API），
//   两者不同：BMServer 端只需读取 .map 二进制做寻路/碰撞检测，
//   不依赖 BMClient 端的 SWilFile / DirectX。
//
// 经典 Mir2 .map 格式：
//   header[52 字节]：宽度/高度等
//   每格 14 字节：bg / mid / fg / door / light...
//   服务器仅关心：bCanWalk(x, y) / bCanFly(x, y)
#pragma once
#ifndef _INC_MIRMAP_
#define _INC_MIRMAP_

#include <string>
#include <vector>

class MirMap
{
public:
    MirMap();
    ~MirMap();

    bool Load(const std::string& _path);
    void Unload();

    int  GetWidth()  const { return m_nWidth; }
    int  GetHeight() const { return m_nHeight; }

    bool CanWalk(int _x, int _y) const;
    bool CanFly(int _x, int _y) const;

private:
    int                m_nWidth;
    int                m_nHeight;
    std::vector<char>  m_vecCells;  // m_nWidth * m_nHeight，每元素 1 字节标志
};

#endif // _INC_MIRMAP_
