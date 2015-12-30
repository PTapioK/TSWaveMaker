#include "fileoperations.h"


void saveAllToBuffer()
{
	for(triggerIT IT = triggers.begin(); IT != triggers.end(); ++IT) {
		(*IT).second->save();
	}
	for(tagIT IT = tags.begin(); IT != tags.end(); ++IT) {
		(*IT).second->save();
	}

	int i = 0;
	deleteSectionFromBuffer("TeamTypes");
	for(teamIT IT = teams.begin(); IT != teams.end(); ++IT) {
		writeLineToBuffer("TeamTypes", intToStr(i), IT->second->getID());
		++i;
	}
	for(teamIT IT = teams.begin(); IT != teams.end(); ++IT) {
		(*IT).second->save();
	}
	i = 0;
	deleteSectionFromBuffer("ScriptTypes");
	for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		writeLineToBuffer("ScriptTypes", intToStr(i), IT->second->getID());
		++i;
	}
	for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		(*IT).second->save();
	}
	i = 0;
	deleteSectionFromBuffer("TaskForces");
	for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		writeLineToBuffer("TaskForces", intToStr(i), IT->second->getID());
		++i;
	}
	for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		(*IT).second->save();
	}

}

void writeLineToBuffer(std::string section, std::string ID, std::string value)
{
	currentFileData.SetValue(ID, value, "", section);
}

void editValueInBuffer(std::string section, std::string ID, std::string value, int count)
{

	std::string rawEx = currentFileData.GetValue(ID, section);
	std::string exvalue = rawEx.substr(rawEx.find(",")+1);
	std::string newVal = intToStr(count) + "," + exvalue + "," + value;
	currentFileData.SetValue(ID, newVal, "", section);

}

void readFileToBuffer() {
	currentFileData.Load(currentFilePath);
}

void deleteLineFromBuffer(std::string section, std::string ID)
{
	currentFileData.DeleteKey(ID, section);
}

void deleteSectionFromBuffer(std::string section)
{
	currentFileData.DeleteSection(section);
}

