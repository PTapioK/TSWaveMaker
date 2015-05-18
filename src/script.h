#ifndef SCRIPT_H
#define SCRIPT_H

#include "main.h"

class Script
{
public:
	Script(string nID);
	Script(string nID, string nName);
	Script(string nID, Script *cS);
	~Script();

	void NewLine(short type, short param);
	void DeleteLine(short ID);

	void setName(string nName) { name = nName; }

	string getName() { return name; }

	std::string getID();

	uint32_t getLineAmount() { return lineCounter; }

	void Save();

private:

	friend class ScriptSection;

	std::string ID;

	string name;

	struct ScriptLine
	{
		short type;
		int param;

		short ID;
	};

	std::vector <ScriptLine*> slines;
	typedef std::vector <ScriptLine*>::iterator slineIT;

	short lineCounter;

public:

	vector<Script::ScriptLine*> GetLinesByType(SATargetType type);

};

#endif // SCRIPT_H
