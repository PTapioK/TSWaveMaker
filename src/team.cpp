#include "team.h"


Team::Team(std::string nID, int nmax, std::string ntagID, bool nfull, std::string nname, int ngroup, std::string nhouse, std::string nscriptID, bool nwhiner, bool ndroppod, bool nsuicide, bool nloadable, bool nprebuild,
		   int nprioirity, std::string nwpoint, bool nannoyance, bool nionimmune, bool nrecruiter,
		   bool nreinforce, std::string ntaskforceid, int ntechlevel, bool naggressive, bool nautocreate, bool nguardslower, bool nontransonly, bool navoidthreats, bool
		   nlooserecruit, int nveteranlevel, bool nisbasedefense,
		   bool nonlytargethouseenemy, bool ntransportsreturnonunload, bool nareteammemberrecruitable) :
	ID(nID), max(nmax), tagID(ntagID), full(nfull), name(nname), group(ngroup), house(nhouse), scriptID(nscriptID), whiner(nwhiner), droppod(ndroppod), suicide(nsuicide),
	loadable(nloadable), prebuild(nprebuild), priority(nprioirity), wPoint(nwpoint), annoyance(nannoyance), ionimmune(nionimmune), recruiter(nrecruiter),
	reinforce(nreinforce), taskForceID(ntaskforceid), techlevel(ntechlevel), aggressive(naggressive), autocreate(nautocreate), guardslower(nguardslower),
	ontransonly(nontransonly), avoidthreats(navoidthreats), looserecruit(nlooserecruit), veteranlevel(nveteranlevel), isbasedefense(nisbasedefense),
	onlytargethousenemy(nonlytargethouseenemy), transportsreturnonunload(ntransportsreturnonunload), areteammembersrecruitable(nareteammemberrecruitable)
{
}

Team::Team(std::string nID, std::string nname) {
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

Team::Team(std::string nID, Team *nTeam)
{
	*this = *nTeam;
	this->ID = nID;
}

Team::~Team()
{
	deleteSectionFromBuffer(ID);
}

void Team::setName(std::string newName)
{
	name = newName;
}

void Team::save()
{
	writeLineToBuffer(ID, "Max", intToStr(max));
	if(!tagID.empty()) {
		writeLineToBuffer(ID, "Tag", tagID);
	}
	writeLineToBuffer(ID, "Full", converBoolToYesNo(full));
	writeLineToBuffer(ID, "Name", name);
	writeLineToBuffer(ID, "Group", intToStr(group));
	writeLineToBuffer(ID, "House", house);
	writeLineToBuffer(ID, "Script", scriptID);
	writeLineToBuffer(ID, "Whiner", converBoolToYesNo(whiner));
	writeLineToBuffer(ID, "Droppod", converBoolToYesNo(droppod));
	writeLineToBuffer(ID, "Suicide", converBoolToYesNo(suicide));
	writeLineToBuffer(ID, "Loadable", converBoolToYesNo(loadable));
	writeLineToBuffer(ID, "Prebuild", converBoolToYesNo(prebuild));
	writeLineToBuffer(ID, "Priority", intToStr(priority));
	writeLineToBuffer(ID, "Waypoint", wPoint);
	writeLineToBuffer(ID, "Annoyance", converBoolToYesNo(annoyance));
	writeLineToBuffer(ID, "IonImmune", converBoolToYesNo(ionimmune));
	writeLineToBuffer(ID, "Recruiter", converBoolToYesNo(recruiter));
	writeLineToBuffer(ID, "Reinforce", converBoolToYesNo(reinforce));
	writeLineToBuffer(ID, "TaskForce", taskForceID);
	writeLineToBuffer(ID, "TechLevel", intToStr(techlevel));
	writeLineToBuffer(ID, "Aggressive", converBoolToYesNo(aggressive));
	writeLineToBuffer(ID, "Autocreate", converBoolToYesNo(autocreate));
	writeLineToBuffer(ID, "GuardSlower", converBoolToYesNo(guardslower));
	writeLineToBuffer(ID, "OnTransOnly", converBoolToYesNo(ontransonly));
	writeLineToBuffer(ID, "AvoidThreats", converBoolToYesNo(avoidthreats));
	writeLineToBuffer(ID, "LooseRecruit", converBoolToYesNo(looserecruit));
	writeLineToBuffer(ID, "VeteranLevel", intToStr(veteranlevel));
	writeLineToBuffer(ID, "IsBaseDefense", converBoolToYesNo(isbasedefense));
	writeLineToBuffer(ID, "OnlyTargetHouseEnemy", converBoolToYesNo(onlytargethousenemy));
	writeLineToBuffer(ID, "TransportsReturnOnUnload", converBoolToYesNo(transportsreturnonunload));
	writeLineToBuffer(ID, "AreTeamMembersRecruitable", converBoolToYesNo(areteammembersrecruitable));
}

std::string Team::getName() const
{
	return name;
}

std::string Team::getID() const
{
	return ID;
}
