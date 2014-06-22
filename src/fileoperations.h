#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include "main.h"

void SaveAllToBuffer();
void WriteValueToBuffer(std::string section, std::string ID);
void WriteValueToBuffer(std::string section, std::string ID, string value, bool sorting = true);
void EditValueInBuffer(std::string section, std::string ID, string value, int count);
void ReadFileToBuffer();
void DeleteLineInBuffer(string line);
void DeleteSectionInBuffer(string section);
void DeleteIDInBuffer(string ID);
void ParseSections();

Team* FindNewTeamFromFile(string teamID);
Script* FindNewScriptFromFile(string scriptID);
Taskforce* FindNewTaskforceFromFile(string taskforceID);

#endif // FILEOPERATIONS_H
