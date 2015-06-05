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

bool ConvertToBool(string str) {
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


Taskforce *GetTaskforceByName(string name)
{
	for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second;
		}
	}
	return NULL;
}


Script* GetScriptByName(string name) {
	for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second;
		}
	}
	return NULL;
}


string GetScriptNameByPosition(uint16_t pos) {
	int i = 0;
	for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		if(i == pos) {
			return IT->second->getName();
		}
		++i;
	}
	return 0;
}

string GetTaskforceNameByPosition(uint16_t pos)
{
	int i = 0;
	for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		if(i == pos) {
			return IT->second->getName();
		}
		++i;
	}
	return 0;
}

QString GetScriptActionMeaning(uint8_t ID) {
	switch(ID) {
	case 0:
		return "Attack a kind of target";
	case 1:
		return "Attack the waypoint";
	case 2:
		return "Go berzerk";
	case 3:
		return "Move to the waypoint";
	case 4:
		return "Move to coordinates...";
	case 5:
		return "Guard area for timer ticks...";
	case 6:
		return "Jump to line...";
	case 7:
		return "Player wins";
	case 8:
		return "Transport releases freight";
	case 9:
		return "Deploy";
	case 10:
		return "Follow friendlies";
	case 11:
		return "Execute mission";
	case 12:
		return "Set a global variable";
	case 13:
		return "Idle anim...";
	case 14:
		return "Transporter loads freight";
	case 15:
		return "Attack building at waypoint";
	case 16:
		return "Patrol to waypoint";
	case 17:
		return "Change to another script";
	case 18:
		return "Join with other Taskforce";
	case 19:
		return "Panic";
	case 20:
		return "Change the house";
	case 21:
		return "Scatter";
	case 22:
		return "Run into shroud";
	case 23:
		return "Player looses";
	case 24:
		return "Voice message";
	case 25:
		return "Play sound";
	case 26:
		return "Play movie";
	case 27:
		return "Play a song";
	case 28:
		return "Reduce tiberium";
	case 29:
		return "Begin production";
	case 30:
		return "Fire sale";
	case 31:
		return "Commit suicide";
	case 32:
		return "Ion storm...";
	case 33:
		return "Ion storm end";
	case 34:
		return "Center view on team (speed)...";
	case 35:
		return "Shroud map";
	case 36:
		return "Reveal map";
	case 37:
		return "Delete team members";
	case 38:
		return "Clear a global variable";
	case 39:
		return "Set a local variable";
	case 40:
		return "Clear a local variable";
	case 41:
		return "End panic";
	case 42:
		return "Change unit facing";
	case 43:
		return "Transport waits until fully loaded";
	case 44:
		return "Unload truck";
	case 45:
		return "Load truck";
	case 46:
		return "Attack enemy building";
	case 47:
		return "Move to enemy building";
	case 48:
		return "Scout";
	case 49:
		return "Success";
	case 50:
		return "Flash taskforce";
	case 51:
		return "Animate taskforce...";
	case 52:
		return "Talk bubble";
	case 53:
		return "Gather at enemy";
	case 54:
		return "Gather at base";
	default:
		return "Not Implemented!";
	}
}

SATargetType GetScriptActionTargetType(uint8_t ID) {
	switch(ID) {
	case 0:
		return TARGET;
	case 1:
	case 3:
		return WAYPOINT;
	case 4:
	case 5:
	case 6:
		return EDITABLE;
	case 8:
		return UNLOAD;
	case 11:
		return MISSION;
	case 12:
		return GLOBAL;
	case 13:
		return EDITABLE;
	case 15:
	case 16:
		return WAYPOINT;
	case 17:
		return SCRIPT;
	case 18:
		return TASKFORCE;
	case 20:
		return HOUSE;
	case 24:
	case 25:
	case 26:
	case 27:
	case 32:
	case 34:
		return EDITABLE;
	case 38:
		return GLOBAL;
	case 39:
	case 40:
		return LOCAL;
	case 42:
		return FACING;
	case 46:
	case 47:
		return BUILDING;
	case 51:
		return EDITABLE;
	case 52:
		return BALLOON;
	default:
		return NONE;
	}
}

QStringList GetScriptActionTargetStrings(SATargetType type) {
	QStringList list;
	switch(type) {
	case TARGET:
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
	case BUILDING:
		for(std::map<uint16_t, unitContainer>::iterator IT = buildingnames.begin(); IT != buildingnames.end(); ++IT) {
			list << (*IT).second.name.c_str();
		}
		break;
	case BALLOON:
		list << "'*'";
		list << "'?'";
		list << "'!'";
		break;
	case FACING:
		list << "North";
		list << "North-East";
		list << "East";
		list << "South-East";
		list << "South";
		list << "South-West";
		list << "West";
		list << "North-West";
		break;
	case LOCAL:
		for(std::map <uint16_t, variableContainer>::iterator IT = localvariables.begin(); IT != localvariables.end(); ++IT) {
			list << (*IT).second.name.c_str();
		}
		break;
	case GLOBAL:
		for(std::map <uint16_t, variableContainer>::iterator IT = globalvariables.begin(); IT != globalvariables.end(); ++IT) {
			list << (*IT).second.name.c_str();
		}
		break;
	case SCRIPT:
		for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
			list << (*IT).second->getName().c_str();
		}
		break;
	case TASKFORCE:
		for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
			list << (*IT).second->getName().c_str();
		}
		break;
	case HOUSE:
		for(std::map<uint16_t, string>::iterator IT = houses.begin(); IT != houses.end(); ++IT) {
			list << (*IT).second.c_str();
		}
		break;
	case EDITABLE:
	default:
		list << "";
	}
	return list;
}

