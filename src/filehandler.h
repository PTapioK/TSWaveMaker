#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "main.h"

struct unitContainer;
struct variableContainer;
class Team;
class Script;
class Taskforce;

class FileHandler {
	public:
		FileHandler();
		FileHandler(QString mapFilePath);

		void loadFile(QString mapFilePath);
		void saveFile(QString as = "");
		void saveAllToBuffer();
		void writeLineToBuffer(QString section, QString ID, QString value);
		void editCountableValueInBuffer(QString section, QString ID, QString value, int count);
		void readFileToBuffer();
		void deleteLineFromBuffer(QString section, QString ID);
		void deleteSectionFromBuffer(QString section);
		void parseSections();
		void parseRules();
		void clear();

		QString getFilePath() const;
	private:
		QString filePath;
		CDataFile fileData;

		void parseUnitTypesToMap(QSettings &rules, std::map<QString, unitContainer> &unitMap, QString type);
		void parseVariablesToMap(QSettings &rules, std::map<uint16_t, variableContainer> &variableMap);
		void parseHouseTypes(QSettings &rules);

		Team* findNewTeamFromFile(std::string teamID);
		Script* findNewScriptFromFile(std::string scriptID);
		Taskforce* findNewTaskforceFromFile(std::string taskforceID);

		bool convertToBool(std::string str);
};

#endif // FILEHANDLER_H
