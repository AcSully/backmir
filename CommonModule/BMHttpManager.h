// BMHttpManager.h - HTTP request manager (stub)
#pragma once
#ifndef _INC_BMHTTPMANAGER_
#define _INC_BMHTTPMANAGER_

#include <string>
#include <functional>

class BMHttpManager
{
public:
    static BMHttpManager* GetInstance()
    {
        static BMHttpManager* s_pIns = nullptr;
        if (!s_pIns) s_pIns = new BMHttpManager;
        return s_pIns;
    }

    typedef std::function<void(const std::string&)> HttpCallback;

    // Synchronous HTTP GET (stub: does nothing, calls callback with empty string)
    void DoGetRequestSync(const std::string& /*url*/, HttpCallback cb)
    {
        if (cb) cb("");
    }

private:
    BMHttpManager() {}
    ~BMHttpManager() {}
};

#endif // _INC_BMHTTPMANAGER_