void parseSections()
{

	t_Section * trSec = currentFileData.GetSection("Triggers");

	if(trSec != NULL) {
		triggers.clear();
		KeyList * trigs = trSec->GetKeyList();
		for(KeyItor keyIT = trigs->begin(); keyIT < trigs->end(); ++keyIT) {
			std::string Key = keyIT->szKey;

			std::string cur_line = currentFileData.GetString(Key, "Triggers");

			std::string ID = Key;

			std::string house = cur_line.substr(0, cur_line.find(","));
			cur_line = cur_line.substr(cur_line.find(",")+1);

			std::string attachID = cur_line.substr(0, cur_line.find(","));
			cur_line = cur_line.substr(cur_line.find(",")+1);

			std::string name = cur_line.substr(0, cur_line.find(","));
			cur_line = cur_line.substr(cur_line.find(",")+1);

			std::string isDisabled_s = cur_line.substr(0, cur_line.find(","));
			cur_line = cur_line.substr(cur_line.find(",")+1);
			bool isDisabled = atoi(isDisabled_s.c_str());

			std::string isEasy_s = cur_line.substr(0, cur_line.find(","));
			cur_line = cur_line.substr(cur_line.find(",")+1);
			bool isEasy = atoi(isEasy_s.c_str());

			std::string isMedium_s = cur_line.substr(0, cur_line.find(","));
			cur_line = cur_line.substr(cur_line.find(",")+1);
			bool isMedium = atoi(isMedium_s.c_str());

			std::string isHard_s = cur_line;
			bool isHard = atoi(isHard_s.c_str());

			triggers[ID] = new Trigger(ID, house, attachID, name, isDisabled, isEasy, isMedium, isHard);
		}

	}

	t_Section * tagSec = currentFileData.GetSection("Tags");

	if (tagSec != NULL) {
		tags.clear();
		KeyList * tagsl = tagSec->GetKeyList();
		for(KeyItor keyIT = tagsl->begin(); keyIT < tagsl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;

			std::string cur_line = currentFileData.GetString(Key, "Tags");

			std::string ID = Key;

			int32_t mode = atoi(cur_line.substr(0, cur_line.find(",")).c_str());
			cur_line = cur_line.substr(cur_line.find(",")+1);

			std::string name = cur_line.substr(0, cur_line.find(","));
			cur_line = cur_line.substr(cur_line.find(",")+1);

			std::string triggerID = cur_line;

			tags[name] = new Tag(ID, name, triggerID, mode);
		}
	}

	t_Section * wpnSec = currentFileData.GetSection("Waypoints");

	if (wpnSec != NULL) {
		waypoints.clear();
		KeyList * wpnl = wpnSec->GetKeyList();
		for(KeyItor keyIT = wpnl->begin(); keyIT < wpnl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;

			int32_t waypoint = atoi(Key.c_str());
			waypoints.push_back(waypoint);
		}

	}

	t_Section * teamSec = currentFileData.GetSection("TeamTypes");

	if (teamSec != NULL) {
		teams.clear();
		KeyList * teaml = teamSec->GetKeyList();
		for(KeyItor keyIT = teaml->begin(); keyIT < teaml->end(); ++keyIT) {
			std::string Key = keyIT->szKey;
			std::string cur_line = currentFileData.GetString(Key, "TeamTypes");

			std::string teamID = cur_line.substr(0, 8);
			Team *nTeam = findNewTeamFromFile(teamID);

			if(nTeam != NULL) {
				teams[teamID] = nTeam;
			}

		}
	}

	t_Section * scriptSec = currentFileData.GetSection("ScriptTypes");
	if (scriptSec != NULL) {
		scripts.clear();
		KeyList * scriptl = scriptSec->GetKeyList();
		for(KeyItor keyIT = scriptl->begin(); keyIT < scriptl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;
			std::string cur_line = currentFileData.GetString(Key, "ScriptTypes");

			std::string scriptID = cur_line.substr(0, 8);
			Script *nScript = findNewScriptFromFile(scriptID);

			if(nScript != NULL) {
				scripts[scriptID] = nScript;
			}

		}
	}

	t_Section * taskSec = currentFileData.GetSection("TaskForces");
	if (taskSec != NULL) {
		taskforces.clear();
		KeyList * taskl = taskSec->GetKeyList();
		for(KeyItor keyIT = taskl->begin(); keyIT < taskl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;
			std::string cur_line = currentFileData.GetString(Key, "TaskForces");

			std::string taskforceID = cur_line.substr(0, 8);
			Taskforce *nTaskforce = findNewTaskforceFromFile(taskforceID);

			if(nTaskforce != NULL) {
				taskforces[taskforceID] = nTaskforce;
			}
		}
	}

	t_Section * eventSec = currentFileData.GetSection("Events");
	if(eventSec != NULL) {
		KeyList * eventl = eventSec->GetKeyList();
		for(KeyItor keyIT = eventl->begin(); keyIT < eventl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;

			std::string cur_line = currentFileData.GetString(Key, "Events");

			std::string ID = Key;

			int32_t count = atoi(cur_line.substr(0, cur_line.find(",")).c_str());
			cur_line = cur_line.substr(cur_line.find(",")+1);

			for(int i = 0; i != count; ++i) {
				int32_t eType = atoi(cur_line.substr(0, cur_line.find(",")).c_str());
				cur_line = cur_line.substr(cur_line.find(",")+1);

				//int32_t nullparam = atoi(cur_line.substr(0, cur_line.find(",")).c_str());
				cur_line = cur_line.substr(cur_line.find(",")+1);

				int32_t param = 0;
				if(i != count-1) {
					param = atoi(cur_line.substr(0, cur_line.find(",")).c_str());
					cur_line = cur_line.substr(cur_line.find(",")+1);
				} else {
					param = atoi(cur_line.c_str());
				}

				triggers[ID]->addEvent(new Event(eType, param, ID));
			}

		}
	}

	t_Section * actionSec = currentFileData.GetSection("Actions");
	if (actionSec != NULL) {

		KeyList * actl = actionSec->GetKeyList();
		for(KeyItor keyIT = actl->begin(); keyIT < actl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;

			std::string cur_line = currentFileData.GetString(Key, "Actions");

			std::string ID = Key;

			int32_t count = atoi(cur_line.substr(0, cur_line.find(",")).c_str());
			cur_line = cur_line.substr(cur_line.find(",")+1);

			std::array<std::string, 6> params;

			for(int i = 0; i != count; ++i) {
				int32_t aType = atoi(cur_line.substr(0, cur_line.find(",")).c_str());
				cur_line = cur_line.substr(cur_line.find(",")+1);

				params[0] = cur_line.substr(0, cur_line.find(","));
				cur_line = cur_line.substr(cur_line.find(",")+1);

				params[1] = cur_line.substr(0, cur_line.find(","));
				cur_line = cur_line.substr(cur_line.find(",")+1);

				params[2] = cur_line.substr(0, cur_line.find(","));
				cur_line = cur_line.substr(cur_line.find(",")+1);

				params[3] = cur_line.substr(0, cur_line.find(","));
				cur_line = cur_line.substr(cur_line.find(",")+1);

				params[4] = cur_line.substr(0, cur_line.find(","));
				cur_line = cur_line.substr(cur_line.find(",")+1);

				params[5] = cur_line.substr(0, cur_line.find(","));
				cur_line = cur_line.substr(cur_line.find(",")+1);

				int32_t wPoint = 0;

				if(i != count-1) {
					wPoint = waypointIDToDec(cur_line.substr(0, cur_line.find(",")).c_str());
					cur_line = cur_line.substr(cur_line.find(",")+1);
				} else {
					wPoint = waypointIDToDec(cur_line.c_str());
				}

				triggers[ID]->addAction(new Action(ID, aType, params, wPoint));
			}

		}
	}

	t_Section * aiTrigSec = currentFileData.GetSection("AITriggerTypes");
	if(aiTrigSec != NULL) {
		KeyList * aiTrigl = aiTrigSec->GetKeyList();
		for(KeyItor keyIT = aiTrigl->begin(); keyIT < aiTrigl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;

			std::string cur_line = currentFileData.GetString(Key, "Actions");

			std::string ID = Key;

			aitriggers[ID] = cur_line;
		}
	}

	// Rules inside map
	t_Section * buildSec = currentFileData.GetSection("BuildingTypes");

	if (buildSec != NULL) {
		KeyList * buildl = buildSec->GetKeyList();
		for(KeyItor keyIT = buildl->begin(); keyIT < buildl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;

			std::string buildingSec = currentFileData.GetString(Key, "BuildingTypes");
			std::string name = getUnitNameFromFile(buildingSec, &currentFileData);

			if(name != "") {
				unitContainer cont;
				cont.unitID = buildingSec;
				cont.name = name;
				cont.key = atoi(Key.c_str());

				buildings[atoi(Key.c_str())] = cont;
			}
		}
	}

	t_Section * vehSec = currentFileData.GetSection("VehicleTypes");


	if (vehSec != NULL) {
		KeyList * vehl = vehSec->GetKeyList();
		for(KeyItor keyIT = vehl->begin(); keyIT < vehl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;

			std::string vehicleID = currentFileData.GetString(Key, "VehicleTypes");
			std::string name = getUnitNameFromFile(vehicleID, &currentFileData);

			if(name != "") {
				unitContainer cont;
				cont.unitID = vehicleID;
				cont.name = name;
				cont.key = atoi(Key.c_str());

				vehicles[vehicleID] = cont;
			}
		}
	}

	t_Section * infSec = currentFileData.GetSection("InfantryTypes");

	if (infSec != NULL) {
		KeyList * infl = infSec->GetKeyList();
		for(KeyItor keyIT = infl->begin(); keyIT < infl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;

			std::string infID = currentFileData.GetString(Key, "InfantryTypes");
			std::string name = getUnitNameFromFile(infID, &currentFileData);

			if(name != "") {
				unitContainer cont;
				cont.unitID = infID;
				cont.name = name;

				infantry[infID] = cont;
			}
		}
	}

	t_Section * airSec = currentFileData.GetSection("AircraftTypes");

	if (airSec != NULL) {
		KeyList * airl = airSec->GetKeyList();
		for(KeyItor keyIT = airl->begin(); keyIT < airl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;

			std::string airID = currentFileData.GetString(Key, "AircraftTypes");
			std::string name = getUnitNameFromFile(airID, &currentFileData);

			if(name != "") {
				unitContainer cont;
				cont.unitID = airID;
				cont.name = name;

				aircraft[airID] = cont;
			}
		}
	}

	t_Section * localSec = currentFileData.GetSection("VariableNames");

	if (localSec != NULL) {
		KeyList * locall = localSec->GetKeyList();
		for(KeyItor keyIT = locall->begin(); keyIT < locall->end(); ++keyIT) {
			std::string Key = keyIT->szKey;

			std::string localstr = currentFileData.GetString(Key, "VariableNames");

			std::string name = localstr.substr(0, localstr.find(","));
			localstr = localstr.substr(localstr.find(",")+1);

			bool set = atoi(localstr.c_str());

			variableContainer cont;
			cont.set = set;
			cont.name = name;

			localvariables[atoi(Key.c_str())] = cont;
		}
	}

	t_Section * houseSec = currentFileData.GetSection("Houses");

	if (houseSec != NULL) {
		KeyList * housel = houseSec->GetKeyList();
		for(KeyItor keyIT = housel->begin(); keyIT < housel->end(); ++keyIT) {
			std::string Key = keyIT->szKey;

			std::string housename = currentFileData.GetString(Key, "Houses");

			houses[atoi(Key.c_str())] = housename;
		}
	}

	for(unitIT IT = aircraft.begin(); IT != aircraft.end(); ++IT) {
		t_Section * curSec = currentFileData.GetSection(IT->first);
		if(curSec != NULL) {
			std::string name = currentFileData.GetString("Name", IT->first);
			if(name != "")
				IT->second.name = name;
		}
	}
	for(unitIT IT = infantry.begin(); IT != infantry.end(); ++IT) {
		t_Section * curSec = currentFileData.GetSection(IT->first);
		if(curSec != NULL) {
			std::string name = currentFileData.GetString("Name", IT->first);
			if(name != "")
				IT->second.name = name;
		}
	}
	for(unitIT IT = vehicles.begin(); IT != vehicles.end(); ++IT) {
		t_Section * curSec = currentFileData.GetSection(IT->first);
		if(curSec != NULL) {
			std::string name = currentFileData.GetString("Name", IT->first);
			if(name != "")
				IT->second.name = name;
		}
	}

}

