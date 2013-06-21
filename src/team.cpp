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

void Team::WriteToFile()
{
	WriteToFileBuffer("[" + ID + "]", "Max", IntToStr(max), false);
	if(!tagID.empty()) {
		WriteToFileBuffer("[" + ID + "]", "Tag", tagID, false);
	}
	WriteToFileBuffer("[" + ID + "]", "Full", ConverBoolToYesNo(full), false);
	WriteToFileBuffer("[" + ID + "]", "Name", name, false);
	WriteToFileBuffer("[" + ID + "]", "Group", IntToStr(group), false);
	WriteToFileBuffer("[" + ID + "]", "House", house, false);
	WriteToFileBuffer("[" + ID + "]", "Script", scriptID, false);
	WriteToFileBuffer("[" + ID + "]", "Whiner", ConverBoolToYesNo(whiner), false);
	WriteToFileBuffer("[" + ID + "]", "Droppod", ConverBoolToYesNo(droppod), false);
	WriteToFileBuffer("[" + ID + "]", "Suicide", ConverBoolToYesNo(suicide), false);
	WriteToFileBuffer("[" + ID + "]", "Loadable", ConverBoolToYesNo(loadable), false);
	WriteToFileBuffer("[" + ID + "]", "Prebuild", ConverBoolToYesNo(prebuild), false);
	WriteToFileBuffer("[" + ID + "]", "Priority", IntToStr(priority), false);
	WriteToFileBuffer("[" + ID + "]", "Waypoint", wPoint, false);
	WriteToFileBuffer("[" + ID + "]", "Annoyance", ConverBoolToYesNo(annoyance), false);
	WriteToFileBuffer("[" + ID + "]", "IonImmune", ConverBoolToYesNo(ionimmune), false);
	WriteToFileBuffer("[" + ID + "]", "Recruiter", ConverBoolToYesNo(recruiter), false);
	WriteToFileBuffer("[" + ID + "]", "Reinforce", ConverBoolToYesNo(reinforce), false);
	WriteToFileBuffer("[" + ID + "]", "TaskForce", taskForceID, false);
	WriteToFileBuffer("[" + ID + "]", "TechLevel", IntToStr(techlevel), false);
	WriteToFileBuffer("[" + ID + "]", "Aggressive", ConverBoolToYesNo(aggressive), false);
	WriteToFileBuffer("[" + ID + "]", "Autocreate", ConverBoolToYesNo(autocreate), false);
	WriteToFileBuffer("[" + ID + "]", "GuardSlower", ConverBoolToYesNo(guardslower), false);
	WriteToFileBuffer("[" + ID + "]", "OnTransOnly", ConverBoolToYesNo(ontransonly), false);
	WriteToFileBuffer("[" + ID + "]", "AvoidThreats", ConverBoolToYesNo(avoidthreats), false);
	WriteToFileBuffer("[" + ID + "]", "LooseRecruit", ConverBoolToYesNo(looserecruit), false);
	WriteToFileBuffer("[" + ID + "]", "VeteranLevel", IntToStr(veteranlevel), false);
	WriteToFileBuffer("[" + ID + "]", "IsBaseDefense", ConverBoolToYesNo(isbasedefense), false);
	WriteToFileBuffer("[" + ID + "]", "OnlyTargetHouseEnemy", ConverBoolToYesNo(onlytargethousenemy), false);
	WriteToFileBuffer("[" + ID + "]", "TransportsReturnOnUnload", ConverBoolToYesNo(transportsreturnonunload), false);
	WriteToFileBuffer("[" + ID + "]", "AreTeamMembersRecruitable", ConverBoolToYesNo(areteammembersrecruitable), false);
}
