#include "main.h"
#include "mainwindow.h"

string cur_file;

map <string, Trigger*> triggers;
map <string, Tag*> tags;
map <string, Team*> teams;
map <string, Script*> scripts;
map <string, Taskforce*> taskforces;
map <string, string> aitriggers;

map <string, Trigger*>::iterator triggerIT;
map <string, Tag*>::iterator tagIT;
map <string, Team*>::iterator teamIT;
map <string, Script*>::iterator scriptIT;
map <string, Taskforce*>::iterator taskforceIT;
map <string, string>::iterator aitriggerIT;

vector <Action*>::iterator actionIT;
vector <Event*>::iterator eventIT;

vector<string> filedata;
CDataFile curdata;

vector <int32_t> waypoints;
vector <int32_t>::iterator waypointIT;

const char alphas[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };

uint32_t sWPoint = 8;

// Find First Free ID
string fffID() {
	string nextID;
	stringstream ssID;

	int32_t i = 1000002;

	vector<string> IDTemp;
	vector<string>::iterator IDIT;

	if(triggers.empty() && tags.empty() && teams.empty() && scripts.empty() && taskforces.empty()) {
		ssID << "0" << i;
		return string(ssID.str().c_str());
	}

	for(triggerIT = triggers.begin(); triggerIT != triggers.end(); ++triggerIT) {
		IDTemp.push_back((*triggerIT).second->getID());
	}

	for(tagIT = tags.begin(); tagIT != tags.end(); ++tagIT) {
		IDTemp.push_back((*tagIT).second->getID());
	}

	for(teamIT = teams.begin(); teamIT != teams.end(); ++teamIT) {
		IDTemp.push_back((*teamIT).first);
	}

	for (scriptIT = scripts.begin(); scriptIT != scripts.end(); ++scriptIT) {
		IDTemp.push_back((*scriptIT).second->getID());
	}

	for (taskforceIT = taskforces.begin(); taskforceIT != taskforces.end(); ++taskforceIT) {
		IDTemp.push_back((*taskforceIT).second->getID());
	}

	sort(IDTemp.begin(), IDTemp.end());

	IDIT = find(IDTemp.begin(), IDTemp.end(), "01000002");

	if(IDIT == IDTemp.end()) {
		IDIT = IDTemp.begin();
	}

	string a = "";
	while(1) {
		ssID.str("");
		ssID << "0" << i;
		nextID = string(ssID.str().c_str());

		if(IDIT == IDTemp.end()) {
			a = "";
		} else {
			a = (*IDIT);
		}


		if(a == nextID) {
			++i;
		} else {
			return nextID;
		}

		if(IDIT != IDTemp.end()) {
			++IDIT;
		} else {
			break;
		}

	}

	ssID.str("");
	ssID << "0" << i;
	nextID = string(ssID.str().c_str());

	return nextID;
}

string GetValueStr(string line) {
	string::size_type pos;
	pos = line.find("=");
	line = line.substr(pos+1);
	return line.substr(0, line.find('\n'));
}

bool isFirstWave(string ID) {
	bool retVal = true;
	map <string, Trigger*>::iterator triggerIT = triggers.begin();
	if((*triggerIT).second->getID() != ID) {
		retVal = false;
	}
	return retVal;
}

Tag* FindTag(string trigID) {
	for(tagIT = tags.begin(); tagIT != tags.end(); ++tagIT) {
		if((*tagIT).second->getTriggerID() == trigID) {
			return (*tagIT).second;
		}
	}
	return NULL;
}

string DecToWaypointID(int dec) {
	string retVal;
	dec=dec+1;
	while(dec != 0) {
		--dec;
		retVal = alphas[dec % 26] + retVal;
		dec /= 26;
	}
	return retVal;
}

string GetTriggerNameByID(string trigID) {
	for(map <string, Trigger*>::iterator triggerIT = triggers.begin(); triggerIT != triggers.end(); ++triggerIT) {
		if((*triggerIT).second->getID() == trigID) {
			return triggerIT->second->getName().toStdString();
		}
	}
	return NULL;
}

