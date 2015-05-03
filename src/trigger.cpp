#include "trigger.h"

Trigger::Trigger(string nName)
{
	name = nName;
	ID = fffID();
	attachID = "<none>";
	house = "Neutral";
	isEasy = true;
	isMedium = true;
	isHard = true;
	isDisabled = false;
}

Trigger::Trigger(string nID, string nHouse, string nAttachID, string nName, bool nIsDis, bool nIsEas, bool nIsMed, bool nIsHar)
{
	name = nName;
	ID = nID;
	attachID = nAttachID;
	house = nHouse;
	isEasy = nIsEas;
	isMedium = nIsMed;
	isHard = nIsHar;
	isDisabled = nIsDis;

}

Trigger::Trigger(Trigger *trig)
{
	*this = *trig;
	setID(fffID());
	events.clear();
	for(eventIT IT = trig->events.begin(); IT != trig->events.end(); ++IT) {
		events.push_back(new Event(*IT, ID));
	}
	actions.clear();
	for(actionIT IT = trig->actions.begin(); IT != trig->actions.end(); ++IT) {
		actions.push_back(new Action(*IT, ID));
	}

}

Trigger::Trigger(string nID, Trigger *trig)
{
	*this = *trig;
	setID(nID);
	events.clear();
	for(eventIT IT = trig->events.begin(); IT != trig->events.end(); ++IT) {
		events.push_back(new Event(*IT, ID));
	}
	actions.clear();
	for(actionIT IT = trig->actions.begin(); IT != trig->actions.end(); ++IT) {
		actions.push_back(new Action(*IT, ID));
	}

}

Trigger::Trigger(string nID, string nName)
{
	name = nName;
	ID = nID;
	attachID = "<none>";
	house = "Neutral";
	isEasy = true;
	isMedium = true;
	isHard = true;
	isDisabled = false;
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

	stringstream line;
	line << ID << "=" << house << "," << attachID << "," << name << "," << isDisabled << "," << isEasy << "," << isMedium << "," << isHard << "," << "0";
	DeleteValueInBuffer("Triggers", ID);
}

std::string Trigger::getID() {
	return ID;
}

void Trigger::setID(std::string nID) {
	ID = nID;
}

void Trigger::Save() {

	stringstream valueSS;
	valueSS << house << "," << attachID << "," << name << "," << isDisabled << "," << isEasy << "," << isMedium << "," << isHard << "," << "0";
	WriteValueToBuffer("Triggers", ID, valueSS.str());

	int i = 0;
	for(eventIT IT = events.begin(); IT != events.end(); ++IT) {
		i = i + 1;
		(*IT)->Save(i);
	}
	i = 0;
	for(actionIT IT = actions.begin(); IT != actions.end(); ++IT) {
		i = i + 1;
		(*IT)->Save(i);
	}

}

bool Trigger::isDis() {
	return isDisabled;
}

void Trigger::setDis(bool dis) {
	isDisabled = dis;
}

void Trigger::setName(string nName) {
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
		if((*IT)->eType == type) {
			delete *IT;
			events.erase(IT);
			return;
		}
	}
}

Action* Trigger::getAction(int32_t count) {
	return *(actions.begin()+count);
}

void Trigger::eraseActionsFromBuffer() {
	DeleteValueInBuffer("Actions", ID);
}

void Trigger::eraseEventsFromBuffer() {
	DeleteValueInBuffer("Events", ID);
}

bool Trigger::hasEventType(int32_t type) {
	for(eventIT IT = events.begin(); IT != events.end(); ++IT) {
		if((*IT)->eType == type) {
			return true;
		}
	}
	return false;
}

bool Trigger::hasActionType(int32_t type) {
	for(actionIT IT = actions.begin(); IT != actions.end(); ++IT) {
		if((*IT)->aType == type) {
			return true;
		}
	}
	return false;
}

Action* Trigger::getActionByType(int32_t type) {
	for(actionIT IT = actions.begin(); IT != actions.end(); ++IT) {
		if((*IT)->aType == type) {
			return *IT;
		}
	}
	return NULL;
}

Event* Trigger::getEventByType(int32_t type) {
	for(eventIT IT = events.begin(); IT != events.end(); ++IT) {
		if((*IT)->eType == type) {
			return *IT;
		}
	}
	return NULL;
}
