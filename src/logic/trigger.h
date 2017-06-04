#ifndef TRIGGER_H
#define TRIGGER_H

#include "../main.h"

class Action;
class Event;
class Trigger
{
	public:
		std::vector <Action*> actions;
		std::vector <Event*> events;

		Trigger(QString newName);
		Trigger(QString newID, QString newHouse, QString newAttachID, QString newName,
				bool newIsDis, bool newIsEas, bool newIsMed, bool newIsHar, int16_t newUnknown = 0);
		Trigger(Trigger* otherTrigger);
		Trigger(QString newID, Trigger* otherTrigger);
		Trigger(QString newID, QString newName);
		~Trigger();

		void save();

		void setID(QString newID);
		void setDis(bool dis);
		void setName(QString nName);

		void addEvent(Event *nEvent);
		void addAction(Action *nAction);

		void eraseAction(int32_t actionID);
		void eraseEvent(int32_t eventID);
		void eraseEventByType(int32_t type);

		void eraseActionsFromBuffer();
		void eraseEventsFromBuffer();

		Action* getAction(size_t count) const;
		Action* getActionByType(int32_t type) const;

		Event* getEvent(size_t count) const;
		Event* getEventByType(int32_t type) const;

		bool hasEventType(int32_t type);
		bool hasActionType(int32_t type);

		QString getID() const;

		bool isDisabled() const;

		QString getName() const;
	private:
		QString name;
		QString house;
		QString ID;
		QString attachID;

		bool isDis;
		bool isEasy, isMedium, isHard;
		int16_t unknown;
};

#endif // TRIGGER_H
