// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   仅 BMClient/BackMir13.vcxproj 与 BMServer/BackMirServer13.vcxproj 引用，
//   源码未直接 #include。提供 enum-class <-> 整数互转的常用模板，
//   主要服务于 CommonModule 内部其他文件可能的需求。
#pragma once
#ifndef _INC_ENUMUTILS_
#define _INC_ENUMUTILS_

#include <type_traits>

namespace EnumUtils
{
    // enum value -> underlying integer
    template<typename E>
    constexpr typename std::underlying_type<E>::type ToInt(E _e)
    {
        return static_cast<typename std::underlying_type<E>::type>(_e);
    }

    // integer -> enum (no validation)
    template<typename E>
    constexpr E FromInt(typename std::underlying_type<E>::type _v)
    {
        return static_cast<E>(_v);
    }

    // 测试枚举位标志
    template<typename E>
    constexpr bool HasFlag(E _val, E _flag)
    {
        using U = typename std::underlying_type<E>::type;
        return (static_cast<U>(_val) & static_cast<U>(_flag)) != 0;
    }
}

#endif // _INC_ENUMUTILS_
