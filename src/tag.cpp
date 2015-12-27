#include "tag.h"

Tag::Tag(std::string tname, std::string trigID)
{
	name = tname;
	ID = fffID();
	triggerID = trigID;
	mode = 0;

}

Tag::Tag(Tag *oTag, std::string trigID)
{
	*this = *oTag;
	setID(fffID());
	triggerID = trigID;

}

Tag::Tag(std::string nID, std::string nName, std::string nTrigID, int32_t nmode)
{
	ID = nID;
	name = nName;
	triggerID = nTrigID;
	mode = nmode;
}

Tag::~Tag()
{
	deleteLineFromBuffer("Tags", ID);
}

std::string Tag::getID() const {
	return ID;
}

void Tag::setID(std::string nID) {
	ID = nID;
}

std::string Tag::getTriggerID() const {
	return triggerID;
}

void Tag::save() {
	std::stringstream valueSS;
	valueSS << mode << "," << name << "," << triggerID;
	writeLineToBuffer("Tags", ID, valueSS.str());
}

std::string Tag::getName() const
{
	return name;
}

void Tag::setName(std::string nName) {
	name = nName;
}
