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
	WriteValueToBuffer(ID, "Max", IntToStr(max), false);
	if(!tagID.empty()) {
		WriteValueToBuffer(ID, "Tag", tagID, false);
	}
	WriteValueToBuffer(ID, "Full", ConverBoolToYesNo(full), false);
	WriteValueToBuffer(ID, "Name", name, false);
	WriteValueToBuffer(ID, "Group", IntToStr(group), false);
	WriteValueToBuffer(ID, "House", house, false);
	WriteValueToBuffer(ID, "Script", scriptID, false);
	WriteValueToBuffer(ID, "Whiner", ConverBoolToYesNo(whiner), false);
	WriteValueToBuffer(ID, "Droppod", ConverBoolToYesNo(droppod), false);
	WriteValueToBuffer(ID, "Suicide", ConverBoolToYesNo(suicide), false);
	WriteValueToBuffer(ID, "Loadable", ConverBoolToYesNo(loadable), false);
	WriteValueToBuffer(ID, "Prebuild", ConverBoolToYesNo(prebuild), false);
	WriteValueToBuffer(ID, "Priority", IntToStr(priority), false);
	WriteValueToBuffer(ID, "Waypoint", wPoint, false);
	WriteValueToBuffer(ID, "Annoyance", ConverBoolToYesNo(annoyance), false);
	WriteValueToBuffer(ID, "IonImmune", ConverBoolToYesNo(ionimmune), false);
	WriteValueToBuffer(ID, "Recruiter", ConverBoolToYesNo(recruiter), false);
	WriteValueToBuffer(ID, "Reinforce", ConverBoolToYesNo(reinforce), false);
	WriteValueToBuffer(ID, "TaskForce", taskForceID, false);
	WriteValueToBuffer(ID, "TechLevel", IntToStr(techlevel), false);
	WriteValueToBuffer(ID, "Aggressive", ConverBoolToYesNo(aggressive), false);
	WriteValueToBuffer(ID, "Autocreate", ConverBoolToYesNo(autocreate), false);
	WriteValueToBuffer(ID, "GuardSlower", ConverBoolToYesNo(guardslower), false);
	WriteValueToBuffer(ID, "OnTransOnly", ConverBoolToYesNo(ontransonly), false);
	WriteValueToBuffer(ID, "AvoidThreats", ConverBoolToYesNo(avoidthreats), false);
	WriteValueToBuffer(ID, "LooseRecruit", ConverBoolToYesNo(looserecruit), false);
	WriteValueToBuffer(ID, "VeteranLevel", IntToStr(veteranlevel), false);
	WriteValueToBuffer(ID, "IsBaseDefense", ConverBoolToYesNo(isbasedefense), false);
	WriteValueToBuffer(ID, "OnlyTargetHouseEnemy", ConverBoolToYesNo(onlytargethousenemy), false);
	WriteValueToBuffer(ID, "TransportsReturnOnUnload", ConverBoolToYesNo(transportsreturnonunload), false);
	WriteValueToBuffer(ID, "AreTeamMembersRecruitable", ConverBoolToYesNo(areteammembersrecruitable), false);
}
