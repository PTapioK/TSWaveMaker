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
		writeLineToBuffer("TeamTypes", QString::number(i), IT->second->getID());
		++i;
	}
	for(teamIT IT = teams.begin(); IT != teams.end(); ++IT) {
		(*IT).second->save();
	}
	i = 0;
	deleteSectionFromBuffer("ScriptTypes");
	for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		writeLineToBuffer("ScriptTypes", QString::number(i), IT->second->getID());
		++i;
	}
	for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		(*IT).second->save();
	}
	i = 0;
	deleteSectionFromBuffer("TaskForces");
	for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		writeLineToBuffer("TaskForces", QString::number(i), IT->second->getID());
		++i;
	}
	for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		(*IT).second->save();
	}

}

void writeLineToBuffer(QString section, QString ID, QString value)
{
	currentFileData.SetValue(ID.toStdString(), value.toStdString(), "", section.toStdString());
}

void editCountableValueInBuffer(QString section, QString ID, QString value, int count)
{
	std::string rawEx = currentFileData.GetValue(ID.toStdString(), section.toStdString());
	std::string exvalue = rawEx.substr(rawEx.find(",")+1);
	std::string newVal = intToStr(count) + "," + exvalue + "," + value.toStdString();
	currentFileData.SetValue(ID.toStdString(), newVal, "", section.toStdString());
}

void readFileToBuffer() {
	currentFileData.Load(currentFilePath.toStdString());
}

void deleteLineFromBuffer(QString section, QString ID)
{
	currentFileData.DeleteKey(ID.toStdString(), section.toStdString());
}

void deleteSectionFromBuffer(QString section)
{
	currentFileData.DeleteSection(section.toStdString());
}

