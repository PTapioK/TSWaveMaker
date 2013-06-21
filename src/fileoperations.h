#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include "main.h"

void SaveAllToFile();
void WriteToFileBuffer(std::string section, std::string ID);
void WriteToFileBuffer(std::string section, std::string ID, string value, bool sorting = true);
void AddToFileBuffer(std::string section, std::string ID, string value, int count);
void ReadFileToBuffer();
void ParseBuffer();

Team* FindNewTeamFromFile(string teamID);
Script* FindNewScriptFromFile(string scriptID);
Taskforce* FindNewTaskforceFromFile(string taskforceID);

#endif // FILEOPERATIONS_H
