#ifndef TEAM_H
#define TEAM_H

#include "main.h"

class Team
{
	public:
		Team(std::string nID, int nmax, std::string ntagid, bool nfull, std::string nname, int ngroup, std::string nhouse, std::string nscriptID, bool nwhiner, bool ndroppod,
			 bool nsuicide, bool nloadable, bool nprebuild, int nprioirity, std::string nwpoint, bool nannoyance, bool nionimmune,
			 bool nrecruiter, bool nreinforce, std::string ntaskforceid, int ntechlevel, bool naggressive, bool nautocreate, bool nguardslower, bool nontransonly,
			 bool navoidthreats, bool nlooserecruit, int nveteranlevel, bool nisbasedefense, bool nonlytargethouseenemy, bool ntransportsreturnonunload,
			 bool nareteammemberrecruitable);
		Team(std::string nID, std::string nname = "New Team");
		Team(std::string nID, Team* nTeam);
		~Team();

		void setName(std::string newName);

		void save();

		std::string getName() const;
		std::string getID() const;

	private:

		friend class TeamSection;

		std::string ID;
		int max;
		std::string tagID;
		bool full;
		std::string name;
		int group;
		std::string house;
		std::string scriptID;
		bool whiner;
		bool droppod;
		bool suicide;
		bool loadable;
		bool prebuild;
		int priority;
		std::string wPoint;
		bool annoyance;
		bool ionimmune;
		bool recruiter;
		bool reinforce;
		std::string taskForceID;
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

};

#endif // TEAM_H
