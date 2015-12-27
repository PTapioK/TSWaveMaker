#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include "main.h"

void saveAllToBuffer();
void writeLineToBuffer(std::string section, std::string ID, std::string value);
void editValueInBuffer(std::string section, std::string ID, std::string value, int count);
void readFileToBuffer();
void deleteLineFromBuffer(std::string section, std::string ID);
void deleteSectionFromBuffer(std::string section);
void parseSections();
void parseRules();

Team* findNewTeamFromFile(std::string teamID);
Script* findNewScriptFromFile(std::string scriptID);
Taskforce* findNewTaskforceFromFile(std::string taskforceID);

std::string getUnitNameFromFile(std::string unitID, CDataFile *file);

#endif // FILEOPERATIONS_H
