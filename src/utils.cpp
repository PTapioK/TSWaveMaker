#include "utils.h"
#include "settings.h"

using namespace Settings;

QString findFirstFreeID()
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

QString decToWaypointID(int32_t dec)
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

QString decToSmallAlphas(int32_t dec)
{
	QString retVal;
	dec = dec + 1;
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

QString convertBoolToYesNo(bool boolean)
{
	if(boolean == true) {
		return "yes";
	} else {
		return "no";
	}
}

std::string intToStr(int64_t integer) {
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


uint16_t getBuildingTypePosByKey(uint16_t key)
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
				name.replace(name.indexOf(ss.readAll()), ss.readAll().length(), QString (" ") + decToSmallAlphas(i + iter + 1));
				break;
			} else if(*(name.end()-1) == small_alphas[i]) {
				name.replace(name.length()-1, sizeof(char), decToSmallAlphas(i + iter + 1));
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
