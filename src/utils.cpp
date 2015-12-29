#include "utils.h"


// Find First Free ID
std::string fffID()
{
	std::string nextID;
	std::stringstream ssID;

	int32_t i = 1000000;

	std::vector<std::string> IDTemp;
	std::vector<std::string>::iterator IDIT;

	if(triggers.empty() && tags.empty() && teams.empty() && scripts.empty() && taskforces.empty() && aitriggers.empty()) {
		ssID << "0" << i;
		return std::string (ssID.str().c_str());
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

	std::string a = "";
	while(1) {
		ssID.str("");
		ssID << "0" << i;
		nextID = std::string (ssID.str().c_str());

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
	nextID = std::string (ssID.str().c_str());

	return nextID;
}

std::string getValueStr(std::string line)
{
	std::string::size_type pos;
	pos = line.find("=");
	line = line.substr(pos+1);
	return line.substr(0, line.find('\n'));
}

bool isFirstTrigger(std::string ID)
{
	bool retVal = true;
	triggerIT IT = triggers.begin();
	if((*IT).second->getID() != ID) {
		retVal = false;
	}
	return retVal;
}

Tag* findTag(std::string trigID)
{
	for(tagIT IT = tags.begin(); IT != tags.end(); ++IT) {
		if((*IT).second->getTriggerID() == trigID) {
			return (*IT).second;
		}
	}
	return NULL;
}

std::string decToWaypointID(int dec)
{
	std::string retVal;
	dec=dec+1;
	while(dec != 0) {
		--dec;
		retVal = alphas[dec % 26] + retVal;
		dec /= 26;
	}
	return retVal;
}

std::string convertToSmallAlphas(int32_t dec)
{
	std::string retVal;
	dec=dec+1;
	while(dec != 0) {
		--dec;
		retVal = small_alphas[dec % 26] + retVal;
		dec /= 26;
	}
	return retVal;
}

std::string getTriggerNameByID(std::string trigID)
{
	for(triggerIT IT = triggers.begin(); IT != triggers.end(); ++IT) {
		if((*IT).second->getID() == trigID) {
			return IT->second->getName().toStdString();
		}
	}
	return NULL;
}

std::string getTriggerIDByName(std::string name)
{
	for(triggerIT IT = triggers.begin(); IT != triggers.end(); ++IT) {
		if((*IT).second->getName().toStdString() == name) {
			return IT->second->getID();
		}
	}
	return std::string ("");
}

Trigger* getTriggerByName(std::string name)
{
	for(triggerIT IT = triggers.begin(); IT != triggers.end(); ++IT) {
		if((*IT).second->getName().toStdString() == name) {
			return IT->second;
		}
	}
	return NULL;
}

int32_t waypointIDToDec(std::string wID)
{
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

bool convertToBool(std::string str)
{
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

std::string converBoolToYesNo(bool boolean)
{
	if(boolean == true) {
		return "yes";
	} else {
		return "no";
	}
}

std::string intToStr(int integer) {
	std::stringstream ss;
	ss << integer;
	return ss.str();
}

std::string getTeamNameByID(std::string ID)
{
	for(teamIT IT = teams.begin(); IT != teams.end(); ++IT) {
		if(IT->second->getID() == ID) {
			return IT->second->getName();
		}
	}
	return std::string ("");
}

Trigger* findNearestTimerTrigger(std::string trigID)
{
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

Team* getTeamByName(std::string name)
{
	for(teamIT IT = teams.begin(); IT != teams.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second;
		}
	}
	return NULL;
}

std::string getTeamIDByName(std::string name)
{
	for(teamIT IT = teams.begin(); IT != teams.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second->getID();
		}
	}
	return std::string ("");
}

std::string getScriptNameByID(std::string ID)
{
	for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		if(IT->second->getID() == ID) {
			return IT->second->getName();
		}
	}
	return "";
}

std::string getScriptIDByName(std::string name)
{
	for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second->getID();
		}
	}
	return "";
}

std::string getTaskforceNameByID(std::string ID)
{
	for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		if(IT->second->getID() == ID) {
			return IT->second->getName();
		}
	}
	return "";
}

std::string getTaskforceIDByName(std::string name)
{
	for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second->getID();
		}
	}
	return "";
}


Taskforce *getTaskforceByName(std::string name)
{
	for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second;
		}
	}
	return NULL;
}


Script* getScriptByName(std::string name)
{
	for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second;
		}
	}
	return NULL;
}


std::string getScriptNameByPosition(uint16_t pos)
{
	int i = 0;
	for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		if(i == pos) {
			return IT->second->getName();
		}
		++i;
	}
	return 0;
}

std::string getTaskforceNameByPosition(uint16_t pos)
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

