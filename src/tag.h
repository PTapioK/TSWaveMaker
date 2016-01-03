#ifndef TAG_H
#define TAG_H

#include "main.h"

class Tag
{
	public:
		Tag(QString tname, QString trigID);
		Tag(Tag* oTag, QString trigID);
		Tag(QString nID, QString nName, QString nTrigID, int32_t nmode);
		~Tag();

		void setID(QString nID);
		void setName(QString nName);

		void save();

		QString getTriggerID() const;
		QString getName() const;
		QString getID() const;

	private:
		QString ID;
		QString name;
		QString triggerID;
		int32_t mode;
};

#endif // TAG_H
