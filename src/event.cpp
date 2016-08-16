#include "event.h"

Event::Event(QString newID)
{
	type = 0;
	param = "0";
	ID = newID;
	unknown = 0;
}

Event::Event(Event *otherEvent, QString newID) {
	type = otherEvent->type;
	param = otherEvent->param;
	ID = newID;
	unknown = 0;
}

Event::Event(int32_t newType, int32_t newParameter, QString newID, int16_t newUnknown)
{
	type = newType;
	param = QString::number(newParameter);
	ID = newID;
	unknown = newUnknown;
}

void Event::setParameter(QString parameter)
{
	param = parameter;
}

void Event::setType(int32_t newType)
{
	type = newType;
}

void Event::save(int32_t count) {
	if(count == 1) {
		QString str;
		QTextStream vSS(&str);
		vSS << count << "," << type << "," << unknown << "," << param;
		file.saveLineToBuffer("Events", ID, vSS.readAll());
	} else if (count > 1) {
		QString str;
		QTextStream vSS(&str);
		vSS << type << "," << unknown << "," << param;
		file.editCountableValueInBuffer("Events", ID, vSS.readAll(), count);
	}
}

QString Event::getParameter() const
{
	return param;
}

int32_t Event::getType() const
{
	return type;
}
