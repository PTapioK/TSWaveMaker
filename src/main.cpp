#include "main.h"
#include "mainwindow.h"

string cur_file;

map <string, Trigger*> triggers;
map <string, Tag*> tags;
map <string, Team*> teams;
map <string, Script*> scripts;
map <string, Taskforce*> taskforces;
map <string, string> aitriggers;

map <string, Trigger*>::iterator triggerIT;
map <string, Tag*>::iterator tagIT;
map <string, Team*>::iterator teamIT;
map <string, Script*>::iterator scriptIT;
map <string, Taskforce*>::iterator taskforceIT;
map <string, string>::iterator aitriggerIT;

vector <Action*>::iterator actionIT;
vector <Event*>::iterator eventIT;

vector<string> filedata;

vector <int32_t> waypoints;
vector <int32_t>::iterator waypointIT;

const char alphas[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };

uint32_t sWPoint = 8;

// Find First Free ID
string fffID() {
	string nextID;
	stringstream ssID;

	int32_t i = 1000002;

	vector<string> IDTemp;
	vector<string>::iterator IDIT;

	if(triggers.empty() && tags.empty() && teams.empty() && scripts.empty() && taskforces.empty()) {
		ssID << "0" << i;
		return string(ssID.str().c_str());
	}

	for(triggerIT = triggers.begin(); triggerIT != triggers.end(); ++triggerIT) {
		IDTemp.push_back((*triggerIT).second->getID());
	}

	for(tagIT = tags.begin(); tagIT != tags.end(); ++tagIT) {
		IDTemp.push_back((*tagIT).second->getID());
	}

	for(teamIT = teams.begin(); teamIT != teams.end(); ++teamIT) {
		IDTemp.push_back((*teamIT).first);
	}

	for (scriptIT = scripts.begin(); scriptIT != scripts.end(); ++scriptIT) {
		IDTemp.push_back((*scriptIT).second->getID());
	}

	for (taskforceIT = taskforces.begin(); taskforceIT != taskforces.end(); ++taskforceIT) {
		IDTemp.push_back((*taskforceIT).second->getID());
	}


	sort(IDTemp.begin(), IDTemp.end());

	IDIT = IDTemp.begin();

	string a = "";
	while(1) {
		ssID.str("");
		ssID << "0" << i;
		nextID = string(ssID.str().c_str());

		if(IDIT == IDTemp.end()) {
			a = "";
		} else {
			a = (*IDIT);
		}


		if(a == nextID) {
			++i;
		} else {
			return nextID;
		}

		if(IDIT != IDTemp.end()) {
			++IDIT;
		} else {
			break;
		}

	}

	ssID.str("");
	ssID << "0" << i;
	nextID = string(ssID.str().c_str());

	return nextID;
}

void SaveAllToFile() {
	for(triggerIT = triggers.begin(); triggerIT != triggers.end(); ++triggerIT) {
		(*triggerIT).second->WriteToFile();
	}
	for(tagIT = tags.begin(); tagIT != tags.end(); ++tagIT) {
		(*tagIT).second->WriteToFile();
	}
	FILE * file;
	file = fopen(cur_file.c_str(), "wb");

	for(vector<string>::iterator fileIT = filedata.begin(); fileIT != filedata.end(); ++fileIT) {
		fputs((*fileIT).c_str(), file);
	}

	fclose(file);
}

