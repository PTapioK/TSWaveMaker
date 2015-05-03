#include "fileoperations.h"


void SaveAllToBuffer() {
	for(triggerIT IT = triggers.begin(); IT != triggers.end(); ++IT) {
		(*IT).second->Save();
	}
	for(tagIT IT = tags.begin(); IT != tags.end(); ++IT) {
		(*IT).second->Save();
	}

	int i = 0;
	DeleteSectionInBuffer("TeamTypes");
	for(teamIT IT = teams.begin(); IT != teams.end(); ++IT) {
		WriteValueToBuffer("TeamTypes", IntToStr(i), IT->second->getID());
		++i;
	}
	for(teamIT IT = teams.begin(); IT != teams.end(); ++IT) {
		(*IT).second->Save();
	}
	i = 0;
	DeleteSectionInBuffer("ScriptTypes");
	for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		WriteValueToBuffer("ScriptTypes", IntToStr(i), IT->second->getID());
		++i;
	}
	for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		(*IT).second->Save();
	}

}

// 0 = value1, 1 = value2 etc...
void WriteValueToBuffer(string section, string ID) {

	for(int idC = 0; idC < 1000; ++idC) {
		stringstream idS;
		idS << idC;
		if(curdata.GetKey(idS.str(), section) == NULL) {
			curdata.SetValue(idS.str(), ID, "", section);
			break;
		}
	}

}

void WriteValueToBuffer(string section, string ID, string value) {
	curdata.SetValue(ID, value, "", section);
}

void EditValueInBuffer(string section, string ID, string value, int count) {

	string rawEx = curdata.GetValue(ID, section);
	string exvalue = rawEx.substr(rawEx.find(",")+1);
	string newVal = IntToStr(count) + "," + exvalue + "," + value;
	curdata.SetValue(ID, newVal, "", section);

}

void ReadFileToBuffer() {
	curdata.Load(cur_file);
}

void DeleteValueInBuffer(string section, string ID) {
	curdata.DeleteKey(ID, section);
}

void DeleteSectionInBuffer(string section) {
	curdata.DeleteSection(section);
}

