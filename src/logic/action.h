#ifndef ACTION_H
#define ACTION_H

#include "../main.h"

class Action
{
	public:
		Action(QString newID);
		Action(Action *otherAction, QString newID);
		Action(QString newID, int32_t newType, int32_t newWaypoint);
		Action(QString newID, int32_t newType, std::array<QString, 6> newParameters, QString newWaypoint);
		Action(QString newID, int32_t newType, int32_t newWaypoint,
			   QString parameter1, QString parameter2, QString parameter3,
			   QString parameter4, QString parameter5, QString parameter6);

		void save(int32_t count);

		void setType(int32_t newType);
		void setWaypoint(int32_t newWaypoint);

		void setParameter(uint8_t i, QString data);
		void setParameter(uint8_t i, int32_t data);
		void setParameters(std::array<QString, 6> newParameters);

		int32_t getType() const;
		int32_t getWaypoint() const;
		QString getParameter(uint8_t i) const;
		std::array<QString, 6> getParameters() const;

	private:
		QString ID;
		int32_t type;
		std::array<QString, 6> params;
		QString waypoint;
};

#endif // ACTION_H
