#ifndef EVENT_H
#define EVENT_H

#include "main.h"

class Event
{
	public:
		Event(std::string newID);
		Event(Event* otherEvent, std::string newID);
		Event(int32_t newType, int32_t newParameter, std::string newID);

		void setParameter(std::string parameter);
		void setType(int32_t newType);
		void save(int32_t count);

		std::string getParameter() const;
		int32_t getType() const;
	private:
		int32_t type;
		std::string param;
		std::string ID;
};

#endif // EVENT_H
