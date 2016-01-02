#ifndef CONTAINERS_H
#define CONTAINERS_H

#include "main.h"

struct unitContainer {
		QString unitID;
		QString name;
		uint16_t key;
};

struct variableContainer {
		bool set;
		QString name;
};

extern bool cloneOfNaming, ascNumNaming, alphabetNaming;

extern const QString settingsFilePath;
extern QSettings settings;

extern QString currentFilePath;
extern CDataFile currentFileData;

extern QString tsRulesPath;
extern QString fsRulesPath;

extern QString lastUsedPath;

extern std::map <std::string, Trigger*> triggers;
extern std::map <std::string, Tag*> tags;
extern std::map <std::string, Team*> teams;
extern std::map <std::string, Script*> scripts;
extern std::map <std::string, Taskforce*> taskforces;
extern std::map <std::string, std::string> aitriggers;

extern std::map <uint16_t, unitContainer> buildings;
extern std::map <QString, unitContainer> vehicles;
extern std::map <QString, unitContainer> infantry;
extern std::map <QString, unitContainer> aircraft;

extern std::map <uint16_t, QString> houses;

extern std::map <uint16_t, variableContainer> localvariables;
extern std::map <uint16_t, variableContainer> globalvariables;

extern std::vector <int32_t> waypoints;

typedef std::map <std::string, Trigger*>::const_iterator triggerIT;
typedef std::map <std::string, Tag*>::const_iterator tagIT;
typedef std::map <std::string, Team*>::const_iterator teamIT;
typedef std::map <std::string, Script*>::const_iterator scriptIT;
typedef std::map <std::string, Taskforce*>::const_iterator taskforceIT;
typedef std::map <std::string, std::string>::const_iterator aitriggerIT;

typedef std::vector <Action*>::const_iterator actionIT;
typedef std::vector <Event*>::const_iterator eventIT;
typedef std::vector <int32_t>::const_iterator waypointIT;

typedef std::map <QString, unitContainer>::iterator unitIT;

#endif // CONTAINERS_H
