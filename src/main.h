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
#include <QDebug>
#include <QTextStream>

#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <array>
#include <algorithm>

#include <cassert>
#include <cstdio>
#include <cstdint>
#include <cmath>

enum class SATargetType;

#include "settings.h"
#include "trigger.h"
#include "tag.h"
#include "event.h"
#include "action.h"
#include "team.h"
#include "taskforce.h"
#include "script.h"
#include "infodialog.h"
#include "settingsdialog.h"
#include "filehandler.h"

namespace Ui {
class MainWindow;
class TriggerSection;
class TeamSection;
class ScriptSection;
class TaskforceSection;
class InfoDialog;
class SettingsDialog;
}

class FileHandler;
class Tag;
class Trigger;
class Team;
class Taskforce;
class Script;

#include "containers.h"
#include "utils.h"

#define CAPTIONBASE (tr("TSWaveMaker ") + tr(VERSION) + tr(" version"))

#endif // MAIN_H
