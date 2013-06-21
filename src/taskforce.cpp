#include "taskforce.h"

Taskforce::Taskforce(string nID)
{
	ID = nID;

	lineCounter = 0;
}

void Taskforce::NewLine(string type, short amount)
{
	TaskforceLine *nLine = new TaskforceLine();
	nLine->type = type;
	nLine->amount = amount;

	tlines.push_back(nLine);
}
