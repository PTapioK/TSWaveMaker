#include "script.h"

Script::Script(QString newID)
{
	name = QString("");

	ID = newID;

	lineCounter = 0;
}

Script::Script(QString newID, QString newName)
{
	name = newName;

	ID = newID;

	lineCounter = 0;
}

Script::Script(QString newID, Script *currentScript)
{
	ID = newID;

	lineCounter = 0;

	scriptLines.clear();
	for(slineIT IT = currentScript->scriptLines.begin(); IT != currentScript->scriptLines.end(); ++IT) {
		ScriptLine *scriptLine = new ScriptLine();
		scriptLine->param = (*IT)->param;
		scriptLine->type = (*IT)->type;
		scriptLine->ID = (*IT)->ID;
		scriptLines.push_back(scriptLine);
		++lineCounter;
	}
}

Script::~Script()
{
	deleteSectionFromBuffer(ID);
}

void Script::addLine(int16_t type, int32_t parameter)
{
	ScriptLine *newLine = new ScriptLine();
	newLine->param = parameter;
	newLine->type = type;
	newLine->ID = lineCounter;

	scriptLines.push_back(newLine);

	++lineCounter;
}

void Script::insertLine(int16_t type, int16_t parameter, int16_t ID)
{
	for(slineIT IT = scriptLines.begin(); IT != scriptLines.end(); ++IT) {
		if((*IT)->ID >= ID) {
			(*IT)->ID = (*IT)->ID + 1;
		}
	}

	ScriptLine *newLine = new ScriptLine();
	newLine->param = parameter;
	newLine->type = type;
	newLine->ID = ID;

	scriptLines.insert(scriptLines.begin() + ID, newLine);

	++lineCounter;

}

void Script::deleteLine(int16_t lineID)
{

	for(slineIT IT = scriptLines.begin(); IT != scriptLines.end(); ++IT) {
		if((*IT)->ID == lineID) {
			delete (*IT);
			scriptLines.erase(IT);
			break;
		}
	}

	lineCounter = 0;

	for(slineIT IT = scriptLines.begin(); IT != scriptLines.end(); ++IT) {
		(*IT)->ID = lineCounter;
		++lineCounter;
	}
	deleteLineFromBuffer(ID, QString::number(lineID));
}

void Script::setName(QString newName)
{
	name = newName;
}

void Script::save()
{
	for(slineIT IT = scriptLines.begin(); IT != scriptLines.end(); ++IT) {
		QString str;
		QTextStream valueSS(&str);
		valueSS << (*IT)->type << "," << (*IT)->param;
		writeLineToBuffer(ID, QString::number((*IT)->ID), valueSS.readAll());
	}
	writeLineToBuffer(ID, "Name", name);
}

QString Script::getName() const
{
	return name;
}

QString Script::getID() const {
	return ID;
}

uint16_t Script::getLineAmount() const
{
	return lineCounter;
}

std::vector<Script::ScriptLine *> Script::GetLinesByType(SATargetType type)
{
	std::vector<ScriptLine*> lines;
	for(slineIT IT = scriptLines.begin(); IT != scriptLines.end(); ++IT) {
		if(getScriptActionTargetType((*IT)->type) == type) {
			lines.push_back((*IT));
		}
	}
	return lines;
}
