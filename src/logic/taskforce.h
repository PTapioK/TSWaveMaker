#ifndef TASKFORCE_H
#define TASKFORCE_H

#include "../main.h"

class Taskforce
{
	public:
		Taskforce(QString nID);
		Taskforce(QString nID, QString nName);
		Taskforce(QString nID, Taskforce *tF);
		~Taskforce();

		void addLine(QString type, uint16_t amount);
		void deleteLine(uint16_t lineID);

		void setGroup(int32_t nGroup) { group = nGroup; }
		void setName(QString nName) { name = nName; }

		void save();

		QString getID() const;

		QString getName() const;

		uint16_t getLineAmount() const;
	private:
		friend class TaskforceSection;

		QString ID;

		QString name;
		int32_t group;

		struct TaskforceLine
		{
			QString type;
			uint16_t amount;

			uint16_t ID;
		};

		std::vector <TaskforceLine*> taskforceLines;
		typedef std::vector <TaskforceLine*>::iterator taskforceLineIT;

		uint16_t lineCounter;
};

#endif // TASKFORCE_H
