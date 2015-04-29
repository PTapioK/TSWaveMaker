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
CDataFile curdata;

vector <int32_t> waypoints;
vector <int32_t>::iterator waypointIT;

int main(int argc, char *argv[])
{
	curdata.m_Flags |= AUTOCREATE_KEYS;
	curdata.m_Flags |= AUTOCREATE_SECTIONS;
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
