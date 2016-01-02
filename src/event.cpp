#include "event.h"

Event::Event(std::string newID)
{
	type = 0;
	param = "0";
	ID = newID;
	unknown = 0;
}

Event::Event(Event *otherEvent, std::string newID) {
	type = otherEvent->type;
	param = otherEvent->param;
	ID = newID;
	unknown = 0;
}

Event::Event(int32_t newType, int32_t newParameter, std::string newID, int16_t newUnknown)
{
	type = newType;
	param = intToStr(newParameter);
	ID = newID;
	unknown = newUnknown;
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
		vSS << count << "," << type << "," << unknown << "," << param;
		writeLineToBuffer("Events", ID, vSS.str());
	} else if (count > 1) {
		std::stringstream vSS;
		vSS << type << "," << unknown << "," << param;
		editCountableValueInBuffer("Events", ID, vSS.str(), count);
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
