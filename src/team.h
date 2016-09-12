#ifndef TEAM_H
#define TEAM_H

#include "main.h"

class Team
{
	public:
		Team(QString nID, int nmax, QString ntagid, bool nfull, QString nname, int ngroup, QString nhouse, QString nscriptID, bool nwhiner, bool ndroppod,
			 bool nsuicide, bool nloadable, bool nprebuild, int nprioirity, QString nwpoint, bool nannoyance, bool nionimmune,
			 bool nrecruiter, bool nreinforce, QString ntaskforceid, int ntechlevel, bool naggressive, bool nautocreate, bool nguardslower, bool nontransonly,
			 bool navoidthreats, bool nlooserecruit, int nveteranlevel, bool nisbasedefense, bool nonlytargethouseenemy, bool ntransportsreturnonunload,
			 bool nareteammemberrecruitable);
		Team(QString nID, QString nName = "New Team");
		Team(QString nID, Team* nTeam);
		~Team();

		void setName(QString newName);
		void setHouse(QString newHouse);

		void save();

		QString getName() const;
		QString getID() const;
		QString getHouse() const;
	private:
		friend class TeamSection;

		QString ID;
		int max;
		QString tagID;
		bool full;
		QString name;
		int group;
		QString house;
		QString scriptID;
		bool whiner;
		bool droppod;
		bool suicide;
		bool loadable;
		bool prebuild;
		int priority;
		QString wPoint;
		bool annoyance;
		bool ionimmune;
		bool recruiter;
		bool reinforce;
		QString taskForceID;
		int techlevel;
		bool aggressive;
		bool autocreate;
		bool guardslower;
		bool ontransonly;
		bool avoidthreats;
		bool looserecruit;
		int veteranlevel;
		bool isbasedefense;
		bool onlytargethousenemy;
		bool transportsreturnonunload;
		bool areteammembersrecruitable;

		QString convertBoolToYesNo(bool boolean);
};

#endif // TEAM_H
