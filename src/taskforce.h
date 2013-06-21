#ifndef TASKFORCE_H
#define TASKFORCE_H

#include "main.h"

class Taskforce
{
public:
	Taskforce(string nID);
	std::string getID() { return ID; }

	void NewLine(string type, short amount);

	void setGroup(int32_t nGroup) { group = nGroup; }
	void setName(string nName) { name = nName; }

	string getName() { return name; }

private:
	std::string ID;

	std::string name;
	int32_t group;

	struct TaskforceLine
	{
		string type;
		short amount;
	};

	std::vector <TaskforceLine*> tlines;
	std::vector <TaskforceLine*>::iterator tlineIT;

	short lineCounter;

};

#endif // TASKFORCE_H
