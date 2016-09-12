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

	for(auto IT = triggers.begin(); IT != triggers.end(); ++IT) {
		IDTemp.push_back((*IT).second->getID());
	}

	for(auto IT = tags.begin(); IT != tags.end(); ++IT) {
		IDTemp.push_back((*IT).second->getID());
	}

	for(auto IT = teams.begin(); IT != teams.end(); ++IT) {
		IDTemp.push_back((*IT).first);
	}

	for (auto IT = scripts.begin(); IT != scripts.end(); ++IT) {
		IDTemp.push_back((*IT).second->getID());
	}

	for (auto IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		IDTemp.push_back((*IT).second->getID());
	}

	for (auto IT = aitriggers.begin(); IT != aitriggers.end(); ++IT) {
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
	for(auto IT = tags.begin(); IT != tags.end(); ++IT) {
		if((*IT).second->getTriggerID() == trigID) {
			return (*IT).second;
		}
	}
	QMessageBox::critical(NULL, "Fatal error!", "Fatal error occured when trying to find trigger with ID: " + trigID + ".\nThe program will now terminate.");
	exit(EXIT_FAILURE);
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
	for(auto IT = triggers.begin(); IT != triggers.end(); ++IT) {
		if((*IT).second->getName() == name) {
			return IT->second->getID();
		}
	}
	return QString("");
}

Trigger* getTriggerByName(QString name)
{
	for(auto IT = triggers.begin(); IT != triggers.end(); ++IT) {
		if((*IT).second->getName() == name) {
			return IT->second;
		}
	}
	QMessageBox::critical(NULL, "Fatal error!", "Fatal error occured when trying to find trigger with name: " + name + ".\nThe program will now terminate.");
	exit(EXIT_FAILURE);
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

QString getTeamNameByID(QString ID)
{
	for(auto IT = teams.begin(); IT != teams.end(); ++IT) {
		if(IT->second->getID() == ID) {
			return IT->second->getName();
		}
	}
	return QString("");
}

Team* getTeamByName(QString name)
{
	for(auto IT = teams.begin(); IT != teams.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second;
		}
	}
	QMessageBox::critical(NULL, "Fatal error!", "Fatal error occured when trying to find team with name: " + name + ".\nThe program will now terminate.");
	exit(EXIT_FAILURE);
	return NULL;
}

QString getTeamIDByName(QString name)
{
	for(auto IT = teams.begin(); IT != teams.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second->getID();
		}
	}
	return QString("");
}

QString getScriptNameByID(QString ID)
{
	for(auto IT = scripts.begin(); IT != scripts.end(); ++IT) {
		if(IT->second->getID() == ID) {
			return IT->second->getName();
		}
	}
	return QString("");
}

QString getScriptIDByName(QString name)
{
	for(auto IT = scripts.begin(); IT != scripts.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second->getID();
		}
	}
	return QString("");
}

QString getTaskforceNameByID(QString ID)
{
	for(auto IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		if(IT->second->getID() == ID) {
			return IT->second->getName();
		}
	}
	return QString("");
}

QString getTaskforceIDByName(QString name)
{
	for(auto IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second->getID();
		}
	}
	return QString("");
}


Taskforce* getTaskforceByName(QString name)
{
	for(auto IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second;
		}
	}
	QMessageBox::critical(NULL, "Fatal error!", "Fatal error occured when trying to find taskforce with name: " + name + ".\nThe program will now terminate.");
	exit(EXIT_FAILURE);
	return NULL;
}


Script* getScriptByName(QString name)
{
	for(auto IT = scripts.begin(); IT != scripts.end(); ++IT) {
		if(IT->second->getName() == name) {
			return IT->second;
		}
	}
	QMessageBox::critical(NULL, "Fatal error!", "Fatal error occured when trying to find script with name: " + name + ".\nThe program will now terminate.");
	exit(EXIT_FAILURE);
	return NULL;
}

SATargetType getScriptActionTargetType(uint8_t ID)
{
	QVariant value;
	value = scriptStrings.value("Actions/" + QString::number(ID));
	if (!value.isNull()) {
		return static_cast<SATargetType>(value.toStringList()[1].toInt());
	} else {
		return SATargetType::NONE;
	}
}

int32_t getStringListMaxWidth(QStringList list, QFont font)
{
	if (!list.empty()) {
		std::vector <size_t> widths;
		QFontMetrics metr(font);
		for(QStringList::Iterator listIT = list.begin(); listIT != list.end(); ++listIT) {
			widths.push_back(metr.width(*listIT));
		}
		return int32_t(*max_element(widths.begin(), widths.end()));
	}
	return 0;
}

int32_t getComboBoxMaxWidth(QComboBox *box)
{
	box->update();
	if (box != NULL && box->count() > 0) {
		std::vector <size_t> widths;
		QFontMetrics metr(box->font());
		for(int i = 0; i < box->count(); ++i) {
			widths.push_back(metr.width(box->itemText(i)));
		}
		return int32_t(*max_element(widths.begin(), widths.end()));
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
	for(auto IT = triggers.begin(); IT != triggers.end(); ++IT) {
		delete (*IT).second;
	}
	triggers.clear();
	for(auto IT = teams.begin(); IT != teams.end(); ++IT) {
		delete (*IT).second;
	}
	teams.clear();
	for(auto IT = tags.begin(); IT != tags.end(); ++IT) {
		delete (*IT).second;
	}
	tags.clear();
	for(auto IT = scripts.begin(); IT != scripts.end(); ++IT) {
		delete (*IT).second;
	}
	scripts.clear();
	for(auto IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
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

	tutorial.clear();
}

QString getNameWithNextMark(QString name, int iter, int numIter)
{
	QString oName = name;
	if(numIter == -1000000) numIter = iter;

	if(alphabetNaming) {
		for(int i = 0; i != 26; ++i) {
			QString str = " " + QString(alphas[i]);
			if(name.contains(str)) {
				QString c = QString (" ") + decToWaypointID(i + iter + 1);
				name.replace(name.indexOf(str), str.length(), QString (" ") + decToWaypointID(i + iter + 1));
				break;
			} else if(*(name.end()-1) == alphas[i]) {
				name.replace(name.length()-1, 1, decToWaypointID(i + iter + 1));
				break;
			}
		}
		for(int i = 0; i != 26; ++i) {
			QString str = " " + QString(small_alphas[i]);
			if(name.contains(str)) {
				name.replace(name.indexOf(str), str.length(), QString (" ") + decToSmallAlphas(i + iter + 1));
				break;
			} else if(*(name.end()-1) == small_alphas[i]) {
				name.replace(name.length()-1, 1, decToSmallAlphas(i + iter + 1));
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
				int num = name.mid(intLoc).toInt();
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
	for(auto IT = aircraft.begin(); IT != aircraft.end(); ++IT) {
		if(IT->second.unitID == unitID) {
			return IT->second.name;
		}
	}
	for(auto IT = infantry.begin(); IT != infantry.end(); ++IT) {
		if(IT->second.unitID == unitID) {
			return IT->second.name;
		}
	}
	for(auto IT = vehicles.begin(); IT != vehicles.end(); ++IT) {
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

Tag *getTagByName(QString name)
{
	for(auto IT = tags.begin(); IT != tags.end(); ++IT) {
		if((*IT).second->getName() == name) {
			return IT->second;
		}
	}
	QMessageBox::critical(NULL, "Fatal error!", "Fatal error occured when trying to find tag with name: " + name + ".\nThe program will now terminate.");
	exit(EXIT_FAILURE);
	return NULL;
}
