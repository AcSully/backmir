// [reconstructed] �ؽ��� 2026-05-06
#include "utils.h"
#include <cctype>
#include <cstdio>
#include <sstream>
#if defined(_MSC_VER) && _MSC_VER < 1900
#  define snprintf _snprintf
#endif

namespace utils
{

std::vector<std::string> Split(const std::string& _str, char _sep)
{
    std::vector<std::string> out;
    if (_str.empty()) return out;
    std::string cur;
    for (char c : _str)
    {
        if (c == _sep) { out.push_back(cur); cur.clear(); }
        else           { cur += c; }
    }
    out.push_back(cur);
    return out;
}

std::string Trim(const std::string& _str)
{
    std::size_t i = 0, j = _str.size();
    while (i < j && std::isspace((unsigned char)_str[i])) ++i;
    while (j > i && std::isspace((unsigned char)_str[j - 1])) --j;
    return _str.substr(i, j - i);
}

std::string ToLower(const std::string& _str)
{
    std::string s = _str;
    for (auto& c : s) c = (char)std::tolower((unsigned char)c);
    return s;
}

std::string ToUpper(const std::string& _str)
{
    std::string s = _str;
    for (auto& c : s) c = (char)std::toupper((unsigned char)c);
    return s;
}

std::string IntToString(int _v)
{
    char buf[16];
    snprintf(buf, sizeof(buf), "%d", _v);
    return std::string(buf);
}

std::string Int64ToString(std::int64_t _v)
{
    char buf[32];
    snprintf(buf, sizeof(buf), "%lld", (long long)_v);
    return std::string(buf);
}

bool StartsWith(const std::string& _s, const std::string& _prefix)
{
    if (_prefix.size() > _s.size()) return false;
    return std::equal(_prefix.begin(), _prefix.end(), _s.begin());
}

bool EndsWith(const std::string& _s, const std::string& _suffix)
{
    if (_suffix.size() > _s.size()) return false;
    return std::equal(_suffix.rbegin(), _suffix.rend(), _s.rbegin());
}

} // namespace utils
