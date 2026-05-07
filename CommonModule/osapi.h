// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMServer/common/shared.h
//   BMServer/GameWorld/FreeListManager.h
//   BMServer/GameWorld/DBThread.h
//
// 为 CommonModule 提供 Windows 平台类型别名。
#pragma once
#ifndef _INC_OSAPI_
#define _INC_OSAPI_

#ifdef _WIN32
#  ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#  endif
#  include <windows.h>
#else
#  include "platform_compat.h"
#endif

#endif // _INC_OSAPI_
