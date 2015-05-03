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

#include "containers.h"

#define XOR(a,b) ((a)||(b) || (a) && (b))

const char alphas[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };

#include "fileoperations.h"
#include "utils.h"

#endif // MAIN_H
