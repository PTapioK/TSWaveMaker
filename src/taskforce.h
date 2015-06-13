#ifndef TASKFORCE_H
#define TASKFORCE_H

#include "main.h"

class Taskforce
{
public:
	Taskforce(string nID);
	Taskforce(string nID, string nName);
	Taskforce(string nID, Taskforce *tF);
	~Taskforce();

	std::string getID() { return ID; }

	void NewLine(string type, short amount);
	void DeleteLine(short lineID);

	void setGroup(int32_t nGroup) { group = nGroup; }
	void setName(string nName) { name = nName; }

	string getName() { return name; }

	uint32_t getLineAmount() { return lineCounter; }

	void Save();

private:

	friend class TaskforceSection;

	std::string ID;

	std::string name;
	int32_t group;

	struct TaskforceLine
	{
		string type;
		short amount;

		short ID;
	};

	std::vector <TaskforceLine*> tlines;
	typedef std::vector <TaskforceLine*>::iterator tlineIT;

	short lineCounter;

};

#endif // TASKFORCE_H