void ParseSections() {

	t_Section * trSec = curdata.GetSection("Triggers");

	if(trSec != NULL) {
		triggers.clear();
		KeyList * trigs = trSec->GetKeyList();
		for(KeyItor keyIT = trigs->begin(); keyIT < trigs->end(); ++keyIT) {
			string Key = keyIT->szKey;

			string cur_line = curdata.GetString(Key, "Triggers");

			string ID = Key;

			string house = cur_line.substr(0, cur_line.find(","));
			cur_line = cur_line.substr(cur_line.find(",")+1);

			string attachID = cur_line.substr(0, cur_line.find(","));
			cur_line = cur_line.substr(cur_line.find(",")+1);

			string name = cur_line.substr(0, cur_line.find(","));
			cur_line = cur_line.substr(cur_line.find(",")+1);

			string isDisabled_s = cur_line.substr(0, cur_line.find(","));
			cur_line = cur_line.substr(cur_line.find(",")+1);
			bool isDisabled = atoi(isDisabled_s.c_str());

			string isEasy_s = cur_line.substr(0, cur_line.find(","));
			cur_line = cur_line.substr(cur_line.find(",")+1);
			bool isEasy = atoi(isEasy_s.c_str());

			string isMedium_s = cur_line.substr(0, cur_line.find(","));
			cur_line = cur_line.substr(cur_line.find(",")+1);
			bool isMedium = atoi(isMedium_s.c_str());

			string isHard_s = cur_line;
			bool isHard = atoi(isHard_s.c_str());

			triggers[ID] = new Trigger(ID, house, attachID, name, isDisabled, isEasy, isMedium, isHard);

		}

	}

	t_Section * tagSec = curdata.GetSection("Tags");

	if (tagSec != NULL) {
		tags.clear();
		KeyList * tagsl = tagSec->GetKeyList();
		for(KeyItor keyIT = tagsl->begin(); keyIT < tagsl->end(); ++keyIT) {
			string Key = keyIT->szKey;

			string cur_line = curdata.GetString(Key, "Tags");

			string ID = Key;

			int32_t mode = atoi(cur_line.substr(0, cur_line.find(",")).c_str());
			cur_line = cur_line.substr(cur_line.find(",")+1);

			string name = cur_line.substr(0, cur_line.find(","));
			cur_line = cur_line.substr(cur_line.find(",")+1);

			string triggerID = cur_line;

			tags[name] = new Tag(ID, name, triggerID, mode);

		}
	}

	t_Section * wpnSec = curdata.GetSection("Waypoints");

	if (wpnSec != NULL) {
		waypoints.clear();
		KeyList * wpnl = wpnSec->GetKeyList();
		for(KeyItor keyIT = wpnl->begin(); keyIT < wpnl->end(); ++keyIT) {
			string Key = keyIT->szKey;

			int32_t waypoint = atoi(Key.c_str());
			waypoints.push_back(waypoint);
		}

	}

	t_Section * teamSec = curdata.GetSection("TeamTypes");

	if (teamSec != NULL) {
		teams.clear();
		KeyList * teaml = teamSec->GetKeyList();
		for(KeyItor keyIT = teaml->begin(); keyIT < teaml->end(); ++keyIT) {
			string Key = keyIT->szKey;
			string cur_line = curdata.GetString(Key, "TeamTypes");

			string teamID = cur_line.substr(0, 8);
			Team *nTeam = FindNewTeamFromFile(teamID);

			if(nTeam != NULL)
				teams[teamID] = nTeam;


		}
	}

	t_Section * scriptSec = curdata.GetSection("ScriptTypes");
	if (scriptSec != NULL) {
		scripts.clear();
		KeyList * scriptl = scriptSec->GetKeyList();
		for(KeyItor keyIT = scriptl->begin(); keyIT < scriptl->end(); ++keyIT) {
			string Key = keyIT->szKey;
			string cur_line = curdata.GetString(Key, "ScriptTypes");

			string scriptID = cur_line.substr(0, 8);
			Script *nScript = FindNewScriptFromFile(scriptID);

			if(nScript != NULL)
				scripts[scriptID] = nScript;

		}
	}

	t_Section * taskSec = curdata.GetSection("TaskForces");
	if (taskSec != NULL) {
		taskforces.clear();
		KeyList * taskl = taskSec->GetKeyList();
		for(KeyItor keyIT = taskl->begin(); keyIT < taskl->end(); ++keyIT) {
			string Key = keyIT->szKey;
			string cur_line = curdata.GetString(Key, "TaskForces");

			string taskforceID = cur_line.substr(0, 8);
			Taskforce *nTaskforce = FindNewTaskforceFromFile(taskforceID);

			if(nTaskforce != NULL)
				taskforces[taskforceID] = nTaskforce;
		}
	}

	t_Section * eventSec = curdata.GetSection("Events");
	if(eventSec != NULL) {
		KeyList * eventl = eventSec->GetKeyList();
		for(KeyItor keyIT = eventl->begin(); keyIT < eventl->end(); ++keyIT) {
			string Key = keyIT->szKey;

			string cur_line = curdata.GetString(Key, "Events");

			string ID = Key;

			int32_t count = atoi(cur_line.substr(0, cur_line.find(",")).c_str());
			cur_line = cur_line.substr(cur_line.find(",")+1);

			for(int i = 0; i != count; ++i) {
				int32_t eType = atoi(cur_line.substr(0, cur_line.find(",")).c_str());
				cur_line = cur_line.substr(cur_line.find(",")+1);

				int32_t nullparam = atoi(cur_line.substr(0, cur_line.find(",")).c_str());
				cur_line = cur_line.substr(cur_line.find(",")+1);

				int32_t param = 0;
				if(i != count-1) {
					param = atoi(cur_line.substr(0, cur_line.find(",")).c_str());
					cur_line = cur_line.substr(cur_line.find(",")+1);
				} else {
					param = atoi(cur_line.c_str());
				}

				triggers[ID]->addEvent(new Event(eType, param, ID));
			}

		}
	}

	t_Section * actionSec = curdata.GetSection("Actions");
	if (actionSec != NULL) {

		KeyList * actl = actionSec->GetKeyList();
		for(KeyItor keyIT = actl->begin(); keyIT < actl->end(); ++keyIT) {
			string Key = keyIT->szKey;

			string cur_line = curdata.GetString(Key, "Actions");

			string ID = Key;

			int32_t count = atoi(cur_line.substr(0, cur_line.find(",")).c_str());
			cur_line = cur_line.substr(cur_line.find(",")+1);

			for(int i = 0; i != count; ++i) {
				int32_t aType = atoi(cur_line.substr(0, cur_line.find(",")).c_str());
				cur_line = cur_line.substr(cur_line.find(",")+1);

				int32_t p1 = atoi(cur_line.substr(0, cur_line.find(",")).c_str());
				cur_line = cur_line.substr(cur_line.find(",")+1);

				string p2 = cur_line.substr(0, cur_line.find(","));
				cur_line = cur_line.substr(cur_line.find(",")+1);

				int32_t p3 = atoi(cur_line.substr(0, cur_line.find(",")).c_str());
				cur_line = cur_line.substr(cur_line.find(",")+1);

				int32_t p4 = atoi(cur_line.substr(0, cur_line.find(",")).c_str());
				cur_line = cur_line.substr(cur_line.find(",")+1);

				int32_t p5 = atoi(cur_line.substr(0, cur_line.find(",")).c_str());
				cur_line = cur_line.substr(cur_line.find(",")+1);

				int32_t p6 = atoi(cur_line.substr(0, cur_line.find(",")).c_str());
				cur_line = cur_line.substr(cur_line.find(",")+1);

				int32_t wPoint = 0;

				if(i != count-1) {
					wPoint = WaypointIDToDec(cur_line.substr(0, cur_line.find(",")).c_str());
					cur_line = cur_line.substr(cur_line.find(",")+1);
				} else {
					wPoint = WaypointIDToDec(cur_line.c_str());
				}

				triggers[ID]->addAction(new Action(ID, aType, wPoint, p1, p2, p3, p4, p5, p6));
			}

		}
	}

	t_Section * aiTrigSec = curdata.GetSection("AITriggerTypes");
	if(aiTrigSec != NULL) {
		KeyList * aiTrigl = aiTrigSec->GetKeyList();
		for(KeyItor keyIT = aiTrigl->begin(); keyIT < aiTrigl->end(); ++keyIT) {
			string Key = keyIT->szKey;

			string cur_line = curdata.GetString(Key, "Actions");

			string ID = Key;

			aitriggers[ID] = cur_line;
		}
	}

}

