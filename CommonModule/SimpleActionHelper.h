// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMServer/GameWorld/BroadcastQueue.cpp (GetCoordX/Y on PkgObjectActionWalkNot)
//   BMClient/Common/GameRenderObject.cpp (GetCoordX/Y/Direction on
//     PkgObjectActionTurnNot/WalkNot/RunNot/AttackNot/DeadNot/ExtNot)
//   BMClient/GameScene/GameMonster.cpp、GameOtherPlayer.cpp 同
//
// 这些不同的 PkgObjectAction*Not 结构体共享 wPosX/wPosY/bDir 字段，
// 所以用模板提取，避免为每种类型重复重载。
//
// 注：与 BMClient/GameDialog/GameRenderObject.cpp 中
//     not.uParam1 = _not.dwPos
// 的写法对照，可见 walk/run 的 dwPos 是「下一格」位置 (MAKELONG(nextX,nextY))，
// 而 GetCoordX/Y 返回的是「当前格」位置——即字段 wPosX/wPosY。
#pragma once
#ifndef _INC_SIMPLEACTIONHELPER_
#define _INC_SIMPLEACTIONHELPER_

class SimpleActionHelper
{
public:
    template<typename T>
    static int GetCoordX(const T& _action) { return (int)_action.wPosX; }

    template<typename T>
    static int GetCoordY(const T& _action) { return (int)_action.wPosY; }

    template<typename T>
    static int GetDirection(const T& _action) { return (int)_action.bDir; }

    static unsigned int MakeWalkAction(int _nDrt, int _wPosX, int _wPosY)
    {
        return ((unsigned int)_nDrt & 0xFF) | (((unsigned int)_wPosX & 0xFFFF) << 8) | (((unsigned int)_wPosY & 0xFFFF) << 24);
    }
};

#endif // _INC_SIMPLEACTIONHELPER_
