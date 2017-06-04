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

#include "utils/settings.h"
#include "logic/trigger.h"
#include "logic/tag.h"
#include "logic/event.h"
#include "logic/action.h"
#include "logic/team.h"
#include "logic/taskforce.h"
#include "logic/script.h"
#include "ui/infodialog.h"
#include "ui/settingsdialog.h"
#include "utils/filehandler.h"

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

#include "utils/containers.h"
#include "utils/utils.h"

#define CAPTIONBASE (tr("TSWaveMaker ") + tr(VERSION) + tr(" version"))

#endif // MAIN_H
