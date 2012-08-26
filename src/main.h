#ifndef MAIN_H
#define MAIN_H

#include <QtGui/QApplication>
#include <QMainWindow>
#include <QFileDialog>
#include <iostream>
#include <string>
#include <QtDebug>
#include <map>
#include <sstream>
#include <cstdio>
#include <cstdint>
#include <vector>

using namespace std;

#include "trigger.h"
#include "tag.h"
#include "event.h"
#include "action.h"
#include "team.h"
#include "taskforce.h"
#include "script.h"
#include "infodialog.h"

namespace Ui {
class MainWindow;
class TriggerSection;
}

class Tag;
class Trigger;
class Team;
class Taskforce;
class Script;

extern std::string cur_file;
extern std::map <std::string, Trigger*> triggers;
extern std::map <std::string, Tag*> tags;
extern std::map <std::string, Team*> teams;
extern std::map <std::string, Script*> scripts;
extern std::map <std::string, Taskforce*> taskforces;
extern std::map <std::string, std::string> aitriggers;

extern std::map <std::string, Trigger*>::iterator triggerIT;
extern std::map <std::string, Tag*>::iterator tagIT;
extern std::map <std::string, Team*>::iterator teamIT;
extern std::map <std::string, Script*>::iterator scriptIT;
extern std::map <std::string, Taskforce*>::iterator taskforceIT;
extern std::map <std::string, std::string>::iterator aitriggerIT;

extern std::vector<std::string> filedata;
extern std::vector<std::string>::iterator fileIT;

extern std::vector <Action*>::iterator actionIT;
extern std::vector <Event*>::iterator eventIT;

extern std::vector <int32_t> waypoints;
extern std::vector <int32_t>::iterator waypointIT;

extern const char alphas[26];

extern uint32_t sWPoint;

std::string fffID();
void SaveAllToFile();
void WriteToFileBuffer(std::string section, std::string ID);
void WriteToFileBuffer(std::string section, std::string ID, string value);
void AddToFileBuffer(std::string section, std::string ID, string value, int count);
void ReadFileToBuffer();
void ParseBuffer();
bool isFirstWave(string ID);
Tag* FindTag(string trigID);
string DecToWaypointID(int32_t dec);
string FindTriggerName(string trigID);
int32_t WaypointIDToDec(string wID);
void ClearValueAtBuffer(string line);

#define XOR(a,b) ((a)||(b) || (a) && (b))

#endif // MAIN_H
