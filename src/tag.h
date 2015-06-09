#ifndef TAG_H
#define TAG_H

#include "main.h"

class Tag
{
public:
	Tag(std::string tname, string trigID);
	Tag(Tag* oTag, string trigID);
	Tag(string nID, string nName, string nTrigID, int32_t nmode);
	~Tag();

	string getID();
	void setID(string nID);
	string getTriggerID();
	string getName() { return name; }

	void Save();

	void setName(string nName);

private:
	std::string ID;
	std::string name;
	std::string triggerID;
	int32_t mode;
};

#endif // TAG_H
