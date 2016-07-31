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

Team::Team(QString nID, QString nname)
{
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

Team::Team(QString nID, Team *nTeam)
{
	*this = *nTeam;
	this->ID = nID;
}

Team::~Team()
{
	fileHandler.deleteSectionFromBuffer(ID);
}

void Team::setName(QString newName)
{
	name = newName;
}

void Team::save()
{
	fileHandler.writeLineToBuffer(ID, "Max", QString::number(max));
	if(!tagID.isEmpty()) {
		fileHandler.writeLineToBuffer(ID, "Tag", tagID);
	}
	fileHandler.writeLineToBuffer(ID, "Full", convertBoolToYesNo(full));
	fileHandler.writeLineToBuffer(ID, "Name", name);
	fileHandler.writeLineToBuffer(ID, "Group", QString::number(group));
	fileHandler.writeLineToBuffer(ID, "House", house);
	fileHandler.writeLineToBuffer(ID, "Script", scriptID);
	fileHandler.writeLineToBuffer(ID, "Whiner", convertBoolToYesNo(whiner));
	fileHandler.writeLineToBuffer(ID, "Droppod", convertBoolToYesNo(droppod));
	fileHandler.writeLineToBuffer(ID, "Suicide", convertBoolToYesNo(suicide));
	fileHandler.writeLineToBuffer(ID, "Loadable", convertBoolToYesNo(loadable));
	fileHandler.writeLineToBuffer(ID, "Prebuild", convertBoolToYesNo(prebuild));
	fileHandler.writeLineToBuffer(ID, "Priority", QString::number(priority));
	fileHandler.writeLineToBuffer(ID, "Waypoint", wPoint);
	fileHandler.writeLineToBuffer(ID, "Annoyance", convertBoolToYesNo(annoyance));
	fileHandler.writeLineToBuffer(ID, "IonImmune", convertBoolToYesNo(ionimmune));
	fileHandler.writeLineToBuffer(ID, "Recruiter", convertBoolToYesNo(recruiter));
	fileHandler.writeLineToBuffer(ID, "Reinforce", convertBoolToYesNo(reinforce));
	fileHandler.writeLineToBuffer(ID, "TaskForce", taskForceID);
	fileHandler.writeLineToBuffer(ID, "TechLevel", QString::number(techlevel));
	fileHandler.writeLineToBuffer(ID, "Aggressive", convertBoolToYesNo(aggressive));
	fileHandler.writeLineToBuffer(ID, "Autocreate", convertBoolToYesNo(autocreate));
	fileHandler.writeLineToBuffer(ID, "GuardSlower", convertBoolToYesNo(guardslower));
	fileHandler.writeLineToBuffer(ID, "OnTransOnly", convertBoolToYesNo(ontransonly));
	fileHandler.writeLineToBuffer(ID, "AvoidThreats", convertBoolToYesNo(avoidthreats));
	fileHandler.writeLineToBuffer(ID, "LooseRecruit", convertBoolToYesNo(looserecruit));
	fileHandler.writeLineToBuffer(ID, "VeteranLevel", QString::number(veteranlevel));
	fileHandler.writeLineToBuffer(ID, "IsBaseDefense", convertBoolToYesNo(isbasedefense));
	fileHandler.writeLineToBuffer(ID, "OnlyTargetHouseEnemy", convertBoolToYesNo(onlytargethousenemy));
	fileHandler.writeLineToBuffer(ID, "TransportsReturnOnUnload", convertBoolToYesNo(transportsreturnonunload));
	fileHandler.writeLineToBuffer(ID, "AreTeamMembersRecruitable", convertBoolToYesNo(areteammembersrecruitable));
}

QString Team::getName() const
{
	return name;
}

QString Team::getID() const
{
	return ID;
}
