// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   仅 BMServer/BackMirServer13.vcxproj 引用，源码未直接 #include。
//   提供文件读写常用工具，供 CommonModule 内部的存档/配置加载使用。
//
// API：ReadFileToBuffer / WriteBufferToFile / FileExists / GetFileSize。
// 使用 C++17 std::filesystem。Windows 下 MBCS（GBK）路径直接传 std::string；
// 内部按字节透传。
#pragma once
#ifndef _INC_FILEOPT_
#define _INC_FILEOPT_

#include <string>
#include <vector>
#include <cstdint>

namespace fileopt
{
    // 读取整个文件到 _out。成功返回 true。
    bool ReadFileToBuffer(const std::string& _path, std::vector<char>& _out);

    // 二进制写入。任意已存在文件将被覆盖。成功返回 true。
    bool WriteBufferToFile(const std::string& _path, const void* _pData, std::size_t _nLen);

    bool FileExists(const std::string& _path);

    // 失败返回 (uint64_t)-1
    std::uint64_t GetFileSize(const std::string& _path);
}

#endif // _INC_FILEOPT_
