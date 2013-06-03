#ifndef TASKFORCE_H
#define TASKFORCE_H

#include "main.h"

class Taskforce
{
public:
	Taskforce();
	std::string getID() { return ID; }
private:
	std::string ID;
};

#endif // TASKFORCE_H