Taskforce* findNewTaskforceFromFile(std::string taskforceID)
{

	t_Section * cTaskF = currentFileData.GetSection(taskforceID);
	if(cTaskF != NULL) {

		std::string name = "New Taskforce";
		int32_t group = -1;

		Taskforce *nTaskforce = new Taskforce(taskforceID);

		KeyList * taskl = cTaskF->GetKeyList();
		for(KeyItor keyIT = taskl->begin(); keyIT < taskl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;
			std::string cur_line = currentFileData.GetString(Key, taskforceID);

			std::string type = "";
			short amount = 0;

			if(Key == "Group") {
				group = currentFileData.GetInt(Key, taskforceID);
				nTaskforce->setGroup(group);
			} else if (Key == "Name") {
				name = cur_line;
				nTaskforce->setName(name);
			} else {
				std::string val = getValueStr(cur_line);
				amount = atoi(val.substr(0, val.find(",")).c_str());

				val = val.substr(val.find(",")+1);
				type = val;

				nTaskforce->addLine(type, amount);
			}
		}
		return nTaskforce;
	}

	return NULL;
}

Script *findNewScriptFromFile(std::string scriptID)
{

	t_Section * cScript = currentFileData.GetSection(scriptID);

	if(cScript != NULL) {

		std::string name = "New Script";

		Script *nScript = new Script(scriptID);

		KeyList * scriptl = cScript->GetKeyList();
		for(KeyItor keyIT = scriptl->begin(); keyIT < scriptl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;
			std::string cur_line = currentFileData.GetString(Key, scriptID);

			short type = 0;
			int param = 0;

			if(Key == "Name") {
				name = cur_line;
				nScript->setName(name);
			} else {

				std::string val = cur_line;
				type = atoi(val.substr(0, val.find(",")).c_str());

				val = val.substr(val.find(",")+1);
				param = atoi(val.c_str());

				nScript->addLine(type, param);
			}
		}
		return nScript;
	}

	return NULL;
}

