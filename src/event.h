#ifndef EVENT_H
#define EVENT_H

#include "main.h"

struct Event
{
	Event(string nID);
	Event(Event* oEvent, string nID);
	Event(int32_t neType, int32_t nparam, string nID);

	int32_t eType;
	string param;
	string ID;

	void WriteToFile(int32_t count);
};

#endif // EVENT_H
