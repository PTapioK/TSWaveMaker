#include "containers.h"

FileHandler file;

Allies allies;
int32_t alliesID = 1;

std::map <QString, Trigger*> triggers;
std::map <QString, Tag*> tags;
std::map <QString, Team*> teams;
std::map <QString, Script*> scripts;
std::map <QString, Taskforce*> taskforces;
std::map <QString, QString > aitriggers;

std::map <uint16_t, unitContainer> buildings;
std::map <QString, unitContainer> vehicles;
std::map <QString, unitContainer> infantry;
std::map <QString, unitContainer> aircraft;

std::map <int16_t, QString> houses;

std::map <uint16_t, variableContainer> localvariables;
std::map <uint16_t, variableContainer> globalvariables;

QMap <uint16_t, QString> tutorial;

std::vector <int32_t> waypoints;
