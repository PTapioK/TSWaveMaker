#ifndef SCRIPT_H
#define SCRIPT_H

#include "main.h"

class Script
{
	public:
		Script(std::string newID);
		Script(std::string newID, std::string newName);
		Script(std::string newID, Script *currentScript);
		~Script();

		void addLine(short type, int parameter);
		void insertLine(short type, short parameter, short ID);
		void deleteLine(short lineID);

		void setName(std::string newName);

		void save();

		std::string getName() const;
		std::string getID() const;
		uint16_t getLineAmount() const;

	private:

		friend class ScriptSection;

		std::string ID;

		std::string name;

		struct ScriptLine
		{
			short type;
			int param;

			short ID;
		};

		std::vector <ScriptLine*> scriptLines;
		typedef std::vector <ScriptLine*>::iterator slineIT;

		uint16_t lineCounter;

	public:
		std::vector<Script::ScriptLine*> GetLinesByType(SATargetType type);

};

#endif // SCRIPT_H
