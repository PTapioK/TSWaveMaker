#include "script.h"

Script::Script(string nID)
{
	name = string("");

	ID = nID;

	lineCounter = 0;
}

Script::Script(string nID, string nName)
{
	name = nName;

	ID = nID;

	lineCounter = 0;
}

Script::Script(string nID, Script *cS)
{
	ID = nID;

	lineCounter = 0;

	slines.clear();
	for(slineIT IT = cS->slines.begin(); IT != cS->slines.end(); ++IT) {
		ScriptLine *sline = new ScriptLine();
		sline->param = (*IT)->param;
		sline->type = (*IT)->type;
		sline->ID = (*IT)->ID;
		slines.push_back(sline);
		++lineCounter;
	}
}

Script::~Script()
{
	DeleteSectionInBuffer(ID);
}

void Script::NewLine(short type, int param) {
	ScriptLine *nLine = new ScriptLine();
	nLine->param = param;
	nLine->type = type;
	nLine->ID = lineCounter;

	slines.push_back(nLine);

	++lineCounter;
}

void Script::InsertLine(short type, short param, short ID)
{
	for(slineIT IT = slines.begin(); IT != slines.end(); ++IT) {
		if((*IT)->ID >= ID) {
			(*IT)->ID = (*IT)->ID + 1;
		}
	}

	ScriptLine *nLine = new ScriptLine();
	nLine->param = param;
	nLine->type = type;
	nLine->ID = ID;

	slines.insert(slines.begin() + ID, nLine);

	++lineCounter;

}

void Script::DeleteLine(short lineID)
{

	for(slineIT IT = slines.begin(); IT != slines.end(); ++IT) {
		if((*IT)->ID == lineID) {
			delete (*IT);
			slines.erase(IT);
			break;
		}
	}

	lineCounter = 0;

	for(slineIT IT = slines.begin(); IT != slines.end(); ++IT) {
		(*IT)->ID = lineCounter;
		++lineCounter;
	}
	DeleteValueInBuffer(ID, IntToStr(lineID));
}

void Script::Save()
{
	for(slineIT IT = slines.begin(); IT != slines.end(); ++IT) {
		stringstream valueSS;
		valueSS << (*IT)->type << "," << (*IT)->param;
		WriteValueToBuffer(ID, IntToStr((*IT)->ID), valueSS.str());
	}
	WriteValueToBuffer(ID, "Name", name);
}

std::string Script::getID() {
	return ID;
}

vector<Script::ScriptLine *> Script::GetLinesByType(SATargetType type)
{
	vector<ScriptLine*> lines;
	for(slineIT IT = slines.begin(); IT != slines.end(); ++IT) {
		if(GetScriptActionTargetType((*IT)->type) == type) {
			lines.push_back((*IT));
		}
	}
	return lines;
}
