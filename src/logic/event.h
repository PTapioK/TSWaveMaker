#ifndef EVENT_H
#define EVENT_H

#include "../main.h"

class Event
{
	public:
		Event(QString newID);
		Event(Event* otherEvent, QString newID);
		Event(int32_t newType, int32_t newParameter, QString newID, int16_t newUnknown = 0);

		void setParameter(QString parameter);
		void setUnknown(int16_t parameter);
		void setType(int32_t newType);
		void save(int32_t count);

		QString getParameter() const;
		int32_t getType() const;
	private:
		int32_t type;
		QString param;
		QString ID;
		int16_t unknown;
};

#endif // EVENT_H
