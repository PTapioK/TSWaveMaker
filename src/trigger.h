#ifndef TRIGGER_H
#define TRIGGER_H

#include "main.h"

struct Action;
struct Event;
class Trigger
{
public:

	std::vector <Action*> actions;
	std::vector <Event*> events;

	Trigger(string nName);
	Trigger(string nID, string nHouse, string nAttachID, string nName, bool nIsDis, bool nIsEas, bool nIsMed, bool nIsHar);
	Trigger(Trigger* trig);
	~Trigger();

	std::string getID();
	void setID(std::string nID);

	void WriteToFile();

	bool isDis();
	void setDis(bool dis);

	void setName(string nName);

	void addEvent(Event *nEvent);
	void addAction(Action *nAction);

	void eraseAction(int32_t count);
	void eraseActionsFromBuffer();

	void eraseEventsFromBuffer();

	Action* getAction(int32_t count);
	Action* getActionByType(int32_t type);

	bool hasEventType(int32_t type);
	bool hasActionType(int32_t type);

private:
	std::string name;
	std::string house;
	std::string ID;
	std::string attachID;

	bool isDisabled;
	bool isEasy, isMedium, isHard;

};

#endif // TRIGGER_H
