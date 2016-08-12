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

extern FileHandler fileHandler;

extern std::map <QString, Trigger*> triggers;
extern std::map <QString, Tag*> tags;
extern std::map <QString, Team*> teams;
extern std::map <QString, Script*> scripts;
extern std::map <QString, Taskforce*> taskforces;
extern std::map <QString, QString> aitriggers;

extern std::map <uint16_t, unitContainer> buildings;
extern std::map <QString, unitContainer> vehicles;
extern std::map <QString, unitContainer> infantry;
extern std::map <QString, unitContainer> aircraft;

extern std::map <uint16_t, QString> houses;

extern std::map <uint16_t, variableContainer> localvariables;
extern std::map <uint16_t, variableContainer> globalvariables;

extern std::vector <int32_t> waypoints;

typedef std::map <QString, Trigger*>::const_iterator triggerIT;
typedef std::map <QString, Tag*>::const_iterator tagIT;
typedef std::map <QString, Team*>::const_iterator teamIT;
typedef std::map <QString, Script*>::const_iterator scriptIT;
typedef std::map <QString, Taskforce*>::const_iterator taskforceIT;
typedef std::map <QString, QString>::const_iterator aitriggerIT;
typedef std::map <QString, unitContainer>::iterator unitIT;

typedef std::vector <Action*>::const_iterator actionIT;
typedef std::vector <Event*>::const_iterator eventIT;
typedef std::vector <int32_t>::const_iterator waypointIT;

#endif // CONTAINERS_H