void WriteToFileBuffer(string section, string ID) {
	section += "\n";
	ID += "\n";
	if(filedata.empty()) {
		ID = "0=" + ID;
		filedata.push_back(section);
		filedata.push_back(ID);
	} else {
		for(vector<string>::iterator fileIT = filedata.begin(); fileIT != filedata.end(); ++fileIT) {
			string cur_line = *fileIT;
			if(cur_line.find(";") == string::npos) {
				if((*fileIT) == section) {
					int idC = 0;
					string::size_type pos;
					while(1) {

						++fileIT;
						if(fileIT == filedata.end()) { break; }

						cur_line = *fileIT;
						pos = cur_line.find('=');
						if(pos != string::npos) {
							if(cur_line.find(ID) != string::npos) {
								(*fileIT) = cur_line.substr(0, pos);
								(*fileIT) += "=";
								(*fileIT) += ID;
								return;
							}
							++idC;
						} else {
							break;
						}

					}

					stringstream ssID;
					ssID << idC;
					ssID << "=";
					ssID << ID;
					filedata.insert(fileIT, ssID.str());
					return;
				}
			}
		}
		for(vector<string>::iterator fileIT = filedata.begin(); fileIT != filedata.end(); ++fileIT) {
			if((*fileIT).find("\n") != string::npos) {
				fileIT = filedata.insert(fileIT, "\n");
				ID = "0=" + ID;
				fileIT = filedata.insert(fileIT+1, section);
				fileIT = filedata.insert(fileIT+1, ID);
				break;
			} else if (fileIT == filedata.end()) {
				filedata.push_back("\n");
				ID = "0=" + ID;
				filedata.push_back(section);
				filedata.push_back(ID);
				break;
			}
		}
	}
}

void WriteToFileBuffer(string section, string ID, string value) {
	section += "\n";
	value += "\n";
	if(filedata.empty()) {
		filedata.push_back(section);
		filedata.push_back(ID + "=" + value);
	} else {
		int i = 0;
		for(vector<string>::iterator fileIT = filedata.begin(); fileIT != filedata.end(); ++fileIT) {
			i = i + 1;
			string cur_line = *fileIT;
			if(cur_line.find(";") == string::npos) {
				if((*fileIT) == section) {
					string::size_type pos;
					int b = i;
					while(1) {
						++fileIT;
						i = i + 1;
						if(fileIT == filedata.end()) { break; }
						cur_line = *fileIT;
						pos = cur_line.find('=');
						if(pos != string::npos) {
							if(cur_line.find(ID) != string::npos) {
								(*fileIT) = ID + "=" + value;
								return;
							}
						} else {
							break;
						}

					}

					filedata.insert(fileIT, ID + "=" + value);

					sort(filedata.begin()+b, filedata.begin()+i);

					return;
				}
			}
		}
		for(vector<string>::iterator fileIT = filedata.begin(); fileIT < filedata.end(); ++fileIT) {
			if(*fileIT == "\n" && fileIT != filedata.end()) {
				fileIT = filedata.insert(fileIT, "\n");
				fileIT = filedata.insert(fileIT+1, section);
				fileIT = filedata.insert(fileIT+1, ID + "=" + value);
				return;
			}
		}
		filedata.push_back("\n");
		filedata.push_back(section);
		filedata.push_back(ID + "=" + value);
	}
}

void AddToFileBuffer(string section, string ID, string value, int count) {
	value += "\n";
	int i = 0;
	for(vector<string>::iterator fileIT = filedata.begin(); fileIT != filedata.end(); ++fileIT) {
		i = i + 1;
		string cur_line = *fileIT;
		if(cur_line.find(";") == string::npos) {
			if((*fileIT) == section + "\n") {
				string::size_type pos;
				int b = i;
				while(1) {
					++fileIT;
					i = i + 1;
					if(fileIT == filedata.end()) { break; }
					cur_line = *fileIT;
					pos = cur_line.find('=');
					if(pos != string::npos) {
						if(cur_line.find(ID) != string::npos) {
							string exvalue = cur_line.substr(pos+3);
							exvalue = exvalue.substr(0, exvalue.length()-1);
							stringstream countSS;
							countSS << count;
							(*fileIT) = ID + "=" + countSS.str() + "," + exvalue + "," + value;
							return;
						}
					} else {
						break;
					}

				}

				filedata.insert(fileIT, ID + "=" + value);

				sort(filedata.begin()+b, filedata.begin()+i);

				return;
			}
		}
	}

}

