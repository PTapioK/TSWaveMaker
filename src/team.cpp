#include "team.h"


Team::Team(string nID, int nmax, string ntagID, bool nfull, string nname, int ngroup, string nhouse, string nscriptID, bool nwhiner, bool ndroppod, bool nsuicide, bool nloadable, bool nprebuild,
		   int nprioirity, string nwpoint, bool nannoyance, bool nionimmune, bool nrecruiter,
		   bool nreinforce, string ntaskforceid, int ntechlevel, bool naggressive, bool nautocreate, bool nguardslower, bool nontransonly, bool navoidthreats, bool
		   nlooserecruit, int nveteranlevel, bool nisbasedefense,
		   bool nonlytargethouseenemy, bool ntransportsreturnonunload, bool nareteammemberrecruitable) :
	ID(nID), max(nmax), tagID(ntagID), full(nfull), name(nname), group(ngroup), house(nhouse), scriptID(nscriptID), whiner(nwhiner), droppod(ndroppod), suicide(nsuicide),
	loadable(nloadable), prebuild(nprebuild), priority(nprioirity), wPoint(nwpoint), annoyance(nannoyance), ionimmune(nionimmune), recruiter(nrecruiter),
	reinforce(nreinforce), taskForceID(ntaskforceid), techlevel(ntechlevel), aggressive(naggressive), autocreate(nautocreate), guardslower(nguardslower),
	ontransonly(nontransonly), avoidthreats(navoidthreats), looserecruit(nlooserecruit), veteranlevel(nveteranlevel), isbasedefense(nisbasedefense),
	onlytargethousenemy(nonlytargethouseenemy), transportsreturnonunload(ntransportsreturnonunload), areteammembersrecruitable(nareteammemberrecruitable)
{
}

Team::Team(string nID, string nname) {
	ID = nID;
	max = 0;
	full = false;
	name = nname;
	group = -1;
	house = "Neutral";
	scriptID = "";
	whiner = false;
	droppod = false;
	suicide = false;
	loadable = false;
	prebuild = false;
	priority = 1;
	wPoint = "A";
	annoyance = false;
	ionimmune = false;
	recruiter = false;
	reinforce = false;
	taskForceID = "";
	techlevel = -1;
	aggressive = false;
	autocreate = false;
	guardslower = false;
	ontransonly = false;
	avoidthreats = false;
	looserecruit = false;
	veteranlevel = 1;
	isbasedefense = false;
	onlytargethousenemy = false;
	transportsreturnonunload = false;
	areteammembersrecruitable = true;
}

Team::Team(string nID, Team *nTeam)
{
	*this = *nTeam;
	this->ID = nID;
}

Team::~Team()
{
	DeleteSectionInBuffer(ID);
}

void Team::Save()
{
	WriteValueToBuffer(ID, "Max", IntToStr(max));
	if(!tagID.empty()) {
		WriteValueToBuffer(ID, "Tag", tagID);
	}
	WriteValueToBuffer(ID, "Full", ConverBoolToYesNo(full));
	WriteValueToBuffer(ID, "Name", name);
	WriteValueToBuffer(ID, "Group", IntToStr(group));
	WriteValueToBuffer(ID, "House", house);
	WriteValueToBuffer(ID, "Script", scriptID);
	WriteValueToBuffer(ID, "Whiner", ConverBoolToYesNo(whiner));
	WriteValueToBuffer(ID, "Droppod", ConverBoolToYesNo(droppod));
	WriteValueToBuffer(ID, "Suicide", ConverBoolToYesNo(suicide));
	WriteValueToBuffer(ID, "Loadable", ConverBoolToYesNo(loadable));
	WriteValueToBuffer(ID, "Prebuild", ConverBoolToYesNo(prebuild));
	WriteValueToBuffer(ID, "Priority", IntToStr(priority));
	WriteValueToBuffer(ID, "Waypoint", wPoint);
	WriteValueToBuffer(ID, "Annoyance", ConverBoolToYesNo(annoyance));
	WriteValueToBuffer(ID, "IonImmune", ConverBoolToYesNo(ionimmune));
	WriteValueToBuffer(ID, "Recruiter", ConverBoolToYesNo(recruiter));
	WriteValueToBuffer(ID, "Reinforce", ConverBoolToYesNo(reinforce));
	WriteValueToBuffer(ID, "TaskForce", taskForceID);
	WriteValueToBuffer(ID, "TechLevel", IntToStr(techlevel));
	WriteValueToBuffer(ID, "Aggressive", ConverBoolToYesNo(aggressive));
	WriteValueToBuffer(ID, "Autocreate", ConverBoolToYesNo(autocreate));
	WriteValueToBuffer(ID, "GuardSlower", ConverBoolToYesNo(guardslower));
	WriteValueToBuffer(ID, "OnTransOnly", ConverBoolToYesNo(ontransonly));
	WriteValueToBuffer(ID, "AvoidThreats", ConverBoolToYesNo(avoidthreats));
	WriteValueToBuffer(ID, "LooseRecruit", ConverBoolToYesNo(looserecruit));
	WriteValueToBuffer(ID, "VeteranLevel", IntToStr(veteranlevel));
	WriteValueToBuffer(ID, "IsBaseDefense", ConverBoolToYesNo(isbasedefense));
	WriteValueToBuffer(ID, "OnlyTargetHouseEnemy", ConverBoolToYesNo(onlytargethousenemy));
	WriteValueToBuffer(ID, "TransportsReturnOnUnload", ConverBoolToYesNo(transportsreturnonunload));
	WriteValueToBuffer(ID, "AreTeamMembersRecruitable", ConverBoolToYesNo(areteammembersrecruitable));
}