void parseSections()
{

	t_Section * trSec = currentFileData.GetSection("Triggers");

	if(trSec != NULL) {
		triggers.clear();
		KeyList * trigs = trSec->GetKeyList();
		for(KeyItor keyIT = trigs->begin(); keyIT < trigs->end(); ++keyIT) {
			std::string Key = keyIT->szKey;

			QStringList curLine = QString::fromStdString(currentFileData.GetString(Key, "Triggers")).split(",");

			if(curLine.size() == 8) {
				QString ID = QString::fromStdString(Key);

				QString house = curLine[0];
				QString attachID = curLine[1];
				QString name = curLine[2];
				bool isDisabled = curLine[3].toInt();
				bool isEasy = curLine[4].toInt();
				bool isMedium = curLine[5].toInt();
				bool isHard = curLine[6].toInt();
				int16_t unknown = curLine[7].toShort();

				triggers[ID] = new Trigger(ID, house, attachID, name, isDisabled, isEasy, isMedium, isHard, unknown);
			} else {
				qDebug() << "Error parsing trigger line: " + curLine.join(",");
			}
		}

	}

	t_Section * tagSec = currentFileData.GetSection("Tags");

	if (tagSec != NULL) {
		tags.clear();
		KeyList * tagsl = tagSec->GetKeyList();
		for(KeyItor keyIT = tagsl->begin(); keyIT < tagsl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;

			QStringList curLine = QString::fromStdString(currentFileData.GetString(Key, "Tags")).split(",");

			if(curLine.size() == 3) {
				QString ID = QString::fromStdString(Key);

				int32_t mode = curLine[0].toInt();
				QString name = curLine[1];
				QString triggerID = curLine[2];

				tags[name] = new Tag(ID, name, triggerID, mode);
			} else {
				qDebug() << "Error parsing tag line: " + curLine.join(",");
			}
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
			std::string curLine = currentFileData.GetString(Key, "TeamTypes");

			std::string teamID = curLine.substr(0, 8);
			Team *nTeam = findNewTeamFromFile(teamID);

			if(nTeam != NULL) {
				teams[QString::fromStdString(teamID)] = nTeam;
			}

		}
	}

	t_Section * scriptSec = currentFileData.GetSection("ScriptTypes");
	if (scriptSec != NULL) {
		scripts.clear();
		KeyList * scriptl = scriptSec->GetKeyList();
		for(KeyItor keyIT = scriptl->begin(); keyIT < scriptl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;
			std::string curLine = currentFileData.GetString(Key, "ScriptTypes");

			std::string scriptID = curLine.substr(0, 8);
			Script *nScript = findNewScriptFromFile(scriptID);

			if(nScript != NULL) {
				scripts[QString::fromStdString(scriptID)] = nScript;
			}

		}
	}

	t_Section * taskSec = currentFileData.GetSection("TaskForces");
	if (taskSec != NULL) {
		taskforces.clear();
		KeyList * taskl = taskSec->GetKeyList();
		for(KeyItor keyIT = taskl->begin(); keyIT < taskl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;
			std::string curLine = currentFileData.GetString(Key, "TaskForces");

			std::string taskforceID = curLine.substr(0, 8);
			Taskforce *nTaskforce = findNewTaskforceFromFile(taskforceID);

			if(nTaskforce != NULL) {
				taskforces[QString::fromStdString(taskforceID)] = nTaskforce;
			}
		}
	}

	t_Section * eventSec = currentFileData.GetSection("Events");
	if(eventSec != NULL) {
		KeyList * eventl = eventSec->GetKeyList();
		for(KeyItor keyIT = eventl->begin(); keyIT < eventl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;

			QStringList curLine = QString::fromStdString(currentFileData.GetString(Key, "Events")).split(",");

			QString ID = QString::fromStdString(Key);

			int32_t count = curLine[0].toInt();

			for(int i = 0; i != count; ++i) {
				int32_t eType = curLine[1 + i*3].toInt();

				int32_t unknown = curLine[2 + i*3].toShort();

				int32_t param = curLine[3 + i*3].toInt();

				triggers[ID]->addEvent(new Event(eType, param, ID, unknown));
			}

		}
	}

	t_Section * actionSec = currentFileData.GetSection("Actions");
	if (actionSec != NULL) {

		KeyList * actl = actionSec->GetKeyList();
		for(KeyItor keyIT = actl->begin(); keyIT < actl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;

			QStringList curLine = QString::fromStdString(currentFileData.GetString(Key, "Actions")).split(",");

			QString ID = QString::fromStdString(Key);

			int32_t count = curLine[0].toInt();

			std::array<QString, 6> params;

			for(int i = 0; i != count; ++i) {
				int32_t aType = curLine[1 + i*8].toInt();

				params[0] = curLine[2 + i*8];

				params[1] = curLine[3 + i*8];

				params[2] = curLine[4 + i*8];

				params[3] = curLine[5 + i*8];

				params[4] = curLine[6 + i*8];

				params[5] = curLine[7 + i*8];

				int32_t wPoint = curLine[8 + i*8].toInt();

				triggers[ID]->addAction(new Action(ID, aType, params, wPoint));
			}

		}
	}

	t_Section * aiTrigSec = currentFileData.GetSection("AITriggerTypes");
	if(aiTrigSec != NULL) {
		KeyList * aiTrigl = aiTrigSec->GetKeyList();
		for(KeyItor keyIT = aiTrigl->begin(); keyIT < aiTrigl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;

			std::string curLine = currentFileData.GetString(Key, "AITriggerTypes");

			std::string ID = Key;

			aitriggers[QString::fromStdString(ID)] = QString::fromStdString(curLine);
		}
	}

	QSettings currentMapSettings(currentFilePath, QSettings::IniFormat);

	uint16_t index = 0;
	parseBuildingTypes(currentMapSettings, index, 0, true);

	parseUnitTypesToMap(currentMapSettings, vehicles, "VehicleTypes");
	parseUnitTypesToMap(currentMapSettings, infantry, "InfantryTypes");
	parseUnitTypesToMap(currentMapSettings, aircraft, "AircraftTypes");

	parseVariablesToMap(currentMapSettings, localvariables);

	parseHouseTypes(currentMapSettings);
}