Taskforce* FindNewTaskforceFromFile(string taskforceID) {

	t_Section * cTaskF = curdata.GetSection(taskforceID);
	if(cTaskF != NULL) {

		string name = "New Taskforce";
		int32_t group = -1;

		Taskforce *nTaskforce = new Taskforce(taskforceID);

		KeyList * taskl = cTaskF->GetKeyList();
		for(KeyItor keyIT = taskl->begin(); keyIT < taskl->end(); ++keyIT) {
			string Key = keyIT->szKey;
			string cur_line = curdata.GetString(Key, taskforceID);

			string type = "";
			short amount = 0;

			if(Key == "Group") {
				group = curdata.GetInt(Key, taskforceID);
				nTaskforce->setGroup(group);

				return nTaskforce;
			} else if (Key == "Name") {
				name = cur_line;
				nTaskforce->setName(name);
			} else {
				string val = GetValueStr(cur_line);
				amount = atoi(val.substr(0, val.find(",")).c_str());

				val = val.substr(val.find(",")+1);
				type = val.substr(0, val.find("\n"));

				nTaskforce->NewLine(type, amount);
			}
		}
	}

	return NULL;
}

Script *FindNewScriptFromFile(string scriptID) {

	t_Section * cScript = curdata.GetSection(scriptID);

	if(cScript != NULL) {

		string name = "New Script";

		Script *nScript = new Script(scriptID);

		KeyList * scriptl = cScript->GetKeyList();
		for(KeyItor keyIT = scriptl->begin(); keyIT < scriptl->end(); ++keyIT) {
			string Key = keyIT->szKey;
			string cur_line = curdata.GetString(Key, scriptID);

			short type = 0;
			short param = 0;

			if(Key == "Name") {
				name = cur_line;
				nScript->setName(name);

				return nScript;
			} else {

				string val = cur_line;
				type = atoi(val.substr(0, val.find(",")).c_str());

				val = val.substr(val.find(",")+1);
				param = atoi(val.c_str());

				nScript->NewLine(type, param);
			}
		}
	}

	return NULL;
}

