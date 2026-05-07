#pragma once
#ifndef _INC_NOTIFYSYSTEM_
#define _INC_NOTIFYSYSTEM_

#include <vector>
#include <string>

class NotifySystem
{
public:
    static NotifySystem* GetInstance(bool _bDestroy = false)
    {
        static NotifySystem* s_pIns = nullptr;
        if (_bDestroy) { delete s_pIns; s_pIns = nullptr; return nullptr; }
        if (!s_pIns) s_pIns = new NotifySystem;
        return s_pIns;
    }

    bool Initialize(const char* _pszPath) { return true; }
    int QueryNotifyItem(std::vector<const char*>& _out) { return 0; }
};

typedef std::vector<const char*> CCharPtrVector;

#endif