QString getScriptActionMeaning(uint8_t ID)
{
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
		return "Unload transports";
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

SATargetType getScriptActionTargetType(uint8_t ID)
{
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

QStringList getScriptActionTargetStrings(SATargetType type)
{
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
			std::stringstream ss;
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
		for(std::map<uint16_t, unitContainer>::iterator IT = buildings.begin(); IT != buildings.end(); ++IT) {
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
		for(std::map<uint16_t, std::string >::iterator IT = houses.begin(); IT != houses.end(); ++IT) {
			list << (*IT).second.c_str();
		}
		break;
	case EDITABLE:
	default:
		list << "";
	}
	return list;
}

uint32_t getStringListMaxWidth(QStringList list, QFont font)
{
	if(!list.empty()) {
		std::vector <uint32_t> widths;
		QFontMetrics metr(font);
		for(QStringList::Iterator listIT = list.begin(); listIT != list.end(); ++listIT) {
			widths.push_back(metr.width(*listIT));
		}
		sort(widths.begin(), widths.end());
		return *(widths.end()-1);
	}
	return 0;
}


uint16_t getBuildingTypePosByKey(int key)
{
	for(std::map<uint16_t, unitContainer>::iterator IT = buildings.begin(); IT != buildings.end(); ++IT) {
		if((*IT).second.key == key) {
			return (*IT).first;
		}
	}
	return 0;
}

void clearContainers()
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

	buildings.clear();
	vehicles.clear();
	infantry.clear();
	aircraft.clear();

	localvariables.clear();

	waypoints.clear();

	currentFileData.Clear();
}


void loadSettings(bool ask)
{
	QString ts_rules_path = settings.value("rules/rulesPath").toString();
	QString fs_rules_path = settings.value("rules/firestrmPath").toString();

	cloneOfNaming = settings.value("cloneOfNaming").toBool();
	ascNumNaming  = settings.value("increaseNumberNaming").toBool();
	alphabetNaming = settings.value("alphabetsInOrderNaming").toBool();

	lastUsedPath = settings.value("lastUsedPath", ".").toString();

	if(ask) {
		if(ts_rules_path.isEmpty()) {
			if(QMessageBox::question(NULL, "Rules.ini path hasn't been set", "Rules.ini path has not been set. Do you want set it now?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
				ts_rules_path = getRulesPathFor("rules.ini", ts_rules_path);
			}
		}
		if(fs_rules_path.isEmpty()) {
			if(QMessageBox::question(NULL, "Firestrm.ini path hasn't been set", "Firestrm.ini path has not been set. Do you want set it now?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
				fs_rules_path = getRulesPathFor("rules.ini", fs_rules_path);
			}
		}
	}

	settings.setValue("rules/rulesPath", ts_rules_path);
	settings.setValue("rules/firestrmPath", fs_rules_path);

	tsRulesPath = ts_rules_path + "/rules.ini";
	fsRulesPath = fs_rules_path + "/firestrm.ini";

	settings.sync();
}

QString getRulesPathFor(QString fileName, QString path)
{
	QFileDialog fDG(NULL);
	fDG.setFileMode(QFileDialog::Directory);
	fDG.setOption(QFileDialog::ShowDirsOnly, true);
	return fDG.getExistingDirectory(NULL, "Select directory containing " + fileName, path);
}

std::string getNameWithNextMark(std::string name, int iter, int numIter)
{
	std::string oName = name;
	if(numIter == -1000000) numIter = iter;

	if(alphabetNaming) {
		for(int i = 0; i != 26; ++i) {
			std::stringstream ss("");
			ss << " " << alphas[i];
			if(name.find(ss.str()) != std::string ::npos) {
				name.replace(name.find(ss.str()), ss.str().length(), std::string (" ") + decToWaypointID(i + iter + 1));
				break;
			} else if(*(name.end()-1) == alphas[i]) {
				name.replace(name.length()-1, sizeof(char), decToWaypointID(i + iter + 1));
				break;
			}
		}
		for(int i = 0; i != 26; ++i) {
			std::stringstream ss("");
			ss << " " << small_alphas[i];
			if(name.find(ss.str()) != std::string ::npos) {
				name.replace(name.find(ss.str()), ss.str().length(), std::string (" ") + convertToSmallAlphas(i + iter + 1));
				break;
			} else if(*(name.end()-1) == small_alphas[i]) {
				name.replace(name.length()-1, sizeof(char), convertToSmallAlphas(i + iter + 1));
				break;
			}
		}
	}
	if(ascNumNaming) {
		int intLoc = std::string ::npos;
		for(int i = 0; i < 10; ++i) {
			intLoc = name.find(intToStr(i));
			if(intLoc != std::string ::npos) {
				std::string numStr("");
				int num = stoi(name.substr(intLoc), nullptr);
				numStr = intToStr(num);
				name.replace(intLoc, numStr.length(), intToStr(atoi(numStr.c_str()) + numIter + 1));
				break;
			}
		}
	}
	if(cloneOfNaming) {
		name = "Clone of " + name;
	}

	if(oName == name)
		return name + intToStr(iter);
	return name;
}


std::string getUnitNameByUnitID(std::string unitID)
{
	for(unitIT IT = aircraft.begin(); IT != aircraft.end(); ++IT) {
		if(IT->second.unitID == unitID) {
			return IT->second.name;
		}
	}
	for(unitIT IT = infantry.begin(); IT != infantry.end(); ++IT) {
		if(IT->second.unitID == unitID) {
			return IT->second.name;
		}
	}
	for(unitIT IT = vehicles.begin(); IT != vehicles.end(); ++IT) {
		if(IT->second.unitID == unitID) {
			return IT->second.name;
		}
	}
	return std::string ("");
}

