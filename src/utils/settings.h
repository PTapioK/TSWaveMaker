#ifndef SETTINGS_H
#define SETTINGS_H

#include "../main.h"

namespace Settings
{
extern void loadSettings();
extern QString getRulesPathFor(QString fileName, QString path);

extern const QString settingsFilePath;
extern const QString scriptStringsPath;
extern const QString triggerStringsPath;

extern QString tsRulesPath;
extern QString fsRulesPath;
extern QString lastUsedPath;

extern QSettings settings;
extern QSettings scriptStrings;
extern QSettings triggerStrings;

extern bool cloneOfNaming, ascNumNaming, alphabetNaming;

extern bool disableWarnings;
}

#endif // SETTINGS_H
