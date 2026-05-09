// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMServer/GameWorld/HeroObject.cpp (m_xNormalAttackRand.Rand/SetSeed/GetSeed/GetPrevRand)
//   BMServer/GameWorld/ObjectEngine.h (RandGenerator m_xNormalAttackRand)
//
// 可重现的线性同余随机数生成器，支持回放（GetPrevRand）。
// 客户端和服务端共享同一种子，用于攻击随机数同步。
#pragma once
#ifndef _INC_RANDGENERATOR_
#define _INC_RANDGENERATOR_

class RandGenerator
{
public:
    RandGenerator();

    void SetSeed(long _nSeed);
    long GetSeed() const;

    // 生成 [_nMin, _nMax] 范围内的随机整数，并推进种子
    int Rand(int _nMin, int _nMax);

    // 返回上一次 Rand 的结果（不推进种子），用于客户端回放验证
    int GetPrevRand(int _nMin, int _nMax);

private:
    long m_nSeed;
    long m_nPrevSeed;
};

#endif // _INC_RANDGENERATOR_
