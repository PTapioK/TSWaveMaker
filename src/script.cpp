#include "script.h"

Script::Script(std::string newID)
{
	name = std::string("");

	ID = newID;

	lineCounter = 0;
}

Script::Script(std::string newID, std::string newName)
{
	name = newName;

	ID = newID;

	lineCounter = 0;
}

Script::Script(std::string newID, Script *currentScript)
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

void Script::addLine(short type, int parameter)
{
	ScriptLine *newLine = new ScriptLine();
	newLine->param = parameter;
	newLine->type = type;
	newLine->ID = lineCounter;

	scriptLines.push_back(newLine);

	++lineCounter;
}

void Script::insertLine(short type, short parameter, short ID)
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

void Script::deleteLine(short lineID)
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
	deleteLineFromBuffer(ID, intToStr(lineID));
}

void Script::setName(std::string newName)
{
	name = newName;
}

void Script::save()
{
	for(slineIT IT = scriptLines.begin(); IT != scriptLines.end(); ++IT) {
		std::stringstream valueSS;
		valueSS << (*IT)->type << "," << (*IT)->param;
		writeLineToBuffer(ID, intToStr((*IT)->ID), valueSS.str());
	}
	writeLineToBuffer(ID, "Name", name);
}

std::string Script::getName() const
{
	return name;
}

std::string Script::getID() const {
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
