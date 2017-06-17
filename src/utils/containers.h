#ifndef CONTAINERS_H
#define CONTAINERS_H

#include "../main.h"

const char alphas[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
const char small_alphas[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };

const uint8_t MAXPLAYERS = 8;

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
enum class SATargetType {
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

// Target types for trigger actions & events
enum class TargetType {
	NONE = 0,
	WAYPOINT,
	GLOBAL,
	LOCAL,
	HOUSE,
	TEAM,
	TRIGGER,
	ONOFF,
	EDITABLE,
	TEXT,
	TAG,
	BUILDING,
	INFANTRY,
	VEHICLE,
	AIRCRAFT,
	CONSTANT
};

extern FileHandler file;

extern Allies allies;
extern int32_t alliesID;

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

extern std::map <int16_t, QString> houses;

extern std::map <uint16_t, variableContainer> localvariables;
extern std::map <uint16_t, variableContainer> globalvariables;

extern std::map <uint16_t, QString> tutorial;

extern std::vector <int32_t> waypoints;
#endif // CONTAINERS_H
