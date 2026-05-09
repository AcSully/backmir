// [reconstructed] 重建于 2026-05-06
#pragma once
#ifndef _INC_CRONSCHEDULE_
#define _INC_CRONSCHEDULE_

class CronJobScheduler
{
public:
    CronJobScheduler() {}
    ~CronJobScheduler() {}

    void Update() {}
    int AddJob(int _nInterval, int (*_pFunc)(int, int), int _nArg = 0) { return 0; }
    void RemoveJob(int _nJobId) {}
    // cron-expression variant used by GameWorld
    int AddCronJob(int _nEventId, const char* /*_pszCronExpr*/, int (*_pFunc)(int, int), int _nArg = 0) { return AddJob(_nEventId, _pFunc, _nArg); }
    void RemoveCronJob(int _nJobId) { RemoveJob(_nJobId); }
};

#endif
