#include "tag.h"

Tag::Tag(QString newName, QString trigID)
{
	name = newName;
	ID = findFirstFreeID();
	triggerID = trigID;
	mode = 0;
}

Tag::Tag(QString newName, QString trigID, QString newID)
{
	name = newName;
	ID = newID;
	triggerID = trigID;
	mode = 0;
}

Tag::Tag(Tag *otherTag, QString trigID)
{
	*this = *otherTag;
	setID(findFirstFreeID());
	triggerID = trigID;
}

Tag::Tag(Tag *otherTag, QString trigID, QString newID, QString newName)
{
	*this = *otherTag;
	setID(newID);
	triggerID = trigID;
	name = newName;
}

Tag::Tag(QString newID, QString newName, QString trigID, int32_t newMode)
{
	ID = newID;
	name = newName;
	triggerID = trigID;
	mode = newMode;
}

Tag::~Tag()
{
	file.deleteLineFromBuffer("Tags", ID);
}

void Tag::setID(QString newID) {
	ID = newID;
}

void Tag::setName(QString newName) {
	name = newName;
}

void Tag::setMode(int16_t newMode)
{
	mode = newMode;
}

void Tag::save() const {
	QString str;
	QTextStream valueSS(&str);
	valueSS << mode << "," << name << "," << triggerID;
	file.saveLineToBuffer("Tags", ID, valueSS.readAll());
}

QString Tag::getID() const {
	return ID;
}

int16_t Tag::getMode() const
{
	return mode;
}

QString Tag::getTriggerID() const {
	return triggerID;
}

QString Tag::getName() const
{
	return name;
}
