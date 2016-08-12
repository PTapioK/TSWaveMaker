#include "tag.h"

Tag::Tag(QString tname, QString trigID)
{
	name = tname;
	ID = findFirstFreeID();
	triggerID = trigID;
	mode = 0;

}

Tag::Tag(Tag *oTag, QString trigID)
{
	*this = *oTag;
	setID(findFirstFreeID());
	triggerID = trigID;

}

Tag::Tag(QString nID, QString nName, QString nTrigID, int32_t nmode)
{
	ID = nID;
	name = nName;
	triggerID = nTrigID;
	mode = nmode;
}

Tag::~Tag()
{
	fileHandler.deleteLineFromBuffer("Tags", ID);
}

QString Tag::getID() const {
	return ID;
}

void Tag::setID(QString nID) {
	ID = nID;
}

QString Tag::getTriggerID() const {
	return triggerID;
}

void Tag::save() {
	QString str;
	QTextStream valueSS(&str);
	valueSS << mode << "," << name << "," << triggerID;
	fileHandler.writeLineToBuffer("Tags", ID, valueSS.readAll());
}

QString Tag::getName() const
{
	return name;
}

void Tag::setName(QString nName) {
	name = nName;
}
