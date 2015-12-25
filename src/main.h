#ifndef MAIN_H
#define MAIN_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QLineEdit>
#include <QCloseEvent>
#include <QMap>
#include <QString>
#include <QSettings>

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <cstdio>
#include <cstdint>
#include <cmath>
#include <vector>
#include <algorithm>
#include <array>
#include <assert.h>

#include "CDataFile/CDataFile.h"

// Script Action Target Type
enum SATargetType {
	NONE = 1,
	WAYPOINT,
	TARGET,
	MISSION,
	UNLOAD,
	EDITABLE,
	GLOBAL,
	SCRIPT,
	TASKFORCE,
	HOUSE,
	LOCAL,
	FACING,
	BUILDING,
	BALLOON
};

#include "trigger.h"
#include "tag.h"
#include "event.h"
#include "action.h"
#include "team.h"
#include "taskforce.h"
#include "script.h"
#include "infodialog.h"
#include "settingsdialog.h"

namespace Ui {
class MainWindow;
class TriggerSection;
class TeamSection;
class ScriptSection;
class TaskforceSection;
class InfoDialog;
class SettingsDialog;
}

class Tag;
class Trigger;
class Team;
class Taskforce;
class Script;

#include "containers.h"

const char alphas[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
const char small_alphas[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };

#include "fileoperations.h"
#include "utils.h"

#define CAPTIONBASE (tr("TSWaveMaker ") + tr(VERSION) + tr(" version"))

#endif // MAIN_H
