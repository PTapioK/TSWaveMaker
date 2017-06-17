#include "filehandler.h"
#include "settings.h"

FileHandler::FileHandler()
{
	fileData.m_Flags |= AUTOCREATE_KEYS;
	fileData.m_Flags |= AUTOCREATE_SECTIONS;
}

FileHandler::FileHandler(QString mapFilePath)
{
	fileData.m_Flags |= AUTOCREATE_KEYS;
	fileData.m_Flags |= AUTOCREATE_SECTIONS;
	filePath = mapFilePath;
}

void FileHandler::load(QString mapFilePath)
{
	filePath = mapFilePath;
	fileData.SetFileName(mapFilePath.toStdString());
	readToBuffer();
	parseSections();
}

void FileHandler::save(QString as)
{
	if(!as.isEmpty()) {
		filePath = as;
		fileData.SetFileName(as.toStdString());
	}
	saveToBuffer();
	fileData.Save();
}

void FileHandler::saveToBuffer()
{
	for(auto IT = triggers.begin(); IT != triggers.end(); ++IT) {
		(*IT).second->save();
	}
	for(auto IT = tags.begin(); IT != tags.end(); ++IT) {
		(*IT).second->save();
	}

	int i = 0;
	deleteSectionFromBuffer("TeamTypes");
	for(auto IT = teams.begin(); IT != teams.end(); ++IT) {
		saveLineToBuffer("TeamTypes", QString::number(i), IT->second->getID());
		++i;
	}
	for(auto IT = teams.begin(); IT != teams.end(); ++IT) {
		(*IT).second->save();
	}
	i = 0;
	deleteSectionFromBuffer("ScriptTypes");
	for(auto IT = scripts.begin(); IT != scripts.end(); ++IT) {
		saveLineToBuffer("ScriptTypes", QString::number(i), IT->second->getID());
		++i;
	}
	for(auto IT = scripts.begin(); IT != scripts.end(); ++IT) {
		(*IT).second->save();
	}
	i = 0;
	deleteSectionFromBuffer("TaskForces");
	for(auto IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		saveLineToBuffer("TaskForces", QString::number(i), IT->second->getID());
		++i;
	}
	for(auto IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		(*IT).second->save();
	}

	deleteLineFromBuffer("Basic", "AllyBySpawnDefault");
	deleteSectionFromBuffer(QString("AllyBySpawnLocation") + QString::number(alliesID));
	allies.save();
}

void FileHandler::saveLineToBuffer(QString section, QString ID, QString value)
{
	fileData.SetValue(ID.toStdString(), value.toStdString(), "", section.toStdString());
}

void FileHandler::editCountableValueInBuffer(QString section, QString ID, QString value, int count)
{
	std::string rawEx = fileData.GetValue(ID.toStdString(), section.toStdString());
	std::string exVal = rawEx.substr(rawEx.find(",")+1);
	std::string newVal = intToStr(count) + "," + exVal + "," + value.toStdString();
	fileData.SetValue(ID.toStdString(), newVal, "", section.toStdString());
}

void FileHandler::readToBuffer() {
	fileData.Load(filePath.toStdString());
}

void FileHandler::deleteLineFromBuffer(QString section, QString ID)
{
	fileData.DeleteKey(ID.toStdString(), section.toStdString());
}

void FileHandler::deleteSectionFromBuffer(QString section)
{
	fileData.DeleteSection(section.toStdString());
}

