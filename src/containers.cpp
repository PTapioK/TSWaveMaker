#include "containers.h"

string cur_file;
CDataFile curdata;

map <string, Trigger*> triggers;
map <string, Tag*> tags;
map <string, Team*> teams;
map <string, Script*> scripts;
map <string, Taskforce*> taskforces;
map <string, string> aitriggers;

vector <int32_t> waypoints;
