// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMServer/GameWorld/ObjectEngine.h (TEST_FLAG_BOOL, MAKELONG, MAX_LEVEL, GRID_MAX)
//   BMServer/GameWorld/GameDbBuffer.cpp (GetGlobalHP, GetGlobalMP, GetGlobalWanLi, GetGlobalExpr, MAX_LEVEL)
//   BMServer/GameWorld/HeroObject.cpp (GRID_MAX)
//   BMClient/GameScene/GameOtherPlayer.cpp (MAX_LEVEL)
//   BMClient/GameScene/GamePlayer.h (MAX_LEVEL)
//   BMServer/GameWorld/LuaItemHelper.cpp (TEST_FLAG_BOOL, LOWORD, HIWORD, MAKELONG)
//
// 全局共享数据：游戏常量、位操作宏、角色基础属性查询函数。
#pragma once
#ifndef _INC_SHAREDATA_
#define _INC_SHAREDATA_

#include "GDefine.h"

// 游戏常量
#define MAX_LEVEL       200
#define GRID_MAX        30      // 消耗品单格最大堆叠数量

// 角色基础属性查询（按等级 + 职业索引 0=战士 1=法师 2=道士）
int GetGlobalHP(int _nLevel, int _nJob);
int GetGlobalMP(int _nLevel, int _nJob);
int GetGlobalWanLi(int _nLevel, int _nJob);
int GetGlobalExpr(int _nLevel);

#endif // _INC_SHAREDATA_