Team *FindNewTeamFromFile(string teamID) {
	t_Section * cTeam = curdata.GetSection(teamID);
	if(cTeam != NULL) {

		int max = 0;
		string tag;
		bool full = false;
		string name;
		int group = -1;
		string house;
		string script;
		bool whiner = false;
		bool droppod = false;
		bool suicide = false;
		bool loadable = false;
		bool prebuild = false;
		int priority = 1;
		string waypoint;
		bool annoyance = false;
		bool ionimmune = false;
		bool recruiter = false;
		bool reinforce = false;
		string taskforce;
		int techlevel;
		bool aggressive = false;
		bool autocreate = false;
		bool guardslower = false;
		bool ontransonly = false;
		bool avoidthreats = false;
		bool looserecruit = false;
		int veteranlevel = 1;
		bool isbasedefense = false;
		bool onlytargethousenemy = false;
		bool transportsreturnonunload = false;
		bool areteammembersrecruitable = true;

		max = curdata.GetInt("Max", teamID);

		tag = curdata.GetString("Tag", teamID);

		full = ConverToBool(curdata.GetString("Full", teamID));

		name = curdata.GetString("Name", teamID);

		group = curdata.GetInt("Group", teamID);

		house = curdata.GetString("House", teamID);

		script = curdata.GetString("Script", teamID);

		whiner = ConverToBool(curdata.GetString("Whiner", teamID));

		droppod = ConverToBool(curdata.GetString("Droppod", teamID));

		suicide = ConverToBool(curdata.GetString("Suicide", teamID));

		loadable = ConverToBool(curdata.GetString("Loadable", teamID));

		prebuild = ConverToBool(curdata.GetString("Prebuild", teamID));

		priority = curdata.GetInt("Priority", teamID);

		waypoint = curdata.GetString("Waypoint", teamID);

		annoyance = ConverToBool(curdata.GetString("Annoyance", teamID));

		ionimmune = ConverToBool(curdata.GetString("IonImmune", teamID));

		recruiter = ConverToBool(curdata.GetString("Recruiter", teamID));

		reinforce = ConverToBool(curdata.GetString("Reinforce", teamID));

		taskforce = curdata.GetString("TaskForce", teamID);

		techlevel = curdata.GetInt("TechLevel", teamID);

		aggressive = ConverToBool(curdata.GetString("Aggressive", teamID));

		autocreate = ConverToBool(curdata.GetString("Autocreate", teamID));

		guardslower = ConverToBool(curdata.GetString("GuardSlower", teamID));

		ontransonly = ConverToBool(curdata.GetString("OnTransOnly", teamID));

		avoidthreats = ConverToBool(curdata.GetString("AvoidThreats", teamID));

		looserecruit = ConverToBool(curdata.GetString("LooseRecruit", teamID));

		veteranlevel = curdata.GetInt("VeteranLevel", teamID);

		isbasedefense = ConverToBool(curdata.GetString("IsBaseDefense", teamID));

		onlytargethousenemy = ConverToBool(curdata.GetString("OnlyTargetHouseEnemy", teamID));

		transportsreturnonunload = ConverToBool(curdata.GetString("TransportsReturnOnUnload", teamID));

		areteammembersrecruitable = ConverToBool(curdata.GetString("AreTeamMembersRecruitable", teamID));


		return new Team(teamID, max, tag, full, name, group, house, script, whiner, droppod, suicide,
						loadable, prebuild, priority, waypoint, annoyance, ionimmune, recruiter,
						reinforce, taskforce, techlevel, aggressive, autocreate, guardslower,
						ontransonly, avoidthreats, looserecruit, veteranlevel, isbasedefense,
						onlytargethousenemy, transportsreturnonunload, areteammembersrecruitable);
	}

	return NULL;
}

