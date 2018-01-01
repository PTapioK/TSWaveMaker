#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "../main.h"
#include "CDataFile/CDataFile.h"

struct unitContainer;
struct variableContainer;
class Team;
class Script;
class Taskforce;

class FileHandler {
	public:
		FileHandler();
		FileHandler(QString mapFilePath);

		void load(QString mapFilePath);
		void save(QString as = "");
		void saveLineToBuffer(QString section, QString ID, QString value);
		void editCountableValueInBuffer(QString section, QString ID, QString value, int count);
		void deleteLineFromBuffer(QString section, QString ID);
		void deleteSectionFromBuffer(QString section);

		QString parseSections();
		void parseRules();

		void clear();

		QString getFilePath() const;
	private:
		QString filePath;
		CDataFile fileData;

		void saveToBuffer();
		void readToBuffer();

		void parseUnitTypes(QSettings &rules, std::map<QString, unitContainer> &unitMap, QString type);
		void parseVariables(QSettings &rules, std::map<uint16_t, variableContainer> &variableMap);
		void parseHouseTypes(QSettings &rules);
		void parseTutorial(QSettings &rules);

		Team* getTeam(std::string teamID);
		Script* getScript(std::string scriptID);
		Taskforce* getTaskforce(std::string taskforceID);

		bool convertToBool(std::string str) const;
		std::string intToStr(int64_t integer);
};

#endif // FILEHANDLER_H
