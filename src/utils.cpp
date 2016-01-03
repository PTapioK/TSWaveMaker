#include "utils.h"


// Find First Free ID
QString fffID()
{
	QString nextID;
	QString value;
	QTextStream ssID(&value);

	int32_t i = 1000000;

	std::vector<QString> IDTemp;
	std::vector<QString>::iterator IDIT;

	if(triggers.empty() && tags.empty() && teams.empty() && scripts.empty() && taskforces.empty() && aitriggers.empty()) {
		ssID << "0" << i;
		return ssID.readAll();
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

	IDIT = find(IDTemp.begin(), IDTemp.end(), QString("01000000"));

	if(IDIT == IDTemp.end()) {
		IDIT = IDTemp.begin();
	}

	QString a = "";
	while(1) {
		QString str("");
		ssID.setString(&str);
		ssID << "0" << i;
		nextID = ssID.readAll();

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

	QString str("");
	ssID.setString(&str);
	ssID << "0" << i;
	nextID = ssID.readAll();

	return nextID;
}

Tag* getTagByTriggerID(QString trigID)
{
	for(tagIT IT = tags.begin(); IT != tags.end(); ++IT) {
		if((*IT).second->getTriggerID() == trigID) {
			return (*IT).second;
		}
	}
	return NULL;
}

QString decToWaypointID(int dec)
{
	QString retVal;
	dec = dec + 1;
	while(dec != 0) {
		--dec;
		retVal = alphas[dec % 26] + retVal;
		dec /= 26;
	}
	return retVal;
}

QString convertToSmallAlphas(int32_t dec)
{
	QString retVal;
	dec=dec+1;
	while(dec != 0) {
		--dec;
		retVal = small_alphas[dec % 26] + retVal;
		dec /= 26;
	}
	return retVal;
}

QString getTriggerIDByName(QString name)
{
	for(triggerIT IT = triggers.begin(); IT != triggers.end(); ++IT) {
		if((*IT).second->getName() == name) {
			return IT->second->getID();
		}
	}
	return QString("");
}

Trigger* getTriggerByName(QString name)
{
	for(triggerIT IT = triggers.begin(); IT != triggers.end(); ++IT) {
		if((*IT).second->getName() == name) {
			return IT->second;
		}
	}
	return NULL;
}

int32_t waypointIDToDec(QString wID)
{
	int32_t value = 0;
	int i = wID.length();
	while(1) {
		if(i == 0) { break; }
		--i;
		const char chr = *wID.mid(i, 1).toStdString().c_str();
		int32_t multip = 0;
		for(int j = 0; j != 26; ++j) {
			if(chr == alphas[j]) {
				multip = j + 1;
				break;
			}
		}
		int p = pow(26.0, int(wID.length() - (i + 1)));
		value = value + (multip * p);
	}
	return value-1;
}

bool convertToBool(std::string str)
{
	if(str == "yes" || str == "true") {
		return true;
	}
	if(str == "no" || str == "false") {
		return false;
	}

	return false;
}

QString converBoolToYesNo(bool boolean)
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

QString getTeamNameByID(QString ID)
{
	for(teamIT IT = teams.begin(); IT != teams.end(); ++IT) {
		if(IT->second->getID() == ID) {
			return IT->second->getName();
		}
	}
	return QString("");
}

Team* getTeamByName(QString name)
{
	for(teamIT IT = teams.begin(); IT != teams.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second;
		}
	}
	return NULL;
}

QString getTeamIDByName(QString name)
{
	for(teamIT IT = teams.begin(); IT != teams.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second->getID();
		}
	}
	return QString("");
}

QString getScriptNameByID(QString ID)
{
	for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		if(IT->second->getID() == ID) {
			return IT->second->getName();
		}
	}
	return QString("");
}

QString getScriptIDByName(QString name)
{
	for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second->getID();
		}
	}
	return QString("");
}

QString getTaskforceNameByID(QString ID)
{
	for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		if(IT->second->getID() == ID) {
			return IT->second->getName();
		}
	}
	return QString("");
}

QString getTaskforceIDByName(QString name)
{
	for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second->getID();
		}
	}
	return QString("");
}


Taskforce* getTaskforceByName(QString name)
{
	for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second;
		}
	}
	return NULL;
}


Script* getScriptByName(QString name)
{
	for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second;
		}
	}
	return NULL;
}


QString getScriptNameByPosition(uint16_t pos)
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

