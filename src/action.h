#ifndef ACTION_H
#define ACTION_H

#include "main.h"

struct Action
{
	Action(string nID);
	Action(string nID, int32_t naType, int32_t nwPoint, int32_t pa1, int32_t pa2, int32_t pa3, int32_t pa4, int32_t pa5, int32_t pa6);
	Action(string nID, int32_t naType, int32_t nwPoint, int32_t pa1, string pa2, int32_t pa3, int32_t pa4, int32_t pa5, int32_t pa6);
	Action(Action *oAct, string nID);

	void WriteToFile(int32_t count);

	void editType(int32_t type);
	void editWPoint(int32_t wayP);
	void editP1(int32_t pa1);
	void editP2(int32_t pa2);
	void editP2(string pa2);
	void editP3(int32_t pa3);
	void editP4(int32_t pa4);
	void editP5(int32_t pa5);
	void editP6(int32_t pa6);

	int32_t getType();
	int32_t getWaypoint();

	string getP2();

	string ID;
	int32_t aType;
	string p1, p2, p3, p4, p5, p6;
	string wPoint;
};

#endif // ACTION_H
