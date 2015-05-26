#ifndef UTILS_H
#define UTILS_H

#include "main.h"

extern std::string fffID();
extern bool isFirstTrigger(string ID);
extern Tag* FindTag(string trigID);
extern string DecToWaypointID(int32_t dec);
extern string GetTriggerNameByID(string trigID);
extern int32_t WaypointIDToDec(string wID);
extern bool ConverToBool(string str);
extern string GetValueStr(string line);
extern string GetTeamNameByID(string ID);
extern string GetTriggerIDByName(string name);
extern Trigger* FindNearestTimerTrigger(string trigID);
extern Team* GetTeamByName(string name);
extern string GetTeamIDByName(string name);
extern string GetScriptNameByID(string ID);
extern string GetScriptIDByName(string name);
extern Trigger* GetTriggerByName(string name);
extern string GetTaskforceNameByID(string ID);
extern string GetTaskforceIDByName(string name);
extern string GetTaskforceNameByPosition(uint16_t pos);
extern Script* GetScriptByName(string name);
extern string GetScriptNameByPosition(uint16_t pos);
extern QString GetScriptActionMeaning(uint8_t ID);
extern SATargetType GetScriptActionTargetType(uint8_t ID);
extern QStringList GetScriptActionTargetStrings(SATargetType type);
extern uint32_t GetStringListMaxWidth(QStringList list, QFont font);
extern uint16_t GetBuildingTypePosByKey(int key);
extern string ConverBoolToYesNo(bool boolean);
extern string IntToStr(int integer);
extern void ClearContainers();
extern void LoadSettings(bool ask = true);
extern string TSRulesPath(string path);
extern string FSRulesPath(string path);

#endif // UTILS_H
