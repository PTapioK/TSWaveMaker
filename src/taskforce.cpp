#include "taskforce.h"

Taskforce::Taskforce(std::string nID)
{
	ID = nID;

	lineCounter = 0;

	group = -1;

	name = "";
}

Taskforce::Taskforce(std::string nID, std::string nName)
{
	ID = nID;

	lineCounter = 0;

	group = -1;

	name = nName;
}

Taskforce::Taskforce(std::string nID, Taskforce *tF)
{
	ID = nID;

	lineCounter = 0;

	tlines.clear();
	for(tlineIT IT = tF->tlines.begin(); IT != tF->tlines.end(); ++IT) {
		TaskforceLine *tline = new TaskforceLine();
		tline->amount = (*IT)->amount;
		tline->type = (*IT)->type;
		tline->ID = (*IT)->ID;
		tlines.push_back(tline);
		++lineCounter;
	}
}

Taskforce::~Taskforce()
{
	deleteSectionFromBuffer(ID);
}

void Taskforce::addLine(std::string type, short amount)
{
	TaskforceLine *nLine = new TaskforceLine();
	nLine->type = type;
	nLine->amount = amount;
	nLine->ID = lineCounter;

	tlines.push_back(nLine);

	++lineCounter;
}

void Taskforce::deleteLine(short lineID)
{
	for(tlineIT IT = tlines.begin(); IT != tlines.end(); ++IT) {
		if((*IT)->ID == lineID) {
			delete (*IT);
			tlines.erase(IT);
			break;
		}
	}

	lineCounter = 0;

	for(tlineIT IT = tlines.begin(); IT != tlines.end(); ++IT) {
		(*IT)->ID = lineCounter;
		++lineCounter;
	}
	deleteLineFromBuffer(ID, intToStr(lineID));
}

void Taskforce::save()
{
	for(tlineIT IT = tlines.begin(); IT != tlines.end(); ++IT) {
		std::stringstream valueSS;
		valueSS << (*IT)->amount << "," << (*IT)->type;
		writeLineToBuffer(ID, intToStr((*IT)->ID), valueSS.str());
	}
	writeLineToBuffer(ID, "Name", name);
	writeLineToBuffer(ID, "Group", intToStr(group));
}

std::string Taskforce::getID() const
{
	return ID;
}

std::string Taskforce::getName() const
{
	return name;
}

uint16_t Taskforce::getLineAmount() const
{
	return lineCounter;
}
