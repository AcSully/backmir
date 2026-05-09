// [reconstructed] 重建于 2026-05-06
#include "LuaBaseExecutor.h"

LuaBaseExecutor::LuaBaseExecutor()
{
}

LuaBaseExecutor::~LuaBaseExecutor()
{
    ClearCallItems();
}

void LuaBaseExecutor::AddCallItem(int _nCallType, const char* _pszFuncName, int _nParam)
{
    if (!_pszFuncName)
        return;
    LuaBaseCallItem* pItem = new LuaBaseCallItem();
    pItem->nCallType      = _nCallType;
    pItem->xCallFuncName  = _pszFuncName;
    pItem->nParam         = _nParam;
    m_xBaseCallList.push_back(pItem);
}

void LuaBaseExecutor::ClearCallItems()
{
    for (LuaBaseCallList::iterator it = m_xBaseCallList.begin();
         it != m_xBaseCallList.end(); ++it)
    {
        delete *it;
    }
    m_xBaseCallList.clear();
}