Team *findNewTeamFromFile(std::string teamID)
{
	t_Section * cTeam = currentFileData.GetSection(teamID);

	if(cTeam != NULL) {
		int max = 0;
		std::string tag;
		bool full = false;
		std::string name;
		int group = -1;
		std::string house;
		std::string script;
		bool whiner = false;
		bool droppod = false;
		bool suicide = false;
		bool loadable = false;
		bool prebuild = false;
		int priority = 1;
		std::string waypoint;
		bool annoyance = false;
		bool ionimmune = false;
		bool recruiter = false;
		bool reinforce = false;
		std::string taskforce;
		int techlevel;
		bool aggressive = false;
		bool autocreate = false;
		bool guardslower = false;
		bool ontransonly = false;
		bool avoidthreats = false;
		bool looserecruit = false;
		int veteranlevel = 1;
		bool isbasedefense = false;
		bool onlytargethousenemy = false;
		bool transportsreturnonunload = false;
		bool areteammembersrecruitable = true;

		max = currentFileData.GetInt("Max", teamID);
		tag = currentFileData.GetString("Tag", teamID);
		full = convertToBool(currentFileData.GetString("Full", teamID));
		name = currentFileData.GetString("Name", teamID);
		group = currentFileData.GetInt("Group", teamID);
		house = currentFileData.GetString("House", teamID);
		script = currentFileData.GetString("Script", teamID);
		whiner = convertToBool(currentFileData.GetString("Whiner", teamID));
		droppod = convertToBool(currentFileData.GetString("Droppod", teamID));
		suicide = convertToBool(currentFileData.GetString("Suicide", teamID));
		loadable = convertToBool(currentFileData.GetString("Loadable", teamID));
		prebuild = convertToBool(currentFileData.GetString("Prebuild", teamID));
		priority = currentFileData.GetInt("Priority", teamID);
		waypoint = currentFileData.GetString("Waypoint", teamID);
		annoyance = convertToBool(currentFileData.GetString("Annoyance", teamID));
		ionimmune = convertToBool(currentFileData.GetString("IonImmune", teamID));
		recruiter = convertToBool(currentFileData.GetString("Recruiter", teamID));
		reinforce = convertToBool(currentFileData.GetString("Reinforce", teamID));
		taskforce = currentFileData.GetString("TaskForce", teamID);
		techlevel = currentFileData.GetInt("TechLevel", teamID);
		aggressive = convertToBool(currentFileData.GetString("Aggressive", teamID));
		autocreate = convertToBool(currentFileData.GetString("Autocreate", teamID));
		guardslower = convertToBool(currentFileData.GetString("GuardSlower", teamID));
		ontransonly = convertToBool(currentFileData.GetString("OnTransOnly", teamID));
		avoidthreats = convertToBool(currentFileData.GetString("AvoidThreats", teamID));
		looserecruit = convertToBool(currentFileData.GetString("LooseRecruit", teamID));
		veteranlevel = currentFileData.GetInt("VeteranLevel", teamID);
		isbasedefense = convertToBool(currentFileData.GetString("IsBaseDefense", teamID));
		onlytargethousenemy = convertToBool(currentFileData.GetString("OnlyTargetHouseEnemy", teamID));
		transportsreturnonunload = convertToBool(currentFileData.GetString("TransportsReturnOnUnload", teamID));
		areteammembersrecruitable = convertToBool(currentFileData.GetString("AreTeamMembersRecruitable", teamID));


		return new Team(teamID, max, tag, full, name, group, house, script, whiner, droppod, suicide,
						loadable, prebuild, priority, waypoint, annoyance, ionimmune, recruiter,
						reinforce, taskforce, techlevel, aggressive, autocreate, guardslower,
						ontransonly, avoidthreats, looserecruit, veteranlevel, isbasedefense,
						onlytargethousenemy, transportsreturnonunload, areteammembersrecruitable);
	}

	return NULL;
}



