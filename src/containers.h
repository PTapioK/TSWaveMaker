#ifndef CONTAINERS_H
#define CONTAINERS_H

#include "main.h"

struct unitContainer {
		string unitID;
		string name;
		uint16_t key;
};

struct variableContainer {
		bool set;
		string name;
};

extern bool cloneOfNaming, ascNumNaming, alphabetNaming;

extern const std::string settings_ini;
extern CDataFile settings_data;

extern std::string cur_file;
extern CDataFile curdata;

extern std::string ts_rules;
extern std::string fs_rules;

extern std::string last_path;

extern std::map <std::string, Trigger*> triggers;
extern std::map <std::string, Tag*> tags;
extern std::map <std::string, Team*> teams;
extern std::map <std::string, Script*> scripts;
extern std::map <std::string, Taskforce*> taskforces;
extern std::map <std::string, std::string> aitriggers;

extern std::map <uint16_t, unitContainer> buildingnames;
extern std::map <string, unitContainer> vehiclenames;
extern std::map <string, unitContainer> infantrynames;
extern std::map <string, unitContainer> aircraftnames;

extern std::map <uint16_t, std::string> houses;

extern std::map <uint16_t, variableContainer> localvariables;
extern std::map <uint16_t, variableContainer> globalvariables;

extern std::vector <int32_t> waypoints;

typedef std::map <std::string, Trigger*>::iterator triggerIT;
typedef std::map <std::string, Tag*>::iterator tagIT;
typedef std::map <std::string, Team*>::iterator teamIT;
typedef std::map <std::string, Script*>::iterator scriptIT;
typedef std::map <std::string, Taskforce*>::iterator taskforceIT;
typedef std::map <std::string, std::string>::iterator aitriggerIT;

typedef std::vector <Action*>::iterator actionIT;
typedef std::vector <Event*>::iterator eventIT;
typedef std::vector <int32_t>::iterator waypointIT;

typedef std::map <string, unitContainer>::iterator unitIT;

#endif // CONTAINERS_H
