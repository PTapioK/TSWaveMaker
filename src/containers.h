#ifndef CONTAINERS_H
#define CONTAINERS_H

#include "main.h"

struct unitContainer {
		std::string unitID;
		std::string name;
		uint16_t key;
};

struct variableContainer {
		bool set;
		std::string name;
};

extern bool cloneOfNaming, ascNumNaming, alphabetNaming;

extern const std::string settingsFilePath;
extern CDataFile settingsFileData;

extern std::string currentFilePath;
extern CDataFile currentFileData;

extern std::string tsRulesPath;
extern std::string fsRulesPath;

extern std::string lastUsedPath;

extern std::map <std::string, Trigger*> triggers;
extern std::map <std::string, Tag*> tags;
extern std::map <std::string, Team*> teams;
extern std::map <std::string, Script*> scripts;
extern std::map <std::string, Taskforce*> taskforces;
extern std::map <std::string, std::string> aitriggers;

extern std::map <uint16_t, unitContainer> buildings;
extern std::map <std::string, unitContainer> vehicles;
extern std::map <std::string, unitContainer> infantry;
extern std::map <std::string, unitContainer> aircraft;

extern std::map <uint16_t, std::string> houses;

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

typedef std::map <std::string, unitContainer>::iterator unitIT;

#endif // CONTAINERS_H
