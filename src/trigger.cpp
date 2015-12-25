#include "trigger.h"

Trigger::Trigger(std::string newName)
{
	name = newName;
	ID = fffID();
	attachID = "<none>";
	house = "Neutral";
	isEasy = true;
	isMedium = true;
	isHard = true;
	isDis = false;
}

Trigger::Trigger(std::string nID, std::string nHouse, std::string newAttachID, std::string newName, bool nIsDis, bool newIsEas, bool newIsMed, bool newIsHar)
{
	name = newName;
	ID = nID;
	attachID = newAttachID;
	house = nHouse;
	isEasy = newIsEas;
	isMedium = newIsMed;
	isHard = newIsHar;
	isDis = nIsDis;

}

Trigger::Trigger(Trigger *otherTrigger)
{
	*this = *otherTrigger;
	setID(fffID());
	events.clear();
	for(eventIT IT = otherTrigger->events.begin(); IT != otherTrigger->events.end(); ++IT) {
		events.push_back(new Event(*IT, ID));
	}
	actions.clear();
	for(actionIT IT = otherTrigger->actions.begin(); IT != otherTrigger->actions.end(); ++IT) {
		actions.push_back(new Action(*IT, ID));
	}

}

Trigger::Trigger(std::string newID, Trigger *otherTrigger)
{
	*this = *otherTrigger;
	setID(newID);
	events.clear();
	for(eventIT IT = otherTrigger->events.begin(); IT != otherTrigger->events.end(); ++IT) {
		events.push_back(new Event(*IT, ID));
	}
	actions.clear();
	for(actionIT IT = otherTrigger->actions.begin(); IT != otherTrigger->actions.end(); ++IT) {
		actions.push_back(new Action(*IT, ID));
	}

}

Trigger::Trigger(std::string newID, std::string newName)
{
	name = newName;
	ID = newID;
	attachID = "<none>";
	house = "Neutral";
	isEasy = true;
	isMedium = true;
	isHard = true;
	isDis = false;
}

Trigger::~Trigger()
{
	eraseEventsFromBuffer();
	eraseActionsFromBuffer();
	for(eventIT IT = events.begin(); IT != events.end(); ++IT) {
		delete (*IT);
	}
	events.clear();
	for(actionIT IT = actions.begin(); IT != actions.end(); ++IT) {
		delete (*IT);
	}
	actions.clear();

	deleteLineFromBuffer("Triggers", ID);
}

std::string Trigger::getID() const {
	return ID;
}

void Trigger::setID(std::string newID) {
	ID = newID;
}

void Trigger::save() {

	std::stringstream valueSS;
	valueSS << house << "," << attachID << "," << name << "," << isDis << "," << isEasy << "," << isMedium << "," << isHard << "," << "0";
	writeLineToBuffer("Triggers", ID, valueSS.str());

	int i = 0;
	for(eventIT IT = events.begin(); IT != events.end(); ++IT) {
		i = i + 1;
		(*IT)->save(i);
	}
	i = 0;
	for(actionIT IT = actions.begin(); IT != actions.end(); ++IT) {
		i = i + 1;
		(*IT)->save(i);
	}

}

bool Trigger::isDisabled() const {
	return isDis;
}

QString Trigger::getName() const {
	return name.c_str();
}

void Trigger::setDis(bool dis) {
	isDis = dis;
}

void Trigger::setName(std::string nName) {
	name = nName;
}

void Trigger::addEvent(Event *nEvent) {
	events.push_back(nEvent);
}

void Trigger::addAction(Action *nAction) {
	actions.push_back((nAction));
}

void Trigger::eraseAction(int32_t count) {
	delete (*(actions.begin() + count));
	actions.erase(actions.begin() + count);
}

void Trigger::eraseEventByType(int32_t type)
{
	for(eventIT IT = events.begin(); IT != events.end(); ++IT) {
		if((*IT)->getType() == type) {
			delete *IT;
			events.erase(IT);
			return;
		}
	}
}

Action* Trigger::getAction(int32_t count) const {
	return *(actions.begin()+count);
}

void Trigger::eraseActionsFromBuffer() {
	deleteLineFromBuffer("Actions", ID);
}

void Trigger::eraseEventsFromBuffer() {
	deleteLineFromBuffer("Events", ID);
}

bool Trigger::hasEventType(int32_t type) {
	for(eventIT IT = events.begin(); IT != events.end(); ++IT) {
		if((*IT)->getType() == type) {
			return true;
		}
	}
	return false;
}

bool Trigger::hasActionType(int32_t type) {
	for(actionIT IT = actions.begin(); IT != actions.end(); ++IT) {
		if((*IT)->getType() == type) {
			return true;
		}
	}
	return false;
}

Action* Trigger::getActionByType(int32_t type) {
	for(actionIT IT = actions.begin(); IT != actions.end(); ++IT) {
		if((*IT)->getType() == type) {
			return *IT;
		}
	}
	return NULL;
}

Event* Trigger::getEventByType(int32_t type) {
	for(eventIT IT = events.begin(); IT != events.end(); ++IT) {
		if((*IT)->getType() == type) {
			return *IT;
		}
	}
	return NULL;
}
