#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include "main.h"

void SaveAllToBuffer();
void WriteValueToBuffer(std::string section, std::string ID);
void WriteValueToBuffer(std::string section, std::string ID, string value);
void EditValueInBuffer(std::string section, std::string ID, string value, int count);
void ReadFileToBuffer();
void DeleteValueInBuffer(string section, string ID);
void DeleteSectionInBuffer(string section);
void ParseSections();
void ParseRules();

Team* FindNewTeamFromFile(string teamID);
Script* FindNewScriptFromFile(string scriptID);
Taskforce* FindNewTaskforceFromFile(string taskforceID);

string GetUnitNameFromFile(string unitID, CDataFile *file);

#endif // FILEOPERATIONS_H
