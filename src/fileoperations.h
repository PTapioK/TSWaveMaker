#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include "main.h"
#include "containers.h"

struct unitContainer;
struct variableContainer;

void saveAllToBuffer();
void writeLineToBuffer(std::string section, std::string ID, std::string value);
void editCountableValueInBuffer(std::string section, std::string ID, std::string value, int count);
void readFileToBuffer();
void deleteLineFromBuffer(std::string section, std::string ID);
void deleteSectionFromBuffer(std::string section);
void parseSections();
void parseRules();
void parseUnitTypesToMap(QSettings &rules, std::map<QString, unitContainer> &unitMap, QString type);
void parseVariablesToMap(QSettings &rules, std::map<uint16_t, variableContainer> &variableMap);
void parseBuildingTypes(QSettings &rules, uint16_t &index, int16_t keyPlus = 0, bool useKeyInstead = false);
void parseHouseTypes(QSettings &rules);

Team* findNewTeamFromFile(std::string teamID);
Script* findNewScriptFromFile(std::string scriptID);
Taskforce* findNewTaskforceFromFile(std::string taskforceID);

#endif // FILEOPERATIONS_H
