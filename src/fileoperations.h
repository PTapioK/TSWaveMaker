#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include "main.h"
#include "containers.h"

struct unitContainer;
struct variableContainer;

void saveAllToBuffer();
void writeLineToBuffer(QString section, QString ID, QString value);
void editCountableValueInBuffer(QString section, QString ID, QString value, int count);
void readFileToBuffer();
void deleteLineFromBuffer(QString section, QString ID);
void deleteSectionFromBuffer(QString section);
void parseSections();
void parseRules();
void parseUnitTypesToMap(QSettings &rules, std::map<QString, unitContainer> &unitMap, QString type);
void parseVariablesToMap(QSettings &rules, std::map<uint16_t, variableContainer> &variableMap);
void parseHouseTypes(QSettings &rules);

Team* findNewTeamFromFile(std::string teamID);
Script* findNewScriptFromFile(std::string scriptID);
Taskforce* findNewTaskforceFromFile(std::string taskforceID);

#endif // FILEOPERATIONS_H
