#ifndef MAIN_H
#define MAIN_H

#include <QtGui/QApplication>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <string>
#include <QtDebug>
#include <map>
#include <sstream>
#include <cstdio>
#include <cstdint>
#include <vector>
#include <algorithm>

using namespace std;

// Script Action Target Type
enum SATargetType {
	NONE = 1,
	WAYPOINT,
	BUILDING,
	MISSION,
	UNLOAD
};

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
class TeamSection;
class ScriptSection;
class TaskforceSection;
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

extern std::vector <Action*>::iterator actionIT;
extern std::vector <Event*>::iterator eventIT;

extern std::vector <int32_t> waypoints;
extern std::vector <int32_t>::iterator waypointIT;

extern const char alphas[26];

extern uint32_t sWPoint;

std::string fffID();
bool isFirstWave(string ID);
Tag* FindTag(string trigID);
string DecToWaypointID(int32_t dec);
string GetTriggerNameByID(string trigID);
int32_t WaypointIDToDec(string wID);
void ClearValueAtBuffer(string line);
bool ConverToBool(string str);
string GetValueStr(string line);
string GetTeamNameByID(string ID);
string GetTriggerIDByName(string name);
Trigger* FindNearestTimerTrigger(string trigID);
Team* GetTeamByName(string name);
string GetTeamIDByName(string name);
string GetScriptNameByID(string ID);
string GetScriptIDByName(string name);
Trigger* GetTriggerByName(string name);
string GetTaskforceNameByID(string ID);
string GetTaskforceIDByName(string name);
Script* GetScriptByName(string name);
QString GetScriptActionMeaning(uint8_t ID);
SATargetType GetScriptActionTargetType(uint8_t ID);
QStringList GetScriptActionTargetStrings(SATargetType type);
uint32_t GetStringListMaxWidth(QStringList list, QFont font);
string ConverBoolToYesNo(bool boolean);
string IntToStr(int integer);

#define XOR(a,b) ((a)||(b) || (a) && (b))

#include "fileoperations.h"

#endif // MAIN_H
