#include "scriptsection.h"
#include "ui_scriptsection.h"

ScriptSection::ScriptSection(QWidget *parent) :
	QDockWidget(parent),
	ui(new Ui::ScriptSection)
{
	ui->setupUi(this);
}

ScriptSection::~ScriptSection()
{
	delete ui;
}



void ScriptSection::on_ScriptList_itemSelectionChanged()
{
	ui->ScriptActionList->setCurrentRow(-1);
	ui->ScriptActionList->clear();
	ui->SATargetBox->setCurrentIndex(-1);

	if(ui->ScriptList->currentRow() != -1) {

		Script *cur_script = GetScriptByName(ui->ScriptList->currentItem()->text().toStdString());

		ui->SNameEdit->setText(ui->ScriptList->currentItem()->text());

		for(std::vector <Script::ScriptLine*>::iterator slineIT = cur_script->slines.begin(); slineIT != cur_script->slines.end(); ++slineIT) {
			stringstream ID;
			ID << (*slineIT)->ID;
			ui->ScriptActionList->addItem(ID.str().c_str());
		}
	}
}

void ScriptSection::on_ScriptActionList_itemSelectionChanged()
{
	if(ui->ScriptList->currentRow() != -1 && ui->ScriptActionList->currentRow() != -1) {
		int index = ui->SATypeBox->findText(GetScriptActionMeaning(GetScriptByName(ui->ScriptList->currentItem()->text().toStdString())->slines[ui->ScriptActionList->currentRow()]->type));
		if(index != -1) {
			ui->SATypeBox->setCurrentIndex(index);
			on_SATypeBox_activated();
		}
	}
}

void ScriptSection::on_SATypeBox_activated()
{
	ui->SATargetBox->clear();
	if(ui->ScriptActionList->currentRow() != -1 && ui->ScriptList->currentRow() != -1) {
		GetScriptByName(ui->ScriptList->currentItem()->text().toStdString())->slines[ui->ScriptActionList->currentRow()]->type = ui->SATypeBox->currentIndex();

		QStringList targetList = GetScriptActionTargetStrings(GetScriptActionTargetType(GetScriptByName(ui->ScriptList->currentItem()->text().toStdString())->slines[ui->ScriptActionList->currentRow()]->type));
		ui->SATargetBox->addItems(targetList);
		ui->SATargetBox->view()->setMinimumWidth(GetStringListMaxWidth(targetList, ui->SATargetBox->font())+50);

		short type = GetScriptByName(ui->ScriptList->currentItem()->text().toStdString())->slines[ui->ScriptActionList->currentRow()]->type;
		if(GetScriptActionTargetType(type) == WAYPOINT) {
			stringstream ss;
			ss << GetScriptByName(ui->ScriptList->currentItem()->text().toStdString())->slines[ui->ScriptActionList->currentRow()]->param;
			ui->SATargetBox->setCurrentIndex(ui->SATargetBox->findText(ss.str().c_str()));
		} else {
			ui->SATargetBox->setCurrentIndex(GetScriptByName(ui->ScriptList->currentItem()->text().toStdString())->slines[ui->ScriptActionList->currentRow()]->param);
		}
	}
}

void ScriptSection::on_SATargetBox_activated()
{
	if(ui->ScriptActionList->currentRow() != -1 && ui->SATargetBox->currentIndex() != -1 && ui->ScriptList->currentRow() != -1) {
		short type = GetScriptByName(ui->ScriptList->currentItem()->text().toStdString())->slines[ui->ScriptActionList->currentRow()]->type;
		if(GetScriptActionTargetType(type) == WAYPOINT) {
			GetScriptByName(ui->ScriptList->currentItem()->text().toStdString())->slines[ui->ScriptActionList->currentRow()]->param = waypoints[ui->SATargetBox->currentIndex()];
		} else {
			GetScriptByName(ui->ScriptList->currentItem()->text().toStdString())->slines[ui->ScriptActionList->currentRow()]->param = ui->SATargetBox->currentIndex();
		}
	}
}

