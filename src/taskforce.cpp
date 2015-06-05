#include "taskforce.h"

Taskforce::Taskforce(string nID)
{
	ID = nID;

	lineCounter = 0;

	group = -1;

	name = "";
}

Taskforce::Taskforce(string nID, string nName)
{
	ID = nID;

	lineCounter = 0;

	group = -1;

	name = nName;
}

Taskforce::Taskforce(string nID, Taskforce *tF)
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
	DeleteSectionInBuffer(ID);
}

void Taskforce::NewLine(string type, short amount)
{
	TaskforceLine *nLine = new TaskforceLine();
	nLine->type = type;
	nLine->amount = amount;
	nLine->ID = lineCounter;

	tlines.push_back(nLine);

	++lineCounter;
}

void Taskforce::DeleteLine(short ID)
{
	for(tlineIT IT = tlines.begin(); IT != tlines.end(); ++IT) {
		if((*IT)->ID == ID) {
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
}

void Taskforce::Save()
{
	for(tlineIT IT = tlines.begin(); IT != tlines.end(); ++IT) {
		stringstream valueSS;
		valueSS << (*IT)->amount << "," << (*IT)->type;
		WriteValueToBuffer(ID, IntToStr((*IT)->ID), valueSS.str());
	}
	WriteValueToBuffer(ID, "Name", name);
	WriteValueToBuffer(ID, "Group", IntToStr(group));
}
