#ifndef TEAM_H
#define TEAM_H

#include "main.h"

class Team
{
public:
	Team(string nID, int nmax, string ntagid, bool nfull, string nname, int ngroup, string nhouse, string nscriptID, bool nwhiner, bool ndroppod,
		 bool nsuicide, bool nloadable, bool nprebuild, int nprioirity, string nwpoint, bool nannoyance, bool nionimmune,
		 bool nrecruiter, bool nreinforce, string ntaskforceid, int ntechlevel, bool naggressive, bool nautocreate, bool nguardslower, bool nontransonly,
		 bool navoidthreats, bool nlooserecruit, int nveteranlevel, bool nisbasedefense, bool nonlytargethouseenemy, bool ntransportsreturnonunload,
		 bool nareteammemberrecruitable);
	Team(string nID, string nname = "New Team");
	Team(string nID, Team* nTeam);

	string getName() { return name; }
	string getID() { return ID; }

	void setName(string nname) { name = nname; }

	void WriteToFile();

private:

	friend class TeamSection;

	std::string ID;
	int max;
	string tagID;
	bool full;
	string name;
	int group;
	string house;
	string scriptID;
	bool whiner;
	bool droppod;
	bool suicide;
	bool loadable;
	bool prebuild;
	int priority;
	string wPoint;
	bool annoyance;
	bool ionimmune;
	bool recruiter;
	bool reinforce;
	string taskForceID;
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
