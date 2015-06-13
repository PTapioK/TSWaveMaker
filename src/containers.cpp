#include "containers.h"

const string settings_ini = "settings.ini";
CDataFile settings_data(settings_ini);

string cur_file;
CDataFile curdata;

string ts_rules;
string fs_rules;

string last_path = ".";

map <string, Trigger*> triggers;
map <string, Tag*> tags;
map <string, Team*> teams;
map <string, Script*> scripts;
map <string, Taskforce*> taskforces;
map <string, string> aitriggers;

map <uint16_t, unitContainer> buildingnames;
map <string, unitContainer> vehiclenames;
map <string, unitContainer> infantrynames;
map <string, unitContainer> aircraftnames;

map <uint16_t, string> houses;

map <uint16_t, variableContainer> localvariables;
map <uint16_t, variableContainer> globalvariables;

vector <int32_t> waypoints;

bool cloneOfNaming, ascNumNaming, alphabetNaming;
