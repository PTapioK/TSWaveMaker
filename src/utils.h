#ifndef UTILS_H
#define UTILS_H

#include "main.h"

extern std::string fffID();
extern bool isFirstTrigger(std::string ID);
extern Tag* findTag(std::string trigID);
extern std::string decToWaypointID(int32_t dec);
extern std::string convertToSmallAlphas(int32_t dec);
extern std::string getTriggerNameByID(std::string trigID);
extern int32_t waypointIDToDec(std::string wID);
extern bool convertToBool(std::string str);
extern std::string getValueStr(std::string line);
extern std::string getTeamNameByID(std::string ID);
extern std::string getTriggerIDByName(std::string name);
extern Trigger* findNearestTimerTrigger(std::string trigID);
extern Team* getTeamByName(std::string name);
extern std::string getTeamIDByName(std::string name);
extern std::string getScriptNameByID(std::string ID);
extern std::string getScriptIDByName(std::string name);
extern Trigger* getTriggerByName(std::string name);
extern std::string getTaskforceNameByID(std::string ID);
extern std::string getTaskforceIDByName(std::string name);
extern std::string getTaskforceNameByPosition(uint16_t pos);
extern Taskforce* getTaskforceByName(std::string name);
extern Script* getScriptByName(std::string name);
extern std::string getScriptNameByPosition(uint16_t pos);
extern QString getScriptActionMeaning(uint8_t ID);
extern SATargetType getScriptActionTargetType(uint8_t ID);
extern QStringList getScriptActionTargetStrings(SATargetType type);
extern uint32_t getStringListMaxWidth(QStringList list, QFont font);
extern uint16_t getBuildingTypePosByKey(int key);
extern std::string converBoolToYesNo(bool boolean);
extern std::string intToStr(int integer);
extern void clearContainers();
extern void loadSettings(bool ask = true);
extern std::string rulesPathForTS(std::string path);
extern std::string rulesPathForFS(std::string path);
extern std::string getNameWithNextMark(std::string name, int iter = 0, int numIter = -1000000);
extern std::string getUnitNameByUnitID(std::string unitID);

#endif // UTILS_H
