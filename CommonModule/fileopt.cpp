// [reconstructed] 重建于 2026-05-06
#include "fileopt.h"
#include <cstdio>
#include <sys/stat.h>

namespace fileopt
{

bool ReadFileToBuffer(const std::string& _path, std::vector<char>& _out)
{
    std::FILE* fp = std::fopen(_path.c_str(), "rb");
    if (!fp) return false;
    std::fseek(fp, 0, SEEK_END);
    long lSize = std::ftell(fp);
    if (lSize < 0) { std::fclose(fp); return false; }
    std::fseek(fp, 0, SEEK_SET);
    _out.resize((std::size_t)lSize);
    std::size_t nRead = (lSize > 0)
        ? std::fread(&_out[0], 1, (std::size_t)lSize, fp)
        : 0;
    std::fclose(fp);
    return (nRead == (std::size_t)lSize);
}

bool WriteBufferToFile(const std::string& _path, const void* _pData, std::size_t _nLen)
{
    std::FILE* fp = std::fopen(_path.c_str(), "wb");
    if (!fp) return false;
    std::size_t nW = 0;
    if (_pData && _nLen > 0)
        nW = std::fwrite(_pData, 1, _nLen, fp);
    std::fclose(fp);
    return (nW == _nLen);
}

bool FileExists(const std::string& _path)
{
    struct stat st;
    return (stat(_path.c_str(), &st) == 0);
}

std::uint64_t GetFileSize(const std::string& _path)
{
    struct stat st;
    if (stat(_path.c_str(), &st) != 0)
        return (std::uint64_t)-1;
    return (std::uint64_t)st.st_size;
}

} // namespace fileopt
