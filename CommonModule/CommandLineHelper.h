// CommandLineHelper.h - Command line parameter parser
// Parses command line in format: key=value key2=value2 ...
// Server example: listenip=127.0.0.1:8400 loginsvr=127.0.0.1:8201 serverid=1
// Client example: svrip=127.0.0.1:8400 account=test password=123
#pragma once
#ifndef _INC_COMMANDLINEHELPER_
#define _INC_COMMANDLINEHELPER_

#include <string>
#include <vector>

class CommandLineHelper
{
public:
    CommandLineHelper();
    ~CommandLineHelper();

    // Initialize from process command line, returns true on success
    bool InitParam();

    // Look up by key, returns NULL if not found
    const char* GetParam(const char* _pszKey) const;

    // Returns all raw "key=value" strings
    const std::vector<std::string>& GetAllParams() const;

private:
    struct Param
    {
        std::string key;
        std::string value;
    };

    std::vector<Param>       m_vecParams;
    std::vector<std::string> m_vecRaw;
    bool                     m_bInited;
};

#endif // _INC_COMMANDLINEHELPER_
