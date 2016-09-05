#ifndef TAG_H
#define TAG_H

#include "main.h"

class Tag
{
	public:
		Tag(QString newName, QString trigID);
		Tag(QString newName, QString trigID, QString newID);
		Tag(Tag* otherTag, QString trigID);
		Tag(Tag* otherTag, QString trigID, QString newID, QString newName);
		Tag(QString newID, QString newName, QString trigID, int32_t newMode);
		~Tag();

		void setID(QString newID);
		void setName(QString newName);
		void setMode(int16_t newMode);
		void save() const;

		QString getTriggerID() const;
		QString getName() const;
		QString getID() const;
		int16_t getMode() const;
	private:
		QString ID;
		QString name;
		QString triggerID;
		int16_t mode;
};

#endif // TAG_H
