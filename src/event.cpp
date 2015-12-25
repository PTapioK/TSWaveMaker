#include "event.h"

Event::Event(std::string newID)
{
	type = 0;
	param = "0";
	ID = newID;
}

Event::Event(Event *otherEvent, std::string newID) {
	type = otherEvent->type;
	param = otherEvent->param;
	ID = newID;
}

Event::Event(int32_t newType, int32_t newParameter, std::string newID)
{
	type = newType;
	param = intToStr(newParameter);
	ID = newID;
}

void Event::setParameter(std::string parameter)
{
	param = parameter;
}

void Event::setType(int32_t newType)
{
	type = newType;
}

void Event::save(int32_t count) {
	if(count == 1) {
		std::stringstream vSS;
		vSS << count << "," << type << "," << "0" << "," << param;
		writeLineToBuffer("Events", ID, vSS.str());
	} else if (count > 1) {
		std::stringstream vSS;
		vSS << type << "," << "0" << "," << param;
		editValueInBuffer("Events", ID, vSS.str(), count);
	}
}

std::string Event::getParameter() const
{
	return param;
}

int32_t Event::getType() const
{
	return type;
}