void ReadFileToBuffer() {
	filedata.clear();

	FILE * file;
	file = fopen(cur_file.c_str(), "rb");
	string line = "";
	while(1) {
		int c = fgetc(file);
		if (c != '\n' && c != EOF) {
			line = line + char(c);
		} else {
			line += "\n";
			filedata.push_back(line);
			line = "";
			if (c == EOF) {
				break;
			}
		}
	}
	fclose(file);

}

void ParseBuffer() {
	ReadFileToBuffer();
	for(vector<string>::iterator fileIT = filedata.begin(); fileIT != filedata.end(); ++fileIT) {
		if((*fileIT).find(";") == string::npos) {
			if((*fileIT) == "[Triggers]\n") {
				string::size_type pos;
				while(1) {
					++fileIT;
					pos = (*fileIT).find("=");
					if(pos != string::npos) {
						string cur_line = (*fileIT);

						string ID = cur_line.substr(0, pos);
						cur_line = cur_line.substr(pos+1);

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

						string isHard_s = cur_line.substr(0, cur_line.find("\n"));
						bool isHard = atoi(isHard_s.c_str());

						triggers[name] = new Trigger(ID, house, attachID, name, isDisabled, isEasy, isMedium, isHard);
					} else {
						break;
					}
					if(fileIT == filedata.end()) { break; }
				}
			} else if ((*fileIT) == "[Tags]\n") {
				string::size_type pos;
				while(1) {
					++fileIT;
					pos = (*fileIT).find("=");
					if(pos != string::npos) {
						string cur_line = (*fileIT);

						string ID = cur_line.substr(0, pos);
						cur_line = cur_line.substr(pos+1);

						int32_t mode = atoi(cur_line.substr(0, cur_line.find(",")).c_str());
						cur_line = cur_line.substr(cur_line.find(",")+1);

						string name = cur_line.substr(0, cur_line.find(","));
						cur_line = cur_line.substr(cur_line.find(",")+1);

						string triggerID = cur_line.substr(0, cur_line.find("\n"));

						tags[name] = new Tag(ID, name, triggerID, mode);
					} else {
						break;
					}
					if(fileIT == filedata.end()) { break; }
				}
			} else if ((*fileIT) == "[Waypoints]\n") {
				string::size_type pos;
				waypoints.clear();
				while(1) {
					++fileIT;
					pos = (*fileIT).find("=");
					if(pos != string::npos) {
						string cur_line = (*fileIT);

						int32_t waypoint = atoi(cur_line.substr(0, pos).c_str());
						waypoints.push_back(waypoint);

					} else {
						break;
					}
					if(fileIT == filedata.end()) { break; }
				}
			} else if ((*fileIT) == "[TeamTypes]\n") {
				string::size_type pos;
				teams.clear();
				while(1) {
					++fileIT;
					pos = (*fileIT).find("=");
					if(pos != string::npos) {
						string cur_line = (*fileIT);

						string teamID = cur_line.substr(pos+1, cur_line.length()-3);
						Team *nTeam = FindNewTeamFromFile(teamID);
						teams[nTeam->getName()] = nTeam;

					} else {
						break;
					}
					if(fileIT == filedata.end()) { break; }
				}
			}
		}
	}
	for(vector<string>::iterator fileIT = filedata.begin(); fileIT != filedata.end(); ++fileIT) {
		if((*fileIT).find(";") == string::npos) {
			if((*fileIT) == "[Events]\n") {
				string::size_type pos;
				while(1) {
					++fileIT;
					pos = (*fileIT).find("=");
					if(pos != string::npos) {
						string cur_line = (*fileIT);

						string ID = cur_line.substr(0, pos);
						cur_line = cur_line.substr(pos+1);

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
								param = atoi(cur_line.substr(0, cur_line.find("\n")).c_str());
							}

							triggers[FindTriggerName(ID)]->addEvent(new Event(eType, param, ID));
						}

					} else {
						break;
					}
					if(fileIT == filedata.end()) { break; }
				}
			} else if ((*fileIT) == "[Actions]\n") {
				string::size_type pos;
				while(1) {
					++fileIT;
					pos = (*fileIT).find("=");
					if(pos != string::npos) {
						string cur_line = (*fileIT);

						string ID = cur_line.substr(0, pos);
						cur_line = cur_line.substr(pos+1);

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
								wPoint = WaypointIDToDec(cur_line.substr(0, cur_line.find("\n")).c_str());
							}

							triggers[FindTriggerName(ID)]->addAction(new Action(ID, aType, wPoint, p1, p2, p3, p4, p5, p6));
						}
					} else {
						break;
					}
					if(fileIT == filedata.end()) { break; }
				}
			}
		}
	}
}

