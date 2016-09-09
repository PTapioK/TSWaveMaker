#include "action.h"

Action::Action(QString newID)
{
	ID = newID;
	type = 0;
	waypoint = decToWaypointID(0);
	params.fill("0");
}

Action::Action(QString newID, int32_t newType, int32_t newWaypoint = 0)
{
	ID = newID;
	type = newType;
	waypoint = decToWaypointID(newWaypoint);
	params.fill("0");
}

Action::Action(QString newID, int32_t newType, int32_t newWaypoint,
			   QString parameter1, QString parameter2, QString parameter3,
			   QString parameter4, QString parameter5, QString parameter6)
{
	ID = newID;
	type = newType;
	waypoint = decToWaypointID(newWaypoint);
	params[0] = parameter1;
	params[1] = parameter2;
	params[2] = parameter3;
	params[3] = parameter4;
	params[4] = parameter5;
	params[5] = parameter6;
}

Action::Action(QString newID, int32_t newType, std::array<QString, 6> newParameters, int32_t newWaypoint = 0)
{
	ID = newID;
	type = newType;
	waypoint = decToWaypointID(newWaypoint);
	params = newParameters;
}

Action::Action(Action *otherAction, QString newID)
{
	*this = *otherAction;
	ID = newID;
}

void Action::save(int32_t count)
{
	if(count == 1) {
		QString str;
		QTextStream valueSS(&str);
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
		file.saveLineToBuffer("Actions", ID, valueSS.readAll());
	} else if (count > 1) {
		QString str;
		QTextStream valueSS(&str);
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
		file.editCountableValueInBuffer("Actions", ID, valueSS.readAll(), count);
	}
}

void Action::setType(int32_t newType)
{
	type = newType;
}

void Action::setWaypoint(int32_t newWaypoint)
{
	waypoint = decToWaypointID(newWaypoint);
}

void Action::setParameter(uint8_t i, QString data)
{
	assert(i < 6);
	params[i] = data;
}

void Action::setParameter(uint8_t i, int32_t data)
{
	assert(i < 6);
	params[i] = QString::number(data);
}

void Action::setParameters(std::array<QString, 6> newParameters)
{
	params = newParameters;
}

int32_t Action::getType() const
{
	return type;
}

int32_t Action::getWaypoint() const
{
	return waypointIDToDec(waypoint);
}

QString Action::getParameter(uint8_t i) const
{
	assert(i < 6);
	return params[i];
}

std::array<QString, 6> Action::getParameters() const
{
	return params;
}
