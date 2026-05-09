#include "QuestContext.h"

void QuestContext::SetQuestStep(int nQuestID, int nStep) {}
int QuestContext::GetQuestStep(int nQuestID) const { return 0; }
int QuestContext::GetQuestCounter(int nQuestID) const { return 0; }
void QuestContext::SetQuestCounter(int nQuestID, int nCounter) {}

bool QuestContext::IsQuestComplete(int nQuestID) const { return false; }
void QuestContext::SetQuestComplete(int nQuestID) {}
bool QuestContext::IsQuestAccept(int nQuestID) const { return false; }