void FileHandler::parseSections()
{

	t_Section * trSec = fileData.GetSection("Triggers");
	if(trSec != NULL) {
		triggers.clear();
		KeyList * trigs = trSec->GetKeyList();
		for(KeyItor keyIT = trigs->begin(); keyIT < trigs->end(); ++keyIT) {
			std::string Key = keyIT->szKey;

			QStringList curLine = QString::fromStdString(fileData.GetString(Key, "Triggers")).split(",");

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

	t_Section * tagSec = fileData.GetSection("Tags");
	if (tagSec != NULL) {
		tags.clear();
		KeyList * tagsl = tagSec->GetKeyList();
		for(KeyItor keyIT = tagsl->begin(); keyIT < tagsl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;

			QStringList curLine = QString::fromStdString(fileData.GetString(Key, "Tags")).split(",");

			if(curLine.size() == 3) {
				QString ID = QString::fromStdString(Key);

				int16_t mode = curLine[0].toShort();
				QString name = curLine[1];
				QString triggerID = curLine[2];

				tags[name] = new Tag(ID, name, triggerID, mode);
			} else {
				qDebug() << "Error parsing tag line: " + curLine.join(",");
			}
		}
	}

	t_Section * wpnSec = fileData.GetSection("Waypoints");
	if (wpnSec != NULL) {
		waypoints.clear();
		KeyList * wpnl = wpnSec->GetKeyList();
		for(KeyItor keyIT = wpnl->begin(); keyIT < wpnl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;
			int32_t waypoint = atoi(Key.c_str());
			waypoints.push_back(waypoint);
		}

	}

	t_Section * teamSec = fileData.GetSection("TeamTypes");
	if (teamSec != NULL) {
		teams.clear();
		KeyList * teaml = teamSec->GetKeyList();
		for(KeyItor keyIT = teaml->begin(); keyIT < teaml->end(); ++keyIT) {
			std::string Key = keyIT->szKey;
			std::string curLine = fileData.GetString(Key, "TeamTypes");

			std::string teamID = curLine.substr(0, 8);
			Team *nTeam = getTeam(teamID);

			if(nTeam != NULL) {
				teams[QString::fromStdString(teamID)] = nTeam;
			}

		}
	}

	t_Section * scriptSec = fileData.GetSection("ScriptTypes");
	if (scriptSec != NULL) {
		scripts.clear();
		KeyList * scriptl = scriptSec->GetKeyList();
		for(KeyItor keyIT = scriptl->begin(); keyIT < scriptl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;
			std::string curLine = fileData.GetString(Key, "ScriptTypes");

			std::string scriptID = curLine.substr(0, 8);
			Script *nScript = getScript(scriptID);

			if(nScript != NULL) {
				scripts[QString::fromStdString(scriptID)] = nScript;
			}

		}
	}

	t_Section * taskSec = fileData.GetSection("TaskForces");
	if (taskSec != NULL) {
		taskforces.clear();
		KeyList * taskl = taskSec->GetKeyList();
		for(KeyItor keyIT = taskl->begin(); keyIT < taskl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;
			std::string curLine = fileData.GetString(Key, "TaskForces");

			std::string taskforceID = curLine.substr(0, 8);
			Taskforce *nTaskforce = getTaskforce(taskforceID);

			if(nTaskforce != NULL) {
				taskforces[QString::fromStdString(taskforceID)] = nTaskforce;
			}
		}
	}

	t_Section * eventSec = fileData.GetSection("Events");
	if(eventSec != NULL) {
		KeyList * eventl = eventSec->GetKeyList();
		for(KeyItor keyIT = eventl->begin(); keyIT < eventl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;

			QStringList curLine = QString::fromStdString(fileData.GetString(Key, "Events")).split(",");
			QString ID = QString::fromStdString(Key);
			int32_t count = curLine[0].toInt();

			for(int i = 0; i != count; ++i) {
				int32_t eType = curLine[1 + i*3].toInt();
				int16_t unknown = curLine[2 + i*3].toShort();
				int32_t param = curLine[3 + i*3].toInt();

				triggers[ID]->addEvent(new Event(eType, param, ID, unknown));
			}

		}
	}

	t_Section * actionSec = fileData.GetSection("Actions");
	if (actionSec != NULL) {

		KeyList * actl = actionSec->GetKeyList();
		for(KeyItor keyIT = actl->begin(); keyIT < actl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;

			QStringList curLine = QString::fromStdString(fileData.GetString(Key, "Actions")).split(",");
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

				QString wPoint = curLine[8 + i*8];

				triggers[ID]->addAction(new Action(ID, aType, params, wPoint));
			}

		}
	}

	t_Section * aiTrigSec = fileData.GetSection("AITriggerTypes");
	if(aiTrigSec != NULL) {
		KeyList * aiTrigl = aiTrigSec->GetKeyList();
		for(KeyItor keyIT = aiTrigl->begin(); keyIT < aiTrigl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;
			std::string curLine = fileData.GetString(Key, "AITriggerTypes");
			std::string ID = Key;

			aitriggers[QString::fromStdString(ID)] = QString::fromStdString(curLine);
		}
	}

	QSettings currentMapSettings(filePath, QSettings::IniFormat);

	// BuildingTypes list should not be sorted...
	t_Section * buildSec = fileData.GetSection("BuildingTypes");

	if (buildSec != NULL) {
		KeyList * buildl = buildSec->GetKeyList();
		for(KeyItor keyIT = buildl->begin(); keyIT < buildl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;

			std::string buildingID = fileData.GetString(Key, "BuildingTypes");
			std::string name = fileData.GetString("Name", buildingID);

			if(name != "") {
				unitContainer cont;
				cont.unitID = QString::fromStdString(buildingID);
				cont.name = QString::fromStdString(name);
				cont.key = atoi(Key.c_str());

				buildings[atoi(Key.c_str())] = cont;
			}
		}
	}

	alliesID = fileData.GetInt("AllyBySpawnDefault", "Basic");
	if (alliesID != NULL) {
		std::stringstream ss;
		ss << "AllyBySpawnLocation" << alliesID;
		std::string secStr = ss.str();

		t_Section * allySec = fileData.GetSection(secStr);
		if (allySec != NULL) {
			KeyList * allyl = allySec->GetKeyList();
			for(KeyItor keyIT = allyl->begin(); keyIT < allyl->end(); ++keyIT) {
				std::string Key = keyIT->szKey;

				if (Key != "Description") {
					QStringList spawnsInTeam = QString::fromStdString(fileData.GetString(Key, secStr)).split(",");

					for (auto IT = spawnsInTeam.begin(); IT != spawnsInTeam.end(); ++IT) {
						allies.addPlayerToTeam((*IT).toInt(), QString::fromStdString(Key));
					}
				} else {
					std::string description = fileData.GetString("Description", secStr);
					allies.setDescription(QString::fromStdString(description));
				}
			}

		}
	}

	parseUnitTypes(currentMapSettings, vehicles, "VehicleTypes");
	parseUnitTypes(currentMapSettings, infantry, "InfantryTypes");
	parseUnitTypes(currentMapSettings, aircraft, "AircraftTypes");

	parseVariables(currentMapSettings, localvariables);

	parseHouseTypes(currentMapSettings);
	parseTutorial(currentMapSettings);
}

void FileHandler::parseRules()
{

	// Structure ID counter
	uint16_t buildingIndex = 0;

	// Tiberian Sun rules
	// BuildingTypes list should not be sorted...
	CDataFile tsRulesCData(Settings::tsRulesPath.toStdString());
	{
		t_Section * buildSec = tsRulesCData.GetSection("BuildingTypes");

		if (buildSec != NULL) {
			KeyList * buildl = buildSec->GetKeyList();
			for(KeyItor keyIT = buildl->begin(); keyIT < buildl->end(); ++keyIT) {
				std::string Key = keyIT->szKey;

				std::string buildingID = tsRulesCData.GetString(Key, "BuildingTypes");
				std::string name = tsRulesCData.GetString("Name", buildingID);

				if(name != "") {
					unitContainer cont;
					cont.unitID = QString::fromStdString(buildingID);
					cont.name = QString::fromStdString(name);
					cont.key = atoi(Key.c_str());

					buildings[buildingIndex] = cont;
				}

				++buildingIndex;
			}
		}
	}

	QSettings tsRulesData(Settings::tsRulesPath, QSettings::IniFormat);
	parseUnitTypes(tsRulesData, vehicles, "VehicleTypes");
	parseUnitTypes(tsRulesData, infantry, "InfantryTypes");
	parseUnitTypes(tsRulesData, aircraft, "AircraftTypes");

	parseVariables(tsRulesData, globalvariables);

	houses[-1] = "Any House";
	parseHouseTypes(tsRulesData);

	// Tiberian Sun Firestorm rules
	// BuildingTypes list should not be sorted...
	CDataFile fsRulesCData(Settings::fsRulesPath.toStdString());
	{
		t_Section * buildSec = fsRulesCData.GetSection("BuildingTypes");

		if (buildSec != NULL) {
			KeyList * buildl = buildSec->GetKeyList();
			for(KeyItor keyIT = buildl->begin(); keyIT < buildl->end(); ++keyIT) {
				std::string Key = keyIT->szKey;

				std::string buildingID = fsRulesCData.GetString(Key, "BuildingTypes");
				std::string name = fsRulesCData.GetString("Name", buildingID);

				if(name != "") {
					unitContainer cont;
					cont.unitID = QString::fromStdString(buildingID);
					cont.name = QString::fromStdString(name);
					cont.key = atoi(Key.c_str()) + 169;

					buildings[buildingIndex] = cont;
				}

				++buildingIndex;
			}
		}
	}

	QSettings fsRulesData(Settings::fsRulesPath, QSettings::IniFormat);
	parseUnitTypes(fsRulesData, vehicles, "VehicleTypes");
	parseUnitTypes(fsRulesData, infantry, "InfantryTypes");
	parseUnitTypes(fsRulesData, aircraft, "AircraftTypes");
}

Taskforce* FileHandler::getTaskforce(std::string taskforceID)
{
	t_Section * cTaskF = fileData.GetSection(taskforceID);
	if(cTaskF != NULL) {

		std::string name = "New Taskforce";
		int32_t group = -1;

		Taskforce *nTaskforce = new Taskforce(QString::fromStdString(taskforceID));

		KeyList * taskl = cTaskF->GetKeyList();
		for(KeyItor keyIT = taskl->begin(); keyIT < taskl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;
			std::string curLine = fileData.GetString(Key, taskforceID);

			std::string type = "";
			short amount = 0;

			if(Key == "Group") {
				group = fileData.GetInt(Key, taskforceID);
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

Script* FileHandler::getScript(std::string scriptID)
{

	t_Section * cScript = fileData.GetSection(scriptID);

	if(cScript != NULL) {

		std::string name = "New Script";

		Script *nScript = new Script(QString::fromStdString(scriptID));

		KeyList * scriptl = cScript->GetKeyList();
		for(KeyItor keyIT = scriptl->begin(); keyIT < scriptl->end(); ++keyIT) {
			std::string Key = keyIT->szKey;
			std::string curLine = fileData.GetString(Key, scriptID);

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

Team* FileHandler::getTeam(std::string teamID)
{
	t_Section * cTeam = fileData.GetSection(teamID);

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

		max = fileData.GetInt("Max", teamID);
		tag = QString::fromStdString(fileData.GetString("Tag", teamID));
		full = convertToBool(fileData.GetString("Full", teamID));
		name = QString::fromStdString(fileData.GetString("Name", teamID));
		group = fileData.GetInt("Group", teamID);
		house = QString::fromStdString(fileData.GetString("House", teamID));
		script = QString::fromStdString(fileData.GetString("Script", teamID));
		whiner = convertToBool(fileData.GetString("Whiner", teamID));
		droppod = convertToBool(fileData.GetString("Droppod", teamID));
		suicide = convertToBool(fileData.GetString("Suicide", teamID));
		loadable = convertToBool(fileData.GetString("Loadable", teamID));
		prebuild = convertToBool(fileData.GetString("Prebuild", teamID));
		priority = fileData.GetInt("Priority", teamID);
		waypoint = QString::fromStdString(fileData.GetString("Waypoint", teamID));
		annoyance = convertToBool(fileData.GetString("Annoyance", teamID));
		ionimmune = convertToBool(fileData.GetString("IonImmune", teamID));
		recruiter = convertToBool(fileData.GetString("Recruiter", teamID));
		reinforce = convertToBool(fileData.GetString("Reinforce", teamID));
		taskforce = QString::fromStdString(fileData.GetString("TaskForce", teamID));
		techlevel = fileData.GetInt("TechLevel", teamID);
		aggressive = convertToBool(fileData.GetString("Aggressive", teamID));
		autocreate = convertToBool(fileData.GetString("Autocreate", teamID));
		guardslower = convertToBool(fileData.GetString("GuardSlower", teamID));
		ontransonly = convertToBool(fileData.GetString("OnTransOnly", teamID));
		avoidthreats = convertToBool(fileData.GetString("AvoidThreats", teamID));
		looserecruit = convertToBool(fileData.GetString("LooseRecruit", teamID));
		veteranlevel = fileData.GetInt("VeteranLevel", teamID);
		isbasedefense = convertToBool(fileData.GetString("IsBaseDefense", teamID));
		onlytargethousenemy = convertToBool(fileData.GetString("OnlyTargetHouseEnemy", teamID));
		transportsreturnonunload = convertToBool(fileData.GetString("TransportsReturnOnUnload", teamID));
		areteammembersrecruitable = convertToBool(fileData.GetString("AreTeamMembersRecruitable", teamID));


		return new Team(QString::fromStdString(teamID), max, tag, full, name, group, house, script, whiner, droppod, suicide,
						loadable, prebuild, priority, waypoint, annoyance, ionimmune, recruiter,
						reinforce, taskforce, techlevel, aggressive, autocreate, guardslower,
						ontransonly, avoidthreats, looserecruit, veteranlevel, isbasedefense,
						onlytargethousenemy, transportsreturnonunload, areteammembersrecruitable);
	}

	return NULL;
}

// Finds and adds units to given container
void FileHandler::parseUnitTypes(QSettings &rules, std::map<QString, unitContainer> &unitMap, QString type) {
	rules.beginGroup(type);
	QStringList unitList = rules.childKeys();
	rules.endGroup();

	if (!unitList.isEmpty()) {
		for(QStringList::ConstIterator keyIT = unitList.begin(); keyIT != unitList.end(); ++keyIT) {

			QString unitID = rules.value(type + "/" + *keyIT).toString();
			QString unitName = rules.value(unitID + "/Name").toString();

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

void FileHandler::parseVariables(QSettings &rules, std::map<uint16_t, variableContainer> &variableMap) {
	rules.beginGroup("VariableNames");
	QStringList variableSec = rules.childKeys();
	rules.endGroup();

	if (!variableSec.isEmpty()) {
		for(QStringList::ConstIterator keyIT = variableSec.begin(); keyIT != variableSec.end(); ++keyIT) {
			QString Key = *keyIT;

			QStringList values = rules.value("VariableNames/" + Key).toStringList();

			bool set = false;
			if(values.size() == 2)
				set = values[1].toInt();

			variableContainer cont;
			cont.set = set;
			cont.name = values[0];
			variableMap[Key.toInt()] = cont;
		}
	}
}

void FileHandler::parseHouseTypes(QSettings &rules) {
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

void FileHandler::parseTutorial(QSettings &rules) {
	rules.beginGroup("Tutorial");
	QStringList tutorialSec = rules.childKeys();
	rules.endGroup();

	if (!tutorialSec.isEmpty()) {
		for(QStringList::ConstIterator keyIT = tutorialSec.begin(); keyIT != tutorialSec.end(); ++keyIT) {
			QString Key = *keyIT;
			QString name = rules.value("Tutorial/" + Key).toString();
			tutorial[Key.toShort()] = name;
		}
	}
}

void FileHandler::clear()
{
	fileData.Clear();
}

QString FileHandler::getFilePath() const
{
	return filePath;
}

bool FileHandler::convertToBool(std::string str) const
{
	if(str == "yes" || str == "true") return true;
	if(str == "no" || str == "false") return false;
	return false;
}

std::string FileHandler::intToStr(int64_t integer) {
	std::stringstream ss;
	ss << integer;
	return ss.str();
}
