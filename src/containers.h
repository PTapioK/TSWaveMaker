#ifndef CONTAINERS_H
#define CONTAINERS_H

#include "main.h"

extern std::string cur_file;
extern CDataFile curdata;

extern std::map <std::string, Trigger*> triggers;
extern std::map <std::string, Tag*> tags;
extern std::map <std::string, Team*> teams;
extern std::map <std::string, Script*> scripts;
extern std::map <std::string, Taskforce*> taskforces;
extern std::map <std::string, std::string> aitriggers;
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

#endif // CONTAINERS_H
