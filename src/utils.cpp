#include "utils.h"


// Find First Free ID
string fffID() {
	string nextID;
	stringstream ssID;

	int32_t i = 1000000;

	vector<string> IDTemp;
	vector<string>::iterator IDIT;

	if(triggers.empty() && tags.empty() && teams.empty() && scripts.empty() && taskforces.empty() && aitriggers.empty()) {
		ssID << "0" << i;
		return string(ssID.str().c_str());
	}

	for(triggerIT IT = triggers.begin(); IT != triggers.end(); ++IT) {
		IDTemp.push_back((*IT).second->getID());
	}

	for(tagIT IT = tags.begin(); IT != tags.end(); ++IT) {
		IDTemp.push_back((*IT).second->getID());
	}

	for(teamIT IT = teams.begin(); IT != teams.end(); ++IT) {
		IDTemp.push_back((*IT).first);
	}

	for (scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		IDTemp.push_back((*IT).second->getID());
	}

	for (taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		IDTemp.push_back((*IT).second->getID());
	}

	for (aitriggerIT IT = aitriggers.begin(); IT != aitriggers.end(); ++IT) {
		IDTemp.push_back((*IT).first);
	}

	sort(IDTemp.begin(), IDTemp.end());

	IDIT = find(IDTemp.begin(), IDTemp.end(), "01000000");

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

bool isFirstTrigger(string ID) {
	bool retVal = true;
	triggerIT IT = triggers.begin();
	if((*IT).second->getID() != ID) {
		retVal = false;
	}
	return retVal;
}

Tag* FindTag(string trigID) {
	for(tagIT IT = tags.begin(); IT != tags.end(); ++IT) {
		if((*IT).second->getTriggerID() == trigID) {
			return (*IT).second;
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
	for(triggerIT IT = triggers.begin(); IT != triggers.end(); ++IT) {
		if((*IT).second->getID() == trigID) {
			return IT->second->getName().toStdString();
		}
	}
	return NULL;
}

string GetTriggerIDByName(string name) {
	for(triggerIT IT = triggers.begin(); IT != triggers.end(); ++IT) {
		if((*IT).second->getName().toStdString() == name) {
			return IT->second->getID();
		}
	}
	return string("");
}

Trigger* GetTriggerByName(string name) {
	for(triggerIT IT = triggers.begin(); IT != triggers.end(); ++IT) {
		if((*IT).second->getName().toStdString() == name) {
			return IT->second;
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
	for(teamIT IT = teams.begin(); IT != teams.end(); ++IT) {
		if(IT->second->getID() == ID) {
			return IT->second->getName();
		}
	}
	return string("");
}

Trigger* FindNearestTimerTrigger(string trigID) {
	triggerIT IT = triggers.find(trigID);
	while(IT != triggers.begin()) {
		--IT;
		if(IT->second->hasActionType(27)) {
			return IT->second;
		}
	}

	IT = triggers.find(trigID);
	while(IT != triggers.end()) {
		++IT;
		if(IT->second->hasActionType(27)) {
			return IT->second;
		}
	}

	return NULL;
}

Team* GetTeamByName(string name) {
	for(teamIT IT = teams.begin(); IT != teams.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second;
		}
	}
	return NULL;
}

string GetTeamIDByName(string name) {
	for(teamIT IT = teams.begin(); IT != teams.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second->getID();
		}
	}
	return string("");
}

string GetScriptNameByID(string ID) {
	for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		if(IT->second->getID() == ID) {
			return IT->second->getName();
		}
	}
	return "";
}

string GetScriptIDByName(string name) {
	for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second->getID();
		}
	}
	return "";
}

string GetTaskforceNameByID(string ID) {
	for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		if(IT->second->getID() == ID) {
			return IT->second->getName();
		}
	}
	return "";
}

string GetTaskforceIDByName(string name) {
	for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second->getID();
		}
	}
	return "";
}

Script* GetScriptByName(string name) {
	for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second;
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
		for(waypointIT IT = waypoints.begin(); IT != waypoints.end(); ++IT) {
			stringstream ss;
			ss << (*IT);
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
		list << "Attack the nearest enemy";
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


void ClearContainers()
{
	for(triggerIT IT = triggers.begin(); IT != triggers.end(); ++IT) {
		delete (*IT).second;
	}
	triggers.clear();
	for(teamIT IT = teams.begin(); IT != teams.end(); ++IT) {
		delete (*IT).second;
	}
	teams.clear();
	for(tagIT IT = tags.begin(); IT != tags.end(); ++IT) {
		delete (*IT).second;
	}
	tags.clear();
	for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		delete (*IT).second;
	}
	scripts.clear();
	for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		delete (*IT).second;
	}
	taskforces.clear();
	aitriggers.clear();
	waypoints.clear();
}
