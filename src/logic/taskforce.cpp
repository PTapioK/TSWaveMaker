#include "taskforce.h"

Taskforce::Taskforce(QString nID)
{
	ID = nID;

	lineCounter = 0;

	group = -1;

	name = "";
}

Taskforce::Taskforce(QString nID, QString nName)
{
	ID = nID;

	lineCounter = 0;

	group = -1;

	name = nName;
}

Taskforce::Taskforce(QString nID, Taskforce *tF)
{
	ID = nID;

	lineCounter = 0;

	taskforceLines.clear();
	for(taskforceLineIT IT = tF->taskforceLines.begin(); IT != tF->taskforceLines.end(); ++IT) {
		TaskforceLine *tline = new TaskforceLine();
		tline->amount = (*IT)->amount;
		tline->type = (*IT)->type;
		tline->ID = (*IT)->ID;
		taskforceLines.push_back(tline);
		++lineCounter;
	}
}

Taskforce::~Taskforce()
{
	file.deleteSectionFromBuffer(ID);
}

void Taskforce::addLine(QString type, uint16_t amount)
{
	TaskforceLine *nLine = new TaskforceLine();
	nLine->type = type;
	nLine->amount = amount;
	nLine->ID = lineCounter;

	taskforceLines.push_back(nLine);

	++lineCounter;
}

void Taskforce::deleteLine(uint16_t lineID)
{
	for(taskforceLineIT IT = taskforceLines.begin(); IT != taskforceLines.end(); ++IT) {
		if((*IT)->ID == lineID) {
			delete (*IT);
			taskforceLines.erase(IT);
			break;
		}
	}

	lineCounter = 0;

	for(taskforceLineIT IT = taskforceLines.begin(); IT != taskforceLines.end(); ++IT) {
		(*IT)->ID = lineCounter;
		++lineCounter;
	}
	file.deleteLineFromBuffer(ID, QString::number(lineID));
}

void Taskforce::save()
{
	for(taskforceLineIT IT = taskforceLines.begin(); IT != taskforceLines.end(); ++IT) {
		QString str;
		QTextStream valueSS(&str);
		valueSS << (*IT)->amount << "," << (*IT)->type;
		file.saveLineToBuffer(ID, QString::number((*IT)->ID), valueSS.readAll());
	}
	file.saveLineToBuffer(ID, "Name", name);
	file.saveLineToBuffer(ID, "Group", QString::number(group));
}

QString Taskforce::getID() const
{
	return ID;
}

QString Taskforce::getName() const
{
	return name;
}

uint16_t Taskforce::getLineAmount() const
{
	return lineCounter;
}
