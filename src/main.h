#ifndef MAIN_H
#define MAIN_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <iostream>
#include <string>
#include <QtDebug>
#include <map>
#include <sstream>
#include <cstdio>
#include <cstdint>
#include <vector>
#include <algorithm>
#include "CDataFile/CDataFile.h"

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
extern CDataFile curdata;

extern std::vector <Action*>::iterator actionIT;
extern std::vector <Event*>::iterator eventIT;

extern std::vector <int32_t> waypoints;
extern std::vector <int32_t>::iterator waypointIT;

#define XOR(a,b) ((a)||(b) || (a) && (b))

const char alphas[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };

#include "fileoperations.h"
#include "utils.h"

#endif // MAIN_H
