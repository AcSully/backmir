#pragma once
#ifndef _INC_OFFLINESSELLSYSTEM_
#define _INC_OFFLINESSELLSYSTEM_

#include "ObjectData.h"
#include <vector>
#include <cstring>

struct SellItem
{
    ItemAttrib stAttrib;
    int        nUID;
    int        nMoney;
    int        nGold;
    int        nItemID;
    char       szItemName[64];
    char       szBuyerName[64];
};
BYTEBUFFER_STRUCT_OPERATOR(SellItem);

typedef std::vector<SellItem>   SellItemVector;
typedef std::vector<SellItem>   SoldItemList;
typedef std::vector<SellItem>   ExpireItemList;
typedef SellItem                ExpireItem;

class OfflineSellSystem
{
public:
    static OfflineSellSystem* GetInstance(bool _bDestroy = false)
    {
        static OfflineSellSystem* s_pIns = nullptr;
        if (_bDestroy) { delete s_pIns; s_pIns = nullptr; return nullptr; }
        if (!s_pIns) s_pIns = new OfflineSellSystem;
        return s_pIns;
    }

    bool Initialize(const char* _pszPath) { return true; }
    void CopyFromSQL() {}
    void QuerySoldItem(int _nUID, SoldItemList& _out) {}
    void QueryExpireItem(int _nUID, ExpireItemList& _out) {}
    void GetAllSellItems(SellItemVector& _out) {}
    const SellItem* GetSellItem(int _nItemID) { return nullptr; }
    bool AddSellItem(int _nUID, int _nMoney, int _nGold, const char* _pszName, ItemAttrib* _pItem) { return false; }
    void RemoveSellItem(int _nItemID) {}
    void AddSoldItem(int _nUID, int _nMoney, int _nGold, const char* _pszItemName, const char* _pszBuyerName) {}
    void RemoveSoldItem(int _nItemID) {}
    void RemoveExpireItem(int _nItemID) {}
    void UpdateExpireItems() {}
};

#endif // _INC_OFFLINESSELLSYSTEM_
