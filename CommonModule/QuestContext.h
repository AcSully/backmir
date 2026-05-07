// [reconstructed] 重建于 2026-05-06 —— 来源调用点：
//   BMServer/tolua/QuestContext.pkg (class interface)
//   BMServer/tolua/luaServer.cpp:1355 (HeroObject::GetQuest() returns QuestContext*)
//   luaServer.cpp:6727-6960 (IsQuestComplete/SetQuestComplete/IsQuestAccept/
//     GetQuestStep/SetQuestStep/GetQuestCounter/SetQuestCounter)
//   BMServer/CMainServer/CMainServer.cpp:1358 (_xBuf >> *quest, 2*MAX_QUEST_NUMBER bytes)
#pragma once
#ifndef _INC_QUESTCONTEXT_
#define _INC_QUESTCONTEXT_

#include <map>
#include "ByteBuffer.h"

class QuestContext
{
public:
    QuestContext() {}
    ~QuestContext() {}

public:
    bool IsQuestComplete(int _questid) const;
    void SetQuestComplete(int _questid);

    bool IsQuestAccept(int _questid) const;

    // Step == 0 means not accepted
    int  GetQuestStep(int _questid) const;
    void SetQuestStep(int _questid, int _step);

    int  GetQuestCounter(int _questid) const;
    void SetQuestCounter(int _questid, int _counter);

private:
    struct QuestEntry
    {
        bool bComplete;
        int  nStep;
        int  nCounter;

        QuestEntry() : bComplete(false), nStep(0), nCounter(0) {}
    };

    std::map<int, QuestEntry> m_xQuests;

    friend ByteBuffer& operator>>(ByteBuffer& _buf, QuestContext& _q);
    friend ByteBuffer& operator<<(ByteBuffer& _buf, const QuestContext& _q);
};

// Serialization: compact 2-byte-per-slot format (step in low byte, complete flag in high byte)
// MAX_QUEST_NUMBER slots total
inline ByteBuffer& operator>>(ByteBuffer& _buf, QuestContext& _q)
{
    // Read raw bytes; each slot is 2 bytes: [step][complete]
    // We don't know MAX_QUEST_NUMBER here, so read until buffer is exhausted
    unsigned char bStep = 0, bComplete = 0;
    int idx = 0;
    while (_buf.GetRemain() >= 2)
    {
        _buf >> bStep;
        _buf >> bComplete;
        if (bStep > 0 || bComplete)
        {
            _q.SetQuestStep(idx, (int)bStep);
            if (bComplete) _q.SetQuestComplete(idx);
        }
        ++idx;
    }
    return _buf;
}

inline ByteBuffer& operator<<(ByteBuffer& _buf, const QuestContext& _q)
{
    // Write is not needed for load path; stub
    return _buf;
}

#endif // _INC_QUESTCONTEXT_
