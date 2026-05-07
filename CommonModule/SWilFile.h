// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   仅 BMServer/BackMirServer13.vcxproj 引用 ..\CommonModule\SWilFile.h
//   BMClient/Common/MirMap.h:116 中已有 class SWilFile（依赖 HBITMAP 等渲染 API），
//   实现位于 BMClient/Common/SWilFile.cpp。
//
// BMServer 不需要做实际的 .wil 解码（无渲染上下文），但它的某些
// 翻译单元 #include 了此头——本文件只提供前置声明，以便满足
// 编译依赖。具体类型仅在 #ifdef _WIN32 + 包含 BMClient/Common/MirMap.h
// 的场景下使用。
#pragma once
#ifndef _INC_SWILFILE_COMMONMODULE_
#define _INC_SWILFILE_COMMONMODULE_

class SWilFile;        // 前置声明，避免拉入 BMClient/Common/MirMap.h
class SWilFileEx;

#endif // _INC_SWILFILE_COMMONMODULE_