Team *FindNewTeamFromFile(string teamID) {
	for(vector<string>::iterator fileIT = filedata.begin(); fileIT != filedata.end(); ++fileIT) {
		if((*fileIT).find(";") == string::npos) {
			if((*fileIT) == "[" + teamID + "]\n") {

				int max = 0;
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

				while(1) {
					++fileIT;
					if((*fileIT).find("Max=") != string::npos) {
						max = atoi(GetValueStr((*fileIT)).c_str());
					} else if ((*fileIT).find("Full=") != string::npos) {
						full = ConverToBool(GetValueStr((*fileIT)));
					} else if ((*fileIT).find("Name=") != string::npos) {
						name = GetValueStr((*fileIT));
					} else if ((*fileIT).find("Group=") != string::npos) {
						group = atoi(GetValueStr((*fileIT)).c_str());
					} else if ((*fileIT).find("House=") != string::npos) {
						house = GetValueStr((*fileIT));
					} else if ((*fileIT).find("Script=") != string::npos) {
						script = GetValueStr((*fileIT));
					} else if ((*fileIT).find("Whiner=") != string::npos) {
						whiner = ConverToBool(GetValueStr((*fileIT)));
					} else if ((*fileIT).find("Droppod=") != string::npos) {
						droppod = ConverToBool(GetValueStr((*fileIT)));
					} else if ((*fileIT).find("Suicide=") != string::npos) {
						suicide = ConverToBool(GetValueStr((*fileIT)));
					} else if ((*fileIT).find("Loadable=") != string::npos) {
						loadable = ConverToBool(GetValueStr((*fileIT)));
					} else if ((*fileIT).find("Prebuild=") != string::npos) {
						prebuild = ConverToBool(GetValueStr((*fileIT)));
					} else if ((*fileIT).find("Priority=") != string::npos) {
						priority = atoi(GetValueStr((*fileIT)).c_str());
					} else if ((*fileIT).find("Waypoint=") != string::npos) {
						waypoint = GetValueStr((*fileIT));
					} else if ((*fileIT).find("Annoyance=") != string::npos) {
						annoyance = ConverToBool(GetValueStr((*fileIT)));
					} else if ((*fileIT).find("IonImmune=") != string::npos) {
						ionimmune = ConverToBool(GetValueStr((*fileIT)));
					} else if ((*fileIT).find("Recruiter=") != string::npos) {
						recruiter = ConverToBool(GetValueStr((*fileIT)));
					} else if ((*fileIT).find("Reinforce=") != string::npos) {
						reinforce = ConverToBool(GetValueStr((*fileIT)));
					} else if ((*fileIT).find("TaskForce=") != string::npos) {
						taskforce = GetValueStr((*fileIT));
					} else if ((*fileIT).find("TechLevel=") != string::npos) {
						techlevel = atoi(GetValueStr((*fileIT)).c_str());
					} else if ((*fileIT).find("Aggressive=") != string::npos) {
						aggressive = ConverToBool(GetValueStr((*fileIT)));
					} else if ((*fileIT).find("Autocreate=") != string::npos) {
						autocreate = ConverToBool(GetValueStr((*fileIT)));
					} else if ((*fileIT).find("GuardSlower=") != string::npos) {
						guardslower = ConverToBool(GetValueStr((*fileIT)));
					} else if ((*fileIT).find("OnTransOnly=") != string::npos) {
						ontransonly = ConverToBool(GetValueStr((*fileIT)));
					} else if ((*fileIT).find("AvoidThreats=") != string::npos) {
						avoidthreats = ConverToBool(GetValueStr((*fileIT)));
					} else if ((*fileIT).find("LooseRecruit=") != string::npos) {
						looserecruit = ConverToBool(GetValueStr((*fileIT)));
					} else if ((*fileIT).find("VeteranLevel=") != string::npos) {
						veteranlevel = atoi(GetValueStr((*fileIT)).c_str());
					} else if ((*fileIT).find("IsBaseDefense=") != string::npos) {
						isbasedefense = ConverToBool(GetValueStr((*fileIT)));
					} else if ((*fileIT).find("OnlyTargetHouseEnemy=") != string::npos) {
						onlytargethousenemy = ConverToBool(GetValueStr((*fileIT)));
					} else if ((*fileIT).find("TransportsReturnOnUnload=") != string::npos) {
						transportsreturnonunload = ConverToBool(GetValueStr((*fileIT)));
					} else if ((*fileIT).find("AreTeamMembersRecruitable=") != string::npos) {
						areteammembersrecruitable = ConverToBool(GetValueStr((*fileIT)));
					} else {
						break;
					}
				}
				return new Team(teamID, max, full, name, group, house, script, whiner, droppod, suicide,
									loadable, prebuild, priority, waypoint, annoyance, ionimmune, recruiter,
									reinforce, taskforce, techlevel, aggressive, autocreate, guardslower,
									ontransonly, avoidthreats, looserecruit, veteranlevel, isbasedefense,
									onlytargethousenemy, transportsreturnonunload, areteammembersrecruitable);
			}
		}
	}
	return new Team(teamID);
}