// Clone script and add 1 for all waypoints of actions of script
void ScriptSection::on_CLastButton_clicked()
{
	if(ui->ScriptList->currentRow() != -1) {
		string newName = "Clone Of " + ui->ScriptList->currentItem()->text().toStdString();

		int i = 0;
		while(ui->ScriptList->findItems(newName.c_str(), Qt::MatchExactly).count() != 0) {
			++i;
			stringstream ssI;
			ssI << i;
			newName = "Clone Of " + ui->ScriptList->currentItem()->text().toStdString() + " " + ssI.str();
		}

		Script *cur_script = scripts[GetScriptIDByName(ui->ScriptList->currentItem()->text().toStdString())];

		string newID = fffID();
		scripts[newID] = new Script(newID, cur_script);
		scripts[newID]->setName(newName);
		ui->ScriptList->addItem(newName.c_str());

		vector<Script::ScriptLine*> slines;
		vector<Script::ScriptLine*>::iterator slineIT;

		slines = scripts[newID]->GetLinesByType(WAYPOINT);

		for(slineIT = slines.begin(); slineIT != slines.end(); ++slineIT) {
			(*slineIT)->param = (*slineIT)->param + 1;
		}

	}
}

// New script
void ScriptSection::on_newS_clicked()
{
	if(ui->ScriptList->findItems(ui->SNameEdit->text(), Qt::MatchExactly).count() == 0) {
		string name = ui->SNameEdit->text().toStdString();
		ui->ScriptList->addItem(ui->SNameEdit->text());
		string nID = fffID();
		scripts[nID] = new Script(nID, name);
	}
}

// Delete script
void ScriptSection::on_delS_clicked()
{
	if(ui->ScriptList->currentRow() != -1) {
		string name = ui->ScriptList->currentItem()->text().toStdString();
		string ID = GetScriptIDByName(name);
		delete GetScriptByName(ID);
		scripts.erase(ID);

		delete ui->ScriptList->item(ui->ScriptList->currentRow());
	}
}

// Edit script mame
void ScriptSection::on_editSN_clicked()
{
	if(ui->ScriptList->findItems(ui->SNameEdit->text(), Qt::MatchExactly).count() == 0) {
		string cur_name = ui->ScriptList->currentItem()->text().toStdString();
		string cur_ID = GetScriptIDByName(cur_name);

		scripts[cur_ID]->setName(ui->SNameEdit->text().toStdString());

		ui->ScriptList->currentItem()->setText(ui->SNameEdit->text());
	}
}

// Clone script
void ScriptSection::on_cloneS_clicked()
{
	if(ui->ScriptList->currentRow() != -1) {
		string newName = "Clone Of " + ui->ScriptList->currentItem()->text().toStdString();

		int i = 0;
		while(ui->ScriptList->findItems(newName.c_str(), Qt::MatchExactly).count() != 0) {
			++i;
			stringstream ssI;
			ssI << i;
			newName = "Clone Of " + ui->ScriptList->currentItem()->text().toStdString() + " " + ssI.str();
		}
		string newID = fffID();
		scripts[newID] = new Script(newID, scripts[GetScriptIDByName(ui->ScriptList->currentItem()->text().toStdString())]);
		scripts[newID]->setName(newName);
		ui->ScriptList->addItem(newName.c_str());
	}
}

// New script action
void ScriptSection::on_newSA_clicked()
{
	if(ui->ScriptList->currentRow() != -1) {
		Script *cur_script = scripts[GetScriptIDByName(ui->ScriptList->currentItem()->text().toStdString())];
		cur_script->NewLine(0, 0);
		stringstream ID;
		ID << (*(cur_script->slines.end()-1))->ID;
		ui->ScriptActionList->addItem(ID.str().c_str());
	}
}

// Delete script action
void ScriptSection::on_delSA_clicked()
{
	if(ui->ScriptActionList->currentRow() != -1) {

		int row = ui->ScriptActionList->currentRow();

		delete ui->ScriptActionList->item(ui->ScriptActionList->currentRow());

		Script *cur_script = scripts[GetScriptIDByName(ui->ScriptList->currentItem()->text().toStdString())];
		cur_script->DeleteLine(row);

		ui->ScriptActionList->clear();
		for(std::vector <Script::ScriptLine*>::iterator slineIT = cur_script->slines.begin(); slineIT != cur_script->slines.end(); ++slineIT) {
			stringstream ID;
			ID << (*slineIT)->ID;
			ui->ScriptActionList->addItem(ID.str().c_str());
		}
	}
}

void ScriptSection::UpdateUi() {
	for(scriptIT = scripts.begin(); scriptIT != scripts.end(); ++scriptIT) {
		ui->ScriptList->addItem(scriptIT->second->getName().c_str());
	}
	for(int i = 0; i != 54; ++i) {
		ui->SATypeBox->addItem(GetScriptActionMeaning(i));
	}
}
