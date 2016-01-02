#ifndef TRIGGER_H
#define TRIGGER_H

#include "main.h"

class Action;
class Event;
class Trigger
{
	public:

		std::vector <Action*> actions;
		std::vector <Event*> events;

		Trigger(std::string newName);
		Trigger(std::string newID, std::string newHouse, std::string newAttachID, std::string newName, bool newIsDis, bool newIsEas, bool newIsMed, bool newIsHar, int16_t newUnknown = 0);
		Trigger(Trigger* otherTrigger);
		Trigger(std::string newID, Trigger* otherTrigger);
		Trigger(std::string newID, std::string newName);
		~Trigger();

		void setID(std::string newID);

		void save();

		void setDis(bool dis);

		void setName(std::string nName);

		void addEvent(Event *nEvent);
		void addAction(Action *nAction);

		void eraseAction(int32_t count);

		void eraseEventByType(int32_t type);

		void eraseActionsFromBuffer();
		void eraseEventsFromBuffer();

		Action* getAction(int32_t count) const;
		Action* getActionByType(int32_t type);

		bool hasEventType(int32_t type);
		bool hasActionType(int32_t type);

		Event* getEventByType(int32_t type);

		std::string getID() const;

		bool isDisabled() const;

		QString getName() const;

	private:
		std::string name;
		std::string house;
		std::string ID;
		std::string attachID;

		bool isDis;
		bool isEasy, isMedium, isHard;
		int16_t unknown;

};

#endif // TRIGGER_H
