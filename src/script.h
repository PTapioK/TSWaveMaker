#ifndef SCRIPT_H
#define SCRIPT_H

#include "main.h"

class Script
{
	public:
		Script(QString newID);
		Script(QString newID, QString newName);
		Script(QString newID, Script *currentScript);
		~Script();

		void addLine(int16_t type, int32_t parameter);
		void insertLine(int16_t type, int32_t parameter, int16_t ID);
		void deleteLine(int16_t lineID);

		void setName(QString newName);

		void save();

		QString getName() const;
		QString getID() const;
		uint16_t getLineAmount() const;
	private:
		friend class ScriptSection;

		QString ID;

		QString name;

		struct ScriptLine
		{
			int16_t type;
			int32_t param;

			int16_t ID;
		};

		std::vector <ScriptLine*> scriptLines;
		typedef std::vector <ScriptLine*>::iterator slineIT;

		uint16_t lineCounter;
	public:
		std::vector<Script::ScriptLine*> getLinesByType(SATargetType type);

};

#endif // SCRIPT_H
