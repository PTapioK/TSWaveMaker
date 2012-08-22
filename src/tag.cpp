#include "tag.h"

Tag::Tag(std::string tname, string trigID)
{
	name = tname;
	ID = fffID();
	triggerID = trigID;
	mode = 0;

}

Tag::Tag(Tag *oTag, string trigID)
{
	*this = *oTag;
	setID(fffID());
	triggerID = trigID;

}

Tag::Tag(string nID, string nName, string nTrigID, int32_t nmode)
{
	ID = nID;
	name = nName;
	triggerID = nTrigID;
	mode = nmode;
}

Tag::~Tag()
{
	stringstream line;
	line << ID << "=" << mode << "," << name << "," << triggerID;
	ClearValueAtBuffer(line.str());
}

string Tag::getID() {
	return ID;
}

void Tag::setID(string nID) {
	ID = nID;
}

string Tag::getTriggerID() {
	return triggerID;
}

void Tag::WriteToFile() {
	stringstream valueSS;
	valueSS << mode << "," << name << "," << triggerID;
	WriteToFileBuffer("[Tags]", ID, valueSS.str());
}

void Tag::setName(string nName) {
	name = nName;
}
