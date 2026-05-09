// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   仅 BMServer/BackMirServer13.vcxproj 引用，源码未直接 #include。
//   未发现 utils:: 命名空间使用，本文件作为占位 + 常见小工具集合，
//   供 CommonModule 内部其他文件（loginsvr、QuestContext 等）按需使用。
#pragma once
#ifndef _INC_UTILS_
#define _INC_UTILS_

#include <string>
#include <vector>
#include <cstdint>

namespace utils
{
    // 字符串切分；空字符串视为 0 个元素。
    std::vector<std::string> Split(const std::string& _str, char _sep);

    // 去除前后空白（空格/制表/CR/LF）
    std::string Trim(const std::string& _str);

    // 大小写转换（仅 ASCII）
    std::string ToLower(const std::string& _str);
    std::string ToUpper(const std::string& _str);

    // 安全 itoa：永远返回 std::string，不写入栈缓冲
    std::string IntToString(int _v);
    std::string Int64ToString(std::int64_t _v);

    // 字符串前缀/后缀判断
    bool StartsWith(const std::string& _s, const std::string& _prefix);
    bool EndsWith(const std::string& _s, const std::string& _suffix);
}

#endif // _INC_UTILS_
