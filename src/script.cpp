#include "script.h"

Script::Script(string nID)
{
	ID = nID;

	lineCounter = 0;

}

void Script::NewLine(short type, short param) {
	ScriptLine *nLine = new ScriptLine();
	nLine->param = param;
	nLine->type = type;

	nLine->ID = lineCounter;

	slines.push_back(nLine);

	++lineCounter;
}

std::string Script::getID() {
	return ID;
}