void parseRules()
{

	// Structure ID counter
	uint16_t buildingIndex = 0;

	// Tiberian Sun rules
	QSettings tsRulesData(tsRulesPath, QSettings::IniFormat);
	parseBuildingTypes(tsRulesData, buildingIndex);

	parseUnitTypesToMap(tsRulesData, vehicles, "VehicleTypes");
	parseUnitTypesToMap(tsRulesData, infantry, "InfantryTypes");
	parseUnitTypesToMap(tsRulesData, aircraft, "AircraftTypes");

	parseVariablesToMap(tsRulesData, globalvariables);

	parseHouseTypes(tsRulesData);

	// Tiberian Sun Firestorm rules
	QSettings fsRulesData(fsRulesPath, QSettings::IniFormat);
	parseBuildingTypes(fsRulesData, buildingIndex, 169);

	parseUnitTypesToMap(fsRulesData, vehicles, "VehicleTypes");
	parseUnitTypesToMap(fsRulesData, infantry, "InfantryTypes");
	parseUnitTypesToMap(fsRulesData, aircraft, "AircraftTypes");
}

Taskforce* findNewTaskforceFromFile(std::string taskforceID)
{
	t_Section * cTaskF = currentFileData.GetSection(taskforceID);
	if(cTaskF != NULL) {

		std::string name = "New Taskforce";
		int32_t group = -1;

		Taskforce *nTaskforce = new Taskforce(QString::fromStdString(taskforceID));

		KeyList * taskl = cTaskF->GetKeyList();
		for(KeyItor keyIT = taskl->begin(); keyIT < taskl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;
			std::string curLine = currentFileData.GetString(Key, taskforceID);

			std::string type = "";
			short amount = 0;

			if(Key == "Group") {
				group = currentFileData.GetInt(Key, taskforceID);
				nTaskforce->setGroup(group);
			} else if (Key == "Name") {
				name = curLine;
				nTaskforce->setName(QString::fromStdString(name));
			} else {
				std::string val = curLine;
				amount = atoi(val.substr(0, val.find(",")).c_str());

				val = val.substr(val.find(",")+1);
				type = val;

				nTaskforce->addLine(QString::fromStdString(type), amount);
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

		Script *nScript = new Script(QString::fromStdString(scriptID));

		KeyList * scriptl = cScript->GetKeyList();
		for(KeyItor keyIT = scriptl->begin(); keyIT < scriptl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;
			std::string curLine = currentFileData.GetString(Key, scriptID);

			int16_t type = 0;
			int32_t param = 0;

			if(Key == "Name") {
				name = curLine;
				nScript->setName(QString::fromStdString(name));
			} else {
				std::string val = curLine;
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
		QString tag;
		bool full = false;
		QString name;
		int group = -1;
		QString house;
		QString script;
		bool whiner = false;
		bool droppod = false;
		bool suicide = false;
		bool loadable = false;
		bool prebuild = false;
		int priority = 1;
		QString waypoint;
		bool annoyance = false;
		bool ionimmune = false;
		bool recruiter = false;
		bool reinforce = false;
		QString taskforce;
		int techlevel = 0;
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
		tag = QString::fromStdString(currentFileData.GetString("Tag", teamID));
		full = convertToBool(currentFileData.GetString("Full", teamID));
		name = QString::fromStdString(currentFileData.GetString("Name", teamID));
		group = currentFileData.GetInt("Group", teamID);
		house = QString::fromStdString(currentFileData.GetString("House", teamID));
		script = QString::fromStdString(currentFileData.GetString("Script", teamID));
		whiner = convertToBool(currentFileData.GetString("Whiner", teamID));
		droppod = convertToBool(currentFileData.GetString("Droppod", teamID));
		suicide = convertToBool(currentFileData.GetString("Suicide", teamID));
		loadable = convertToBool(currentFileData.GetString("Loadable", teamID));
		prebuild = convertToBool(currentFileData.GetString("Prebuild", teamID));
		priority = currentFileData.GetInt("Priority", teamID);
		waypoint = QString::fromStdString(currentFileData.GetString("Waypoint", teamID));
		annoyance = convertToBool(currentFileData.GetString("Annoyance", teamID));
		ionimmune = convertToBool(currentFileData.GetString("IonImmune", teamID));
		recruiter = convertToBool(currentFileData.GetString("Recruiter", teamID));
		reinforce = convertToBool(currentFileData.GetString("Reinforce", teamID));
		taskforce = QString::fromStdString(currentFileData.GetString("TaskForce", teamID));
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


		return new Team(QString::fromStdString(teamID), max, tag, full, name, group, house, script, whiner, droppod, suicide,
						loadable, prebuild, priority, waypoint, annoyance, ionimmune, recruiter,
						reinforce, taskforce, techlevel, aggressive, autocreate, guardslower,
						ontransonly, avoidthreats, looserecruit, veteranlevel, isbasedefense,
						onlytargethousenemy, transportsreturnonunload, areteammembersrecruitable);
	}

	return NULL;
}

// Finds and adds units to given container
void parseUnitTypesToMap(QSettings &rules, std::map<QString, unitContainer> &unitMap, QString type) {
	rules.beginGroup(type);
	QStringList unitList = rules.childKeys();
	rules.endGroup();

	if (!unitList.isEmpty()) {
		for(QStringList::ConstIterator keyIT = unitList.begin(); keyIT != unitList.end(); ++keyIT) {

			QString unitID = rules.value(type + "/" + *keyIT).toString();
			QString unitName = rules.value(unitID + "/name").toString();

			if(unitName != "") {
				unitContainer cont;
				cont.unitID = unitID;
				cont.name = unitName;
				cont.key = (*keyIT).toShort();

				unitMap[unitID] = cont;
			}
		}
	}
}

void parseVariablesToMap(QSettings &rules, std::map<uint16_t, variableContainer> &variableMap) {
	rules.beginGroup("VariableNames");
	QStringList variableSec = rules.childKeys();
	rules.endGroup();

	if (!variableSec.isEmpty()) {
		for(QStringList::ConstIterator keyIT = variableSec.begin(); keyIT != variableSec.end(); ++keyIT) {
			QString Key = *keyIT;

			QStringList values = rules.value("VariableNames/" + Key).toString().split(",");

			QString name = values.at(0);

			bool set = false;
			if(values.size() == 2)
				set = values.at(1).toInt();

			variableContainer cont;
			cont.set = set;
			cont.name = name;

			variableMap[Key.toShort()] = cont;
		}
	}
}

void parseBuildingTypes(QSettings &rules, uint16_t &index, int16_t keyPlus, bool useKeyInstead) {
	rules.beginGroup("BuildingTypes");
	QStringList buildSec = rules.childKeys();
	rules.endGroup();

	if (!buildSec.isEmpty()) {
		for(QStringList::ConstIterator keyIT = buildSec.begin(); keyIT != buildSec.end(); ++keyIT) {
			QString Key = *keyIT;

			QString buildingID = rules.value("BuildingTypes/" + Key).toString();
			QString name = rules.value(buildingID + "/name").toString();

			if(name != "") {
				unitContainer cont;
				cont.unitID = buildingID;
				cont.name = name;
				cont.key = Key.toShort() + keyPlus;

				if(useKeyInstead) {
					buildings[Key.toShort()] = cont;
				} else {
					buildings[index] = cont;
				}
			}

			++index;
		}
	}
}

void parseHouseTypes(QSettings &rules) {
	rules.beginGroup("Houses");
	QStringList houseSec = rules.childKeys();
	rules.endGroup();

	if (!houseSec.isEmpty()) {
		for(QStringList::ConstIterator keyIT = houseSec.begin(); keyIT != houseSec.end(); ++keyIT) {
			QString Key = *keyIT;
			QString name = rules.value("Houses/" + Key).toString();
			houses[Key.toShort()] = name;
		}
	}
}