string GetTriggerIDByName(string name) {
	for(map <string, Trigger*>::iterator triggerIT = triggers.begin(); triggerIT != triggers.end(); ++triggerIT) {
		if((*triggerIT).second->getName().toStdString() == name) {
			return triggerIT->second->getID();
		}
	}
	return string("");
}

Trigger* GetTriggerByName(string name) {
	for(map <string, Trigger*>::iterator triggerIT = triggers.begin(); triggerIT != triggers.end(); ++triggerIT) {
		if((*triggerIT).second->getName().toStdString() == name) {
			return triggerIT->second;
		}
	}
	return NULL;
}

int32_t WaypointIDToDec(string wID) {
	int32_t value = 0;
	int i = wID.length();
	while(1) {
		if(i == 0) { break; }
		--i;
		const char chr = *wID.substr(i, 1).c_str();
		int32_t multip = 0;
		for(int j = 0; j != 26; ++j) {
			if(chr == alphas[j]) {
				multip = j+1;
				break;
			}
		}
		int p = pow(26.0, int(wID.length() - (i+1)));
		value = value + (multip * p);
	}
	return value-1;
}

bool ConverToBool(string str) {
	if(str == "yes") {
		return true;
	}
	if(str == "no") {
		return false;
	}
	if(str == "true") {
		return true;
	}
	if(str == "false") {
		return false;
	}

	return false;
}

string ConverBoolToYesNo(bool boolean) {
	if(boolean == true) {
		return "yes";
	} else {
		return "no";
	}
}

string IntToStr(int integer) {
	stringstream ss;
	ss << integer;
	return ss.str();
}

string GetTeamNameByID(string ID) {
	for(teamIT = teams.begin(); teamIT != teams.end(); ++teamIT) {
		if(teamIT->second->getID() == ID) {
			return teamIT->second->getName();
		}
	}
	return string("");
}

Trigger* FindNearestTimerTrigger(string trigID) {
	map <string, Trigger*>::iterator triggerIT = triggers.find(trigID);
	while(triggerIT != triggers.begin()) {
		--triggerIT;
		if(triggerIT->second->hasActionType(27)) {
			return triggerIT->second;
		}
	}

	triggerIT = triggers.find(trigID);
	while(triggerIT != triggers.end()) {
		++triggerIT;
		if(triggerIT->second->hasActionType(27)) {
			return triggerIT->second;
		}
	}

	return NULL;
}

Team* GetTeamByName(string name) {
	for(teamIT = teams.begin(); teamIT != teams.end(); ++teamIT) {
		if(teamIT->second->getName() == name) {
			return teamIT->second;
		}
	}
	return NULL;
}

string GetTeamIDByName(string name) {
	for(teamIT = teams.begin(); teamIT != teams.end(); ++teamIT) {
		if(teamIT->second->getName() == name) {
			return teamIT->second->getID();
		}
	}
	return string("");
}

string GetScriptNameByID(string ID) {
	for(scriptIT = scripts.begin(); scriptIT != scripts.end(); ++scriptIT) {
		if(scriptIT->second->getID() == ID) {
			return scriptIT->second->getName();
		}
	}
	return "";
}

string GetScriptIDByName(string name) {
	for(scriptIT = scripts.begin(); scriptIT != scripts.end(); ++scriptIT) {
		if(scriptIT->second->getName() == name) {
			return scriptIT->second->getID();
		}
	}
	return "";
}

string GetTaskforceNameByID(string ID) {
	for(taskforceIT = taskforces.begin(); taskforceIT != taskforces.end(); ++taskforceIT) {
		if(taskforceIT->second->getID() == ID) {
			return taskforceIT->second->getName();
		}
	}
	return "";
}

string GetTaskforceIDByName(string name) {
	for(taskforceIT = taskforces.begin(); taskforceIT != taskforces.end(); ++taskforceIT) {
		if(taskforceIT->second->getName() == name) {
			return taskforceIT->second->getID();
		}
	}
	return "";
}

