#include "trigger.h"

Trigger::Trigger(QString newName)
{
	name = newName;
	ID = findFirstFreeID();
	attachID = "<none>";
	house = "Neutral";
	isEasy = true;
	isMedium = true;
	isHard = true;
	isDis = false;
	unknown = 0;
}

Trigger::Trigger(QString nID, QString nHouse, QString newAttachID, QString newName,
				 bool newIsDis, bool newIsEas, bool newIsMed, bool newIsHar, int16_t newUnknown)
{
	name = newName;
	ID = nID;
	attachID = newAttachID;
	house = nHouse;
	isEasy = newIsEas;
	isMedium = newIsMed;
	isHard = newIsHar;
	isDis = newIsDis;
	unknown = newUnknown;
}

Trigger::Trigger(Trigger *otherTrigger)
{
	*this = *otherTrigger;
	setID(findFirstFreeID());
	events.clear();
	for(auto IT = otherTrigger->events.begin(); IT != otherTrigger->events.end(); ++IT) {
		events.push_back(new Event(*IT, ID));
	}
	actions.clear();
	for(auto IT = otherTrigger->actions.begin(); IT != otherTrigger->actions.end(); ++IT) {
		actions.push_back(new Action(*IT, ID));
	}

}

Trigger::Trigger(QString newID, Trigger *otherTrigger)
{
	*this = *otherTrigger;
	setID(newID);
	events.clear();
	for(auto IT = otherTrigger->events.begin(); IT != otherTrigger->events.end(); ++IT) {
		events.push_back(new Event(*IT, ID));
	}
	actions.clear();
	for(auto IT = otherTrigger->actions.begin(); IT != otherTrigger->actions.end(); ++IT) {
		actions.push_back(new Action(*IT, ID));
	}

}

Trigger::Trigger(QString newID, QString newName)
{
	name = newName;
	ID = newID;
	attachID = "<none>";
	house = "Neutral";
	isEasy = true;
	isMedium = true;
	isHard = true;
	isDis = false;
	unknown = 0;
}

Trigger::~Trigger()
{
	eraseEventsFromBuffer();
	eraseActionsFromBuffer();
	for(auto IT = events.begin(); IT != events.end(); ++IT) {
		delete (*IT);
	}
	events.clear();
	for(auto IT = actions.begin(); IT != actions.end(); ++IT) {
		delete (*IT);
	}
	actions.clear();

	file.deleteLineFromBuffer("Triggers", ID);
}

QString Trigger::getID() const
{
	return ID;
}

QString Trigger::getAttachedTriggerID() const
{
	return attachID;
}

void Trigger::setID(QString newID)
{
	ID = newID;
}

void Trigger::save()
{
	QString str;
	QTextStream valueSS(&str);
	valueSS << house << "," << attachID << "," << name << "," << isDis << "," << isEasy << "," << isMedium << "," << isHard << "," << unknown;
	file.saveLineToBuffer("Triggers", ID, valueSS.readAll());

	int i = 0;
	for(auto IT = events.begin(); IT != events.end(); ++IT) {
		i = i + 1;
		(*IT)->save(i);
	}
	i = 0;
	for(auto IT = actions.begin(); IT != actions.end(); ++IT) {
		i = i + 1;
		(*IT)->save(i);
	}
}

bool Trigger::isDisabled() const
{
	return isDis;
}

QString Trigger::getName() const
{
	return name;
}

void Trigger::setDis(bool dis)
{
	isDis = dis;
}

void Trigger::setName(QString nName)
{
	name = nName;
}

void Trigger::setHouse(QString nHouse)
{
	house = nHouse;
}

void Trigger::setAttachedTriggerID(QString nAttachedID)
{
	attachID = nAttachedID;
}

void Trigger::addEvent(Event *nEvent)
{
	events.push_back(nEvent);
}

void Trigger::addAction(Action *nAction)
{
	actions.push_back((nAction));
}

void Trigger::eraseAction(int32_t actionID)
{
	delete (*(actions.begin() + actionID));
	actions.erase(actions.begin() + actionID);
}

void Trigger::eraseEvent(int32_t eventID)
{
	delete (*(events.begin() + eventID));
	events.erase(events.begin() + eventID);
}

void Trigger::eraseEventByType(int32_t type)
{
	for(auto IT = events.begin(); IT != events.end(); ++IT) {
		if((*IT)->getType() == type) {
			delete *IT;
			events.erase(IT);
			return;
		}
	}
}

Action* Trigger::getAction(size_t count) const
{
	return *(actions.begin()+count);
}

Event *Trigger::getEvent(size_t count) const
{
	return *(events.begin()+count);
}

Action* Trigger::getActionByType(int32_t type) const
{
	for(auto IT = actions.begin(); IT != actions.end(); ++IT) {
		if((*IT)->getType() == type) {
			return *IT;
		}
	}
	return NULL;
}

Event* Trigger::getEventByType(int32_t type) const
{
	for(auto IT = events.begin(); IT != events.end(); ++IT) {
		if((*IT)->getType() == type) {
			return *IT;
		}
	}
	return NULL;
}

void Trigger::eraseActionsFromBuffer()
{
	file.deleteLineFromBuffer("Actions", ID);
}

void Trigger::eraseEventsFromBuffer()
{
	file.deleteLineFromBuffer("Events", ID);
}

bool Trigger::hasEventType(int32_t type)
{
	for(auto IT = events.begin(); IT != events.end(); ++IT) {
		if((*IT)->getType() == type) {
			return true;
		}
	}
	return false;
}

bool Trigger::hasActionType(int32_t type)
{
	for(auto IT = actions.begin(); IT != actions.end(); ++IT) {
		if((*IT)->getType() == type) {
			return true;
		}
	}
	return false;
}

QString Trigger::getHouse() const
{
	return house;
}
