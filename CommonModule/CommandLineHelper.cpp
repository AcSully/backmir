// CommandLineHelper.cpp - Command line parameter parser implementation
#include "CommandLineHelper.h"
#ifdef _WIN32
#  include <windows.h>
#endif
#include <string>
#include <vector>

CommandLineHelper::CommandLineHelper()
    : m_bInited(false)
{
}

CommandLineHelper::~CommandLineHelper()
{
}

bool CommandLineHelper::InitParam()
{
    m_vecParams.clear();
    m_vecRaw.clear();

#ifdef _WIN32
    const char* pszCmdLine = GetCommandLineA();
#else
    static char s_cmdline[4096] = {0};
    FILE* f = fopen("/proc/self/cmdline", "rb");
    if (f) {
        size_t n = fread(s_cmdline, 1, sizeof(s_cmdline) - 1, f);
        fclose(f);
        for (size_t i = 0; i < n - 1; ++i)
            if (s_cmdline[i] == '\0') s_cmdline[i] = ' ';
    }
    const char* pszCmdLine = s_cmdline;
#endif
    if (!pszCmdLine)
    {
        m_bInited = true;
        return true;
    }

    std::string xLine(pszCmdLine);
    bool bSkippedExe = false;
    size_t pos = 0;

    while (pos < xLine.size())
    {
        while (pos < xLine.size() && xLine[pos] == ' ')
            ++pos;
        if (pos >= xLine.size())
            break;

        std::string token;
        if (xLine[pos] == '"')
        {
            ++pos;
            while (pos < xLine.size() && xLine[pos] != '"')
                token += xLine[pos++];
            if (pos < xLine.size())
                ++pos;
        }
        else
        {
            while (pos < xLine.size() && xLine[pos] != ' ')
                token += xLine[pos++];
        }

        if (token.empty())
            continue;

        if (!bSkippedExe)
        {
            bSkippedExe = true;
            continue;
        }

        m_vecRaw.push_back(token);

        size_t eq = token.find('=');
        if (eq != std::string::npos)
        {
            Param p;
            p.key   = token.substr(0, eq);
            p.value = token.substr(eq + 1);
            m_vecParams.push_back(p);
        }
    }

    m_bInited = true;
    return true;
}

const char* CommandLineHelper::GetParam(const char* _pszKey) const
{
    if (!_pszKey)
        return NULL;
    for (size_t i = 0; i < m_vecParams.size(); ++i)
    {
        if (m_vecParams[i].key == _pszKey)
            return m_vecParams[i].value.c_str();
    }
    return NULL;
}

const std::vector<std::string>& CommandLineHelper::GetAllParams() const
{
    return m_vecRaw;
}