Script* GetScriptByName(string name) {
	for(scriptIT = scripts.begin(); scriptIT != scripts.end(); ++scriptIT) {
		if(scriptIT->second->getName() == name) {
			return scriptIT->second;
		}
	}
	return NULL;
}

QString GetScriptActionMeaning(uint8_t ID) {
	switch(ID) {
	case 0:
		return "Attack a kind of target";
	case 1:
		return "Attack the waypoint";
	case 3:
		return "Move to the waypoint";
	case 8:
		return "Transport releases freight";
	case 9:
		return "Deploy";
	case 11:
		return "Execute mission";
	case 16:
		return "Patrol to waypoint";
	case 37:
		return "Delete team members";
	default:
		return "Not Implemented!";
	}
}

SATargetType GetScriptActionTargetType(uint8_t ID) {
	switch(ID) {
	case 0:
		return BUILDING;
	case 1:
		return WAYPOINT;
	case 3:
		return WAYPOINT;
	case 8:
		return UNLOAD;
	case 11:
		return MISSION;
	case 16:
		return WAYPOINT;
	default:
		return NONE;
	}
}

QStringList GetScriptActionTargetStrings(SATargetType type) {
	QStringList list;
	switch(type) {
	case BUILDING:
		list << "Cancel attack";
		list << "Everything";
		list << "Buildings";
		list << "Harvester";
		list << "Infantry";
		list << "Vehicles";
		list << "Factories";
		list << "Buildings of base defense";
		list << "Everything which threatens the own base";
		list << "Power plants";
		list << "Conquer buildings";
		break;
	case WAYPOINT:
		for(waypointIT = waypoints.begin(); waypointIT != waypoints.end(); ++waypointIT) {
			stringstream ss;
			ss << (*waypointIT);
			list << ss.str().c_str();
		}
		break;
	case UNLOAD:
		list << "The remaining script commands are valid for both, the transport and its freight";
		list << "The remaining script commands are valid only for the transport, not for its freight";
		list << "The remaining script commands are valid only for the freight, not for the transport";
		list << "The remaining script commands are not executed";
		break;
	case MISSION:
		list << "Deaktivate the taskforce. Further commands do not work";
		list << "Attack nearest enemy";
		list << "Move";
		list << "QMove";
		list << "Retreat. The units may leave the map";
		list << "Defend the position. If necessary follow the opponent in order to attack him, but come back asap";
		list << "Defend the position. Do not move";
		list << "Enter a building or transport within Sight range";
		list << "Capture any buildings in the neighborhood";
		list << "Move into & get eaten";
		list << "Begin to harvest Tiberium (-waste)";
		list << "Defend the location in Sight range. If necessary follow the opponent in order to attack him, but no need to come back";
		list << "Return to the place where this unit was spawned. Effective for harvesters (HARV) only...";
		list << "Stop";
		list << "Ambush (wait until discovered)";
		list << "Hunt";
		list << "Unload";
		list << "Sabotage (move in & destroy)";
		list << "Construction";
		list << "Deconstruction";
		list << "Repair";
		list << "Rescue";
		list << "Missile";
		list << "Harmless";
		list << "Open";
		list << "Patrol";
		list << "Paradrop approach drop zone";
		list << "Paradrop overlay drop zone";
		list << "Wait";
		list << "Attack move";
		break;
	default:
		list << "";
	}
	return list;
}

uint32_t GetStringListMaxWidth(QStringList list, QFont font) {
	vector <uint32_t> widths;
	QFontMetrics metr(font);
	for(QStringList::Iterator listIT = list.begin(); listIT != list.end(); ++listIT) {
		QString str;
		widths.push_back(metr.width(*listIT));
	}
	sort(widths.begin(), widths.end());
	return *(widths.end()-1);
}

int main(int argc, char *argv[])
{
	curdata.m_Flags |= AUTOCREATE_KEYS;
	curdata.m_Flags |= AUTOCREATE_SECTIONS;
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