QString getTaskforceNameByPosition(uint16_t pos)
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
	QString retVal;

	QSettings strings("scriptactionscriptStrings.ini", QSettings::IniFormat);
	retVal = scriptStrings.value("Actions/" + QString::number(ID), QString("Not Implemented!")).toString();

	return retVal;

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
	QStringList strList;

	switch(type) {
	case TARGET:
		scriptStrings.beginGroup("Target");
		strList = scriptStrings.childKeys();
		qSort(strList.begin(), strList.end(), lessThanQString);
		for(QStringList::ConstIterator IT = strList.begin(); IT != strList.end(); ++IT) {
			list << scriptStrings.value((*IT)).toStringList().join(", ");
		}
		scriptStrings.endGroup();
		break;
	case WAYPOINT:
		for(waypointIT IT = waypoints.begin(); IT != waypoints.end(); ++IT) {
			list << QString::number((*IT));
		}
		break;
	case UNLOAD:
		scriptStrings.beginGroup("Unload");
		strList = scriptStrings.childKeys();
		qSort(strList.begin(), strList.end(), lessThanQString);
		for(QStringList::ConstIterator IT = strList.begin(); IT != strList.end(); ++IT) {
			list << scriptStrings.value((*IT)).toStringList().join(", ");
		}
		scriptStrings.endGroup();
		break;
	case MISSION:
		scriptStrings.beginGroup("Mission");
		strList = scriptStrings.childKeys();
		qSort(strList.begin(), strList.end(), lessThanQString);
		for(QStringList::ConstIterator IT = strList.begin(); IT != strList.end(); ++IT) {
			list << scriptStrings.value((*IT)).toStringList().join(", ");
		}
		scriptStrings.endGroup();
		break;
	case BUILDING:
		for(std::map<uint16_t, unitContainer>::iterator IT = buildings.begin(); IT != buildings.end(); ++IT) {
			list << (*IT).second.name;
		}
		break;
	case BALLOON:
		scriptStrings.beginGroup("Balloon");
		strList = scriptStrings.childKeys();
		qSort(strList.begin(), strList.end(), lessThanQString);
		for(QStringList::ConstIterator IT = strList.begin(); IT != strList.end(); ++IT) {
			list << scriptStrings.value((*IT)).toStringList().join(", ");
		}
		scriptStrings.endGroup();
		break;
	case FACING:
		scriptStrings.beginGroup("Facing");
		strList = scriptStrings.childKeys();
		qSort(strList.begin(), strList.end(), lessThanQString);
		for(QStringList::ConstIterator IT = strList.begin(); IT != strList.end(); ++IT) {
			list << scriptStrings.value((*IT)).toStringList().join(", ");
		}
		scriptStrings.endGroup();
		break;
	case LOCAL:
		for(std::map <uint16_t, variableContainer>::iterator IT = localvariables.begin(); IT != localvariables.end(); ++IT) {
			list << (*IT).second.name;
		}
		break;
	case GLOBAL:
		for(std::map <uint16_t, variableContainer>::iterator IT = globalvariables.begin(); IT != globalvariables.end(); ++IT) {
			list << (*IT).second.name;
		}
		break;
	case SCRIPT:
		for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
			list << (*IT).second->getName();
		}
		break;
	case TASKFORCE:
		for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
			list << (*IT).second->getName();
		}
		break;
	case HOUSE:
		for(std::map<uint16_t, QString >::iterator IT = houses.begin(); IT != houses.end(); ++IT) {
			list << (*IT).second;
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

QString getNameWithNextMark(QString name, int iter, int numIter)
{
	QString oName = name;
	if(numIter == -1000000) numIter = iter;

	if(alphabetNaming) {
		for(int i = 0; i != 26; ++i) {
			QString str;
			QTextStream ss(&str);
			ss << " " << alphas[i];
			if(name.contains(ss.readAll())) {
				name.replace(name.indexOf(ss.readAll()), ss.readAll().length(), QString (" ") + decToWaypointID(i + iter + 1));
				break;
			} else if(*(name.end()-1) == alphas[i]) {
				name.replace(name.length()-1, sizeof(char), decToWaypointID(i + iter + 1));
				break;
			}
		}
		for(int i = 0; i != 26; ++i) {
			QString str;
			QTextStream ss(&str);
			ss << " " << small_alphas[i];
			if(name.contains(ss.readAll())) {
				name.replace(name.indexOf(ss.readAll()), ss.readAll().length(), QString (" ") + convertToSmallAlphas(i + iter + 1));
				break;
			} else if(*(name.end()-1) == small_alphas[i]) {
				name.replace(name.length()-1, sizeof(char), convertToSmallAlphas(i + iter + 1));
				break;
			}
		}
	}
	if(ascNumNaming) {
		int intLoc = -1;
		for(int i = 0; i < 10; ++i) {
			intLoc = name.indexOf(QString::number(i));
			if(intLoc != -1) {
				QString numStr("");
				int num = name.right(intLoc).toInt();
				numStr = QString::number(num);
				name.replace(intLoc, numStr.length(), QString::number(num + numIter + 1));
				break;
			}
		}
	}
	if(cloneOfNaming) {
		name = "Clone of " + name;
	}

	if(oName == name)
		return name + QString::number(iter);
	return name;
}


QString getUnitNameByUnitID(QString unitID)
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
	return QString("");
}



bool lessThanQString(const QString &str1, const QString &str2)
{
	return str1.toInt() < str2.toInt();
}
