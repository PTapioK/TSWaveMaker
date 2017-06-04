#include "team.h"


Team::Team(QString nID, int nmax, QString ntagID, bool nfull, QString nname, int ngroup, QString nhouse, QString nscriptID, bool nwhiner, bool ndroppod, bool nsuicide, bool nloadable, bool nprebuild,
		   int nprioirity, QString nwpoint, bool nannoyance, bool nionimmune, bool nrecruiter,
		   bool nreinforce, QString ntaskforceid, int ntechlevel, bool naggressive, bool nautocreate, bool nguardslower, bool nontransonly, bool navoidthreats, bool
		   nlooserecruit, int nveteranlevel, bool nisbasedefense,
		   bool nonlytargethouseenemy, bool ntransportsreturnonunload, bool nareteammemberrecruitable) :
	ID(nID), max(nmax), tagID(ntagID), full(nfull), name(nname), group(ngroup), house(nhouse), scriptID(nscriptID), whiner(nwhiner), droppod(ndroppod), suicide(nsuicide),
	loadable(nloadable), prebuild(nprebuild), priority(nprioirity), wPoint(nwpoint), annoyance(nannoyance), ionimmune(nionimmune), recruiter(nrecruiter),
	reinforce(nreinforce), taskForceID(ntaskforceid), techlevel(ntechlevel), aggressive(naggressive), autocreate(nautocreate), guardslower(nguardslower),
	ontransonly(nontransonly), avoidthreats(navoidthreats), looserecruit(nlooserecruit), veteranlevel(nveteranlevel), isbasedefense(nisbasedefense),
	onlytargethousenemy(nonlytargethouseenemy), transportsreturnonunload(ntransportsreturnonunload), areteammembersrecruitable(nareteammemberrecruitable)
{
}

Team::Team(QString nID, QString nName)
{
	ID = nID;
	max = 0;
	full = false;
	name = nName;
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

Team::Team(QString nID, Team *nTeam)
{
	*this = *nTeam;
	this->ID = nID;
}

Team::~Team()
{
	file.deleteSectionFromBuffer(ID);
}

void Team::setName(QString newName)
{
	name = newName;
}

void Team::setHouse(QString newHouse)
{
	house = newHouse;
}

void Team::save()
{
	file.saveLineToBuffer(ID, "Max", QString::number(max));
	if(!tagID.isEmpty()) {
		file.saveLineToBuffer(ID, "Tag", tagID);
	}
	file.saveLineToBuffer(ID, "Full", convertBoolToYesNo(full));
	file.saveLineToBuffer(ID, "Name", name);
	file.saveLineToBuffer(ID, "Group", QString::number(group));
	file.saveLineToBuffer(ID, "House", house);
	file.saveLineToBuffer(ID, "Script", scriptID);
	file.saveLineToBuffer(ID, "Whiner", convertBoolToYesNo(whiner));
	file.saveLineToBuffer(ID, "Droppod", convertBoolToYesNo(droppod));
	file.saveLineToBuffer(ID, "Suicide", convertBoolToYesNo(suicide));
	file.saveLineToBuffer(ID, "Loadable", convertBoolToYesNo(loadable));
	file.saveLineToBuffer(ID, "Prebuild", convertBoolToYesNo(prebuild));
	file.saveLineToBuffer(ID, "Priority", QString::number(priority));
	file.saveLineToBuffer(ID, "Waypoint", wPoint);
	file.saveLineToBuffer(ID, "Annoyance", convertBoolToYesNo(annoyance));
	file.saveLineToBuffer(ID, "IonImmune", convertBoolToYesNo(ionimmune));
	file.saveLineToBuffer(ID, "Recruiter", convertBoolToYesNo(recruiter));
	file.saveLineToBuffer(ID, "Reinforce", convertBoolToYesNo(reinforce));
	file.saveLineToBuffer(ID, "TaskForce", taskForceID);
	file.saveLineToBuffer(ID, "TechLevel", QString::number(techlevel));
	file.saveLineToBuffer(ID, "Aggressive", convertBoolToYesNo(aggressive));
	file.saveLineToBuffer(ID, "Autocreate", convertBoolToYesNo(autocreate));
	file.saveLineToBuffer(ID, "GuardSlower", convertBoolToYesNo(guardslower));
	file.saveLineToBuffer(ID, "OnTransOnly", convertBoolToYesNo(ontransonly));
	file.saveLineToBuffer(ID, "AvoidThreats", convertBoolToYesNo(avoidthreats));
	file.saveLineToBuffer(ID, "LooseRecruit", convertBoolToYesNo(looserecruit));
	file.saveLineToBuffer(ID, "VeteranLevel", QString::number(veteranlevel));
	file.saveLineToBuffer(ID, "IsBaseDefense", convertBoolToYesNo(isbasedefense));
	file.saveLineToBuffer(ID, "OnlyTargetHouseEnemy", convertBoolToYesNo(onlytargethousenemy));
	file.saveLineToBuffer(ID, "TransportsReturnOnUnload", convertBoolToYesNo(transportsreturnonunload));
	file.saveLineToBuffer(ID, "AreTeamMembersRecruitable", convertBoolToYesNo(areteammembersrecruitable));
}

QString Team::getName() const
{
	return name;
}

QString Team::getID() const
{
	return ID;
}

QString Team::getHouse() const
{
	return house;
}

QString Team::convertBoolToYesNo(bool boolean)
{
	if(boolean == true) {
		return "yes";
	} else {
		return "no";
	}
}
