#ifndef TASKFORCE_H
#define TASKFORCE_H

#include "main.h"

class Taskforce
{
	public:
		Taskforce(std::string nID);
		Taskforce(std::string nID, std::string nName);
		Taskforce(std::string nID, Taskforce *tF);
		~Taskforce();

		void addLine(std::string type, short amount);
		void deleteLine(short lineID);

		void setGroup(int32_t nGroup) { group = nGroup; }
		void setName(std::string nName) { name = nName; }

		void save();

		std::string getID() const;

		std::string getName() const;

		uint16_t getLineAmount() const;

	private:

		friend class TaskforceSection;

		std::string ID;

		std::string name;
		int32_t group;

		struct TaskforceLine
		{
			std::string type;
			short amount;

			short ID;
		};

		std::vector <TaskforceLine*> tlines;
		typedef std::vector <TaskforceLine*>::iterator tlineIT;

		uint16_t lineCounter;

};

#endif // TASKFORCE_H
