#ifndef TAG_H
#define TAG_H

#include "main.h"

class Tag
{
	public:
		Tag(std::string tname, std::string trigID);
		Tag(Tag* oTag, std::string trigID);
		Tag(std::string nID, std::string nName, std::string nTrigID, int32_t nmode);
		~Tag();

		void setID(std::string nID);
		void setName(std::string nName);

		void save();

		std::string getTriggerID() const;
		std::string getName() const;
		std::string getID() const;

	private:
		std::string ID;
		std::string name;
		std::string triggerID;
		int32_t mode;
};

#endif // TAG_H
