#ifndef SCRIPT_H
#define SCRIPT_H

#include "main.h"

class Script
{
public:
	Script(string nID);

	void NewLine(short type, short param);

	void setName(string nName) { name = nName; }

	string getName() { return name; }

	std::string getID();
private:
	std::string ID;

	string name;

	struct ScriptLine
	{
		short type;
		short param;

		short ID;
	};

	std::vector <ScriptLine*> slines;
	std::vector <ScriptLine*>::iterator slineIT;

	short lineCounter;

};

#endif // SCRIPT_H