uint32_t GetStringListMaxWidth(QStringList list, QFont font) {
	if(!list.empty()) {
		vector <uint32_t> widths;
		QFontMetrics metr(font);
		for(QStringList::Iterator listIT = list.begin(); listIT != list.end(); ++listIT) {
			widths.push_back(metr.width(*listIT));
		}
		sort(widths.begin(), widths.end());
		return *(widths.end()-1);
	}
	return 0;
}


uint16_t GetBuildingTypePosByKey(int key)
{
	for(std::map<uint16_t, unitContainer>::iterator IT = buildingnames.begin(); IT != buildingnames.end(); ++IT) {
		if((*IT).second.key == key) {
			return (*IT).first;
		}
	}
	return 0;
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

	buildingnames.clear();
	vehiclenames.clear();
	infantrynames.clear();
	aircraftnames.clear();

	localvariables.clear();

	waypoints.clear();
}


void LoadSettings(bool ask)
{
	string ts_rules_path = settings_data.GetString("rules_path");
	string fs_rules_path = settings_data.GetString("firestrm_path");

	cloneOfNaming = settings_data.GetBool("cloneOfNaming");
	ascNumNaming  = settings_data.GetBool("increaseNumberNaming");
	alphabetNaming = settings_data.GetBool("alphabetsInOrderNaming");

	if(ask) {
		if(ts_rules_path.empty()) {
			if(QMessageBox::question(NULL, "Rules.ini path hasn't been set", "Rules.ini path has not been set. Do you want set it now?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
				ts_rules_path = TSRulesPath(ts_rules_path);
			}
		}
		if(fs_rules_path.empty()) {
			if(QMessageBox::question(NULL, "Firestrm.ini path hasn't been set", "Firestrm.ini path has not been set. Do you want set it now?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
				fs_rules_path = FSRulesPath(fs_rules_path);
			}
		}
	}

	settings_data.SetValue("rules_path", ts_rules_path);
	settings_data.SetValue("firestrm_path", fs_rules_path);

	ts_rules = ts_rules_path + "/rules.ini";
	fs_rules = fs_rules_path + "/firestrm.ini";

	settings_data.Save();
}

string TSRulesPath(string path)
{
	QFileDialog fDG(NULL);
	fDG.setFileMode(QFileDialog::Directory);
	fDG.setOption(QFileDialog::ShowDirsOnly, true);
	return fDG.getExistingDirectory(NULL, "Select directory containing rules.ini", path.c_str()).toStdString();
}

string FSRulesPath(string path)
{
	QFileDialog fDG(NULL);
	fDG.setFileMode(QFileDialog::Directory);
	fDG.setOption(QFileDialog::ShowDirsOnly, true);
	return fDG.getExistingDirectory(NULL, "Select directory containing firestrm.ini", path.c_str()).toStdString();
}

string GetNameWithNextMark(string name, int iter)
{
	string oName = name;
	if(alphabetNaming) {
		for(int i = 0; i != 26; ++i) {
			stringstream ss("");
			ss << " " << alphas[i];
			if(name.find(ss.str()) != string::npos) {
				name.replace(name.find(ss.str()), ss.str().length(), string(" ") + DecToWaypointID(i + iter + 1));
				break;
			}
		}
	}
	if(ascNumNaming) {
		for(int i = 0; i != 99; ++i) {
			stringstream ss("");
			ss << i;
			if(name.find(ss.str()) != string::npos) {
				name.replace(name.find(ss.str()), ss.str().length(), IntToStr(i + iter + 1));
				break;
			}
		}
	}
	if(cloneOfNaming) {
		name = "Clone of " + name;
	}
	if(oName == name)
		return name + IntToStr(iter);
	return name;
}


string GetUnitNameByUnitID(string unitID)
{
	for(unitIT IT = aircraftnames.begin(); IT != aircraftnames.end(); ++IT) {
		if(IT->second.unitID == unitID) {
			return IT->second.name;
		}
	}
	for(unitIT IT = infantrynames.begin(); IT != infantrynames.end(); ++IT) {
		if(IT->second.unitID == unitID) {
			return IT->second.name;
		}
	}
	for(unitIT IT = vehiclenames.begin(); IT != vehiclenames.end(); ++IT) {
		if(IT->second.unitID == unitID) {
			return IT->second.name;
		}
	}
	return string("");
}
