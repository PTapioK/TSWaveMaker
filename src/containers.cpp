#include "containers.h"

string cur_file;
CDataFile curdata;

map <string, Trigger*> triggers;
map <string, Tag*> tags;
map <string, Team*> teams;
map <string, Script*> scripts;
map <string, Taskforce*> taskforces;
map <string, string> aitriggers;

map <uint16_t, unitContainer> buildingnames;
map <uint16_t, unitContainer> vehiclenames;
map <uint16_t, unitContainer> infantrynames;
map <uint16_t, unitContainer> aircraftnames;

map <uint16_t, string> houses;

map <uint16_t, variableContainer> localvariables;
map <uint16_t, variableContainer> globalvariables;

vector <int32_t> waypoints;
