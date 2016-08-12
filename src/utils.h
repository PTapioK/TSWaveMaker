#ifndef UTILS_H
#define UTILS_H

#include "main.h"

extern QString findFirstFreeID();
extern Tag* getTagByTriggerID(QString trigID);
extern QString decToWaypointID(int32_t dec);
extern QString decToSmallAlphas(int32_t dec);
extern int32_t waypointIDToDec(QString wID);
extern bool convertToBool(std::string str);
extern QString getTeamNameByID(QString ID);
extern QString getTriggerIDByName(QString name);
extern Team* getTeamByName(QString name);
extern QString getTeamIDByName(QString name);
extern QString getScriptNameByID(QString ID);
extern QString getScriptIDByName(QString name);
extern Trigger* getTriggerByName(QString name);
extern QString getTaskforceNameByID(QString ID);
extern QString getTaskforceIDByName(QString name);
extern QString getTaskforceNameByPosition(uint16_t pos);
extern Taskforce* getTaskforceByName(QString name);
extern Script* getScriptByName(QString name);
extern QString getScriptNameByPosition(uint16_t pos);
extern SATargetType getScriptActionTargetType(uint8_t ID);
extern uint32_t getStringListMaxWidth(QStringList list, QFont font);
extern uint16_t getBuildingTypePosByKey(uint16_t key);
extern QString convertBoolToYesNo(bool boolean);
extern std::string intToStr(int64_t integer);
extern void clearContainers();
extern QString getNameWithNextMark(QString name, int iter = 0, int numIter = -1000000);
extern QString getUnitNameByUnitID(QString unitID);
extern bool lessThanQString(const QString &str1, const QString &str2);

#endif // UTILS_H
