// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMServer/GameWorld/LuaItemHelper.cpp
//
// 位操作工具宏。调用点仅 include 此头文件，未发现具体宏调用，
// 推测实际位操作通过 ObjectValid 的内联函数完成。
// 保留此头文件以满足编译依赖。
#pragma once
#ifndef _INC_BITOP_
#define _INC_BITOP_

#define BIT_SET(val, bit)    ((val) |=  (1u << (bit)))
#define BIT_CLEAR(val, bit)  ((val) &= ~(1u << (bit)))
#define BIT_TEST(val, bit)   (((val) >> (bit)) & 1u)
#define BIT_GET(val, bit)    BIT_TEST(val, bit)

#endif // _INC_BITOP_
