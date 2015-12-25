#include "action.h"

Action::Action(std::string newID)
{
	ID = newID;
	type = 0;
	waypoint = decToWaypointID(0);
	params.fill("0");
}

Action::Action(std::string newID, int32_t newType, int32_t newWayPoint = 0)
{
	ID = newID;
	type = newType;
	waypoint = decToWaypointID(newWayPoint);
}

Action::Action(std::string newID, int32_t newType, int32_t newWayPoint, std::string parameter1, std::string parameter2, std::string parameter3, std::string parameter4, std::string parameter5, std::string parameter6)
{
	ID = newID;
	type = newType;
	waypoint = decToWaypointID(newWayPoint);
	params[0] = parameter1;
	params[1] = parameter2;
	params[2] = parameter3;
	params[3] = parameter4;
	params[4] = parameter5;
	params[5] = parameter6;
}

Action::Action(std::string newID, int32_t newType, std::array<std::string, 6> newParameters, int32_t newWaypoint = 0)
{
	ID = newID;
	type = newType;
	waypoint = decToWaypointID(newWaypoint);
	params = newParameters;
}

Action::Action(Action *otherAction, std::string newID)
{
	*this = *otherAction;
	ID = newID;
}

void Action::save(int32_t count) {
	if(count == 1) {
		std::stringstream valueSS;
		valueSS << count
				<< ","
				<< type
				<< ","
				<< params[0]
				<< ","
				<< params[1]
				<< ","
				<< params[2]
				<< ","
				<< params[3]
				<< ","
				<< params[4]
				<< ","
				<< params[5]
				<< ","
				<< waypoint;
		writeLineToBuffer("Actions", ID, valueSS.str());
	} else if (count > 1) {
		std::stringstream valueSS;
		valueSS	<< type
				<< ","
				<< params[0]
				<< ","
				<< params[1]
				<< ","
				<< params[2]
				<< ","
				<< params[3]
				<< ","
				<< params[4]
				<< ","
				<< params[5]
				<< ","
				<< waypoint;
		editValueInBuffer("Actions", ID, valueSS.str(), count);
	}
}

void Action::setType(int32_t newType) {
	type = newType;
}

void Action::setWayPoint(int32_t newWaypoint) {
	waypoint = decToWaypointID(newWaypoint);
}

void Action::setParameter(int i, std::string data)
{
	assert(i > 0 && i < 6);
	params[i-1] = data;
}

void Action::setParameter(int i, int32_t data)
{
	assert(i > 0 && i < 6);
	params[i-1] = intToStr(data);
}

int32_t Action::getType() const {
	return type;
}

int32_t Action::getWaypoint() const {
	return waypointIDToDec(waypoint);
}

std::string Action::getParameter(int i) const {
	assert(i > 0 && i < 6);
	return params[i-1];
}
