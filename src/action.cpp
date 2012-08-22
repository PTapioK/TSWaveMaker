#include "action.h"

Action::Action(string nID)
{
	ID = nID;
	aType = 0;
	wPoint = DecToWaypointID(0);
	p1 = "0";
	p2 = "0";
	p3 = "0";
	p4 = "0";
	p5 = "0";
	p6 = "0";
}

Action::Action(string nID, int32_t naType, int32_t nwPoint = 0, int32_t pa1 = 0, int32_t pa2 = 0, int32_t pa3 = 0, int32_t pa4 = 0, int32_t pa5 = 0, int32_t pa6 = 0)
{
	ID = nID;
	aType = naType;
	wPoint = DecToWaypointID(nwPoint);
	editP1(pa1);
	editP2(pa2);
	editP3(pa3);
	editP4(pa4);
	editP5(pa5);
	editP6(pa6);

}

Action::Action(string nID, int32_t naType, int32_t nwPoint = 0, int32_t pa1 = 0, string pa2 = 0, int32_t pa3 = 0, int32_t pa4 = 0, int32_t pa5 = 0, int32_t pa6 = 0)
{
	ID = nID;
	aType = naType;
	wPoint = DecToWaypointID(nwPoint);
	editP1(pa1);
	editP2(pa2);
	editP3(pa3);
	editP4(pa4);
	editP5(pa5);
	editP6(pa6);

}

Action::Action(Action *oAct, string nID)
{
	*this = *oAct;
	ID = nID;
}

void Action::WriteToFile(int32_t count) {
	if(count == 1) {
		stringstream vSS;
		vSS << count
			<< ","
			<< aType
			<< ","
			<< p1
			<< ","
			<< p2
			<< ","
			<< p3
			<< ","
			<< p4
			<< ","
			<< p5
			<< ","
			<< p6
			<< ","
			<< wPoint;
		WriteToFileBuffer("[Actions]", ID, vSS.str());
	} else if (count > 1) {
		stringstream vSS;
		vSS	<< aType
			<< ","
			<< p1
			<< ","
			<< p2
			<< ","
			<< p3
			<< ","
			<< p4
			<< ","
			<< p5
			<< ","
			<< p6
			<< ","
			<< wPoint;
		AddToFileBuffer("[Actions]", ID, vSS.str(), count);
	}
}

void Action::editType(int32_t type) {
	aType = type;
}

void Action::editWPoint(int32_t wayP) {
	wPoint = DecToWaypointID(wayP);
}

void Action::editP1(int32_t pa1) {
	stringstream ss;
	ss << pa1;
	p1 = ss.str();
}

void Action::editP2(int32_t pa2) {
	stringstream ss;
	ss << pa2;
	p2 = ss.str();
}

void Action::editP2(string pa2) {
	p2 = pa2;
}

void Action::editP3(int32_t pa3) {
	stringstream ss;
	ss << pa3;
	p3 = ss.str();
}

void Action::editP4(int32_t pa4) {
	stringstream ss;
	ss << pa4;
	p4 = ss.str();
}

void Action::editP5(int32_t pa5) {
	stringstream ss;
	ss << pa5;
	p5 = ss.str();
}

void Action::editP6(int32_t pa6) {
	stringstream ss;
	ss << pa6;
	p6 = ss.str();
}

int32_t Action::getType() {
	return aType;
}

int32_t Action::getWaypoint() {
	return WaypointIDToDec(wPoint);
}

string Action::getP2() {
	return p2;
}