string GetValueStr(string line) {
	string::size_type pos;
	pos = line.find("=");
	return line.substr(pos+1);
}

bool isFirstWave(string ID) {
	bool retVal = true;
	triggerIT = triggers.begin();
	if((*triggerIT).second->getID() != ID) {
		retVal = false;
	}
	return retVal;
}

Tag* FindTag(string trigID) {
	for(tagIT = tags.begin(); tagIT != tags.end(); ++tagIT) {
		if((*tagIT).second->getTriggerID() == trigID) {
			return (*tagIT).second;
		}
	}
	return NULL;
}

string DecToWaypointID(int dec) {
	string retVal;
	dec=dec+1;
	while(dec != 0) {
		--dec;
		retVal = alphas[dec % 26] + retVal;
		dec /= 26;
	}
	return retVal;
}

string FindTriggerName(string trigID) {
	for(triggerIT = triggers.begin(); triggerIT != triggers.end(); ++triggerIT) {
		if((*triggerIT).second->getID() == trigID) {
			return (*triggerIT).first;
		}
	}
	return NULL;
}

int32_t WaypointIDToDec(string wID) {
	int32_t value = 0;
	int i = wID.length();
	while(1) {
		if(i == 0) { break; }
		--i;
		const char chr = *wID.substr(i, 1).c_str();
		int32_t multip = 0;
		for(int j = 0; j != 26; ++j) {
			if(chr == alphas[j]) {
				multip = j+1;
				break;
			}
		}
		int p = pow(26.0, int(wID.length() - (i+1)));
		value = value + (multip * p);
	}
	return value-1;
}

void ClearValueAtBuffer(string line) {
	line += "\n";
	for(vector<string>::iterator fileIT = filedata.begin(); fileIT != filedata.end(); ++fileIT) {
		string cur_line = *fileIT;
		if(cur_line.find(";") == string::npos) {
			if((*fileIT) == line) {
				filedata.erase(fileIT);
				return;
			}
		}
	}
}

bool ConverToBool(string str) {
	if(str == "yes") {
		return true;
	}
	if(str == "no") {
		return false;
	}
	if(str == "true") {
		return true;
	}
	if(str == "false") {
		return false;
	}

	return false;
}

int main(int argc, char *argv[])
{
	filedata.clear();
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
