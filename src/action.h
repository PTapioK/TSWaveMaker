#ifndef ACTION_H
#define ACTION_H

#include "main.h"

class Action
{
	public:
		Action(std::string newID);
		Action(Action *otherAction, std::string newID);
		Action(std::string newID, int32_t newType, int32_t newWayPoint);
		Action(std::string newID, int32_t newType, std::array<std::string, 6> newParameters, int32_t newWaypoint);
		Action(std::string newID, int32_t newType, int32_t newWayPoint,
			   std::string parameter1, std::string parameter2, std::string parameter3, std::string parameter4, std::string parameter5, std::string parameter6);

		void save(int32_t count);

		void setType(int32_t newType);
		void setWayPoint(int32_t newWaypoint);

		void setParameter(int i, std::string data);
		void setParameter(int i, int32_t data);

		int32_t getType() const;
		int32_t getWaypoint() const;
		std::string getParameter(int i) const;

	private:
		std::string ID;
		int32_t type;
		std::array<std::string, 6> params;
		std::string waypoint;
};

#endif // ACTION_H
