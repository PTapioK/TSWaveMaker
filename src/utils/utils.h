#ifndef UTILS_H
#define UTILS_H

#include "../main.h"
#include <QComboBox>

extern QString findFirstFreeID();

extern Tag* getTagByTriggerID(QString trigID);
extern Tag* getTagByName(QString name);
extern QString getTagNameByID(QString tagID);
extern QString getTagIDByName(QString name);

extern Trigger* getTriggerByName(QString name);
extern QString getTriggerIDByName(QString name);

extern Team* getTeamByName(QString name);
extern QString getTeamNameByID(QString ID);
extern QString getTeamIDByName(QString name);

extern QString getScriptNameByID(QString ID);
extern QString getScriptIDByName(QString name);
extern Script* getScriptByName(QString name);
extern QString getScriptNameByPosition(uint16_t pos);
extern SATargetType getScriptActionTargetType(uint8_t ID);

extern QString getTaskforceNameByID(QString ID);
extern QString getTaskforceIDByName(QString name);
extern QString getTaskforceNameByPosition(uint16_t pos);
extern Taskforce* getTaskforceByName(QString name);

extern QString getUnitNameByUnitID(QString unitID);
extern uint16_t getBuildingTypePosByKey(uint16_t key);

extern QString decToWaypointID(int32_t dec);
extern QString decToSmallAlphas(int32_t dec);
extern int32_t waypointIDToDec(QString wID);

extern QString getNameWithNextMark(QString name, int iter = 0, int numIter = -1000000);

extern int32_t getStringListMaxWidth(QStringList list, QFont font);
extern int32_t getComboBoxMaxWidth(QComboBox *box);
extern bool lessThanQString(const QString &str1, const QString &str2);
extern void clearContainers();

extern variableContainer* findLocalVariableByName(const QString &name, bool errorOnMissing = false);
extern uint16_t getLocalVariableKeyByName(const QString &name);

extern void showWarning(const QString &msg);

#endif // UTILS_H