void parseRules()
{

	// Structure ID counter
	uint16_t i = 0;

	// Tiberian Sun rules
	CDataFile ts_rules_data(tsRulesPath);
	{
		t_Section * buildSec = ts_rules_data.GetSection("BuildingTypes");

		if (buildSec != NULL) {
			KeyList * buildl = buildSec->GetKeyList();
			for(KeyItor keyIT = buildl->begin(); keyIT < buildl->end(); ++keyIT) {
				std::string Key = keyIT->szKey;

				std::string buildingID = ts_rules_data.GetString(Key, "BuildingTypes");
				std::string name = getUnitNameFromFile(buildingID, &ts_rules_data);

				if(name != "") {
					unitContainer cont;
					cont.unitID = buildingID;
					cont.name = name;
					cont.key = atoi(Key.c_str());

					buildings[i] = cont;
				}

				++i;
			}
		}

		t_Section * vehSec = ts_rules_data.GetSection("VehicleTypes");

		if (vehSec != NULL) {
			KeyList * vehl = vehSec->GetKeyList();
			for(KeyItor keyIT = vehl->begin(); keyIT < vehl->end(); ++keyIT) {
				std::string Key = keyIT->szKey;

				std::string vehicleID = ts_rules_data.GetString(Key, "VehicleTypes");
				std::string name = getUnitNameFromFile(vehicleID, &ts_rules_data);

				if(name != "") {
					unitContainer cont;
					cont.unitID = vehicleID;
					cont.name = name;

					vehicles[vehicleID] = cont;
				}
			}
		}

		t_Section * infSec = ts_rules_data.GetSection("InfantryTypes");

		if (infSec != NULL) {
			KeyList * infl = infSec->GetKeyList();
			for(KeyItor keyIT = infl->begin(); keyIT < infl->end(); ++keyIT) {
				std::string Key = keyIT->szKey;

				std::string infID = ts_rules_data.GetString(Key, "InfantryTypes");
				std::string name = getUnitNameFromFile(infID, &ts_rules_data);
				if(name != "") {
					unitContainer cont;
					cont.unitID = infID;
					cont.name = name;

					infantry[infID] = cont;
				}
			}
		}

		t_Section * airSec = ts_rules_data.GetSection("AircraftTypes");

		if (airSec != NULL) {
			KeyList * airl = airSec->GetKeyList();
			for(KeyItor keyIT = airl->begin(); keyIT < airl->end(); ++keyIT) {
				std::string Key = keyIT->szKey;

				std::string airID = ts_rules_data.GetString(Key, "AircraftTypes");
				std::string name = getUnitNameFromFile(airID, &ts_rules_data);

				if(name != "") {
					unitContainer cont;
					cont.unitID = airID;
					cont.name = name;

					aircraft[airID] = cont;
				}
			}
		}

		t_Section * globalSec = ts_rules_data.GetSection("VariableNames");

		if (globalSec != NULL) {
			KeyList * globall = globalSec->GetKeyList();
			for(KeyItor keyIT = globall->begin(); keyIT < globall->end(); ++keyIT) {
				std::string Key = keyIT->szKey;

				std::string globalstr = ts_rules_data.GetString(Key, "VariableNames");

				std::string name = globalstr.substr(0, globalstr.find(","));
				globalstr = globalstr.substr(globalstr.find(",")+1);

				bool set = atoi(globalstr.c_str());

				variableContainer cont;
				cont.set = set;
				cont.name = name;

				globalvariables[atoi(Key.c_str())] = cont;
			}
		}

		t_Section * houseSec = ts_rules_data.GetSection("Houses");

		if (houseSec != NULL) {
			KeyList * housel = houseSec->GetKeyList();
			for(KeyItor keyIT = housel->begin(); keyIT < housel->end(); ++keyIT) {
				std::string Key = keyIT->szKey;

				std::string housename = ts_rules_data.GetString(Key, "Houses");

				houses[atoi(Key.c_str())] = housename;
			}
		}

	}

	ts_rules_data.Clear();
	ts_rules_data.~CDataFile();

	// Tiberian Sun Firestorm rules
	CDataFile fs_rules_data(fsRulesPath);
	{
		t_Section * buildSec = fs_rules_data.GetSection("BuildingTypes");

		if (buildSec != NULL) {
			KeyList * buildl = buildSec->GetKeyList();
			for(KeyItor keyIT = buildl->begin(); keyIT < buildl->end(); ++keyIT) {
				std::string Key = keyIT->szKey;

				std::string buildingSec = fs_rules_data.GetString(Key, "BuildingTypes");
				std::string name = getUnitNameFromFile(buildingSec, &fs_rules_data);

				if(name != "") {
					unitContainer cont;
					cont.unitID = buildingSec;
					cont.name = name;
					cont.key = atoi(Key.c_str()) + 169;

					buildings[i] = cont;
				}
				++i;
			}
		}


		t_Section * vehSec = fs_rules_data.GetSection("VehicleTypes");

		if (vehSec != NULL) {
			KeyList * vehl = vehSec->GetKeyList();
			for(KeyItor keyIT = vehl->begin(); keyIT < vehl->end(); ++keyIT) {
				std::string Key = keyIT->szKey;

				std::string vehicleID = fs_rules_data.GetString(Key, "VehicleTypes");
				std::string name = getUnitNameFromFile(vehicleID, &fs_rules_data);

				if(name != "") {
					unitContainer cont;
					cont.unitID = vehicleID;
					cont.name = name;

					vehicles[vehicleID] = cont;
				}
			}
		}

		t_Section * infSec = fs_rules_data.GetSection("InfantryTypes");

		if (infSec != NULL) {
			KeyList * infl = infSec->GetKeyList();
			for(KeyItor keyIT = infl->begin(); keyIT < infl->end(); ++keyIT) {
				std::string Key = keyIT->szKey;

				std::string infID = fs_rules_data.GetString(Key, "InfantryTypes");
				std::string name = getUnitNameFromFile(infID, &fs_rules_data);

				if(name != "") {
					unitContainer cont;
					cont.unitID = infID;
					cont.name = name;

					infantry[infID] = cont;
				}
			}
		}

		t_Section * airSec = fs_rules_data.GetSection("AircraftTypes");

		if (airSec != NULL) {
			KeyList * airl = airSec->GetKeyList();
			for(KeyItor keyIT = airl->begin(); keyIT < airl->end(); ++keyIT) {
				std::string Key = keyIT->szKey;

				std::string airID = fs_rules_data.GetString(Key, "AircraftTypes");
				std::string name = getUnitNameFromFile(airID, &fs_rules_data);
				if(name != "") {
					unitContainer cont;
					cont.unitID = airID;
					cont.name = name;

					aircraft[airID] = cont;
				}
			}
		}

		fs_rules_data.Clear();
		fs_rules_data.~CDataFile();
	}
}


std::string getUnitNameFromFile(std::string unitID, CDataFile *file)
{
	t_Section * cUnit = file->GetSection(unitID);
	if(cUnit != NULL) {
		return file->GetString("Name", unitID);
	}

	return std::string("");
}
