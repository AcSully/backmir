// [reconstructed] 重建于 2026-05-06
#include "ShareData.h"

// 基础属性表（占位实现，实际值由 Lua 配置覆盖）
int GetGlobalHP(int _nLevel, int _nJob)
{
    (void)_nJob;
    return _nLevel * 10;
}

int GetGlobalMP(int _nLevel, int _nJob)
{
    (void)_nJob;
    return _nLevel * 5;
}

int GetGlobalWanLi(int _nLevel, int _nJob)
{
    (void)_nJob;
    return _nLevel * 3;
}

int GetGlobalExpr(int _nLevel)
{
    return _nLevel * _nLevel * 100;
}
