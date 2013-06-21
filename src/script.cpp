#include "script.h"

Script::Script(string nID)
{
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
	*this = *cS;
	ID = nID;

	slines.clear();
	for(slineIT = cS->slines.begin(); slineIT != cS->slines.end(); ++slineIT) {
		ScriptLine *sline = new ScriptLine();
		sline->param = (*slineIT)->param;
		sline->type = (*slineIT)->type;
		sline->ID = (*slineIT)->ID;
		slines.push_back(sline);
	}
}

void Script::NewLine(short type, short param) {
	ScriptLine *nLine = new ScriptLine();
	nLine->param = param;
	nLine->type = type;

	nLine->ID = lineCounter;

	slines.push_back(nLine);

	++lineCounter;
}

void Script::DeleteLine(short ID)
{

	for(slineIT = slines.begin(); slineIT != slines.end(); ++slineIT) {
		if((*slineIT)->ID == ID) {
			delete (*slineIT);
			slines.erase(slineIT);
			break;
		}
	}

	lineCounter = 0;

	for(slineIT = slines.begin(); slineIT != slines.end(); ++slineIT) {
		(*slineIT)->ID = lineCounter;
		++lineCounter;
	}

}

void Script::WriteToFile()
{
	for(slineIT = slines.begin(); slineIT != slines.end(); ++slineIT) {
		stringstream IDss;
		IDss << (*slineIT)->ID;
		stringstream valueSS;
		valueSS << (*slineIT)->type << "," << (*slineIT)->param;
		WriteToFileBuffer("[" + ID + "]", IDss.str(), valueSS.str());
	}
	WriteToFileBuffer("[" + ID + "]", "Name", name);
}

std::string Script::getID() {
	return ID;
}

vector<Script::ScriptLine *> Script::GetLinesByType(SATargetType type)
{
	vector<ScriptLine*> lines;
	for(slineIT = slines.begin(); slineIT != slines.end(); ++slineIT) {
		if(GetScriptActionTargetType((*slineIT)->type) == type) {
			lines.push_back((*slineIT));
		}
	}
	return lines;
}
