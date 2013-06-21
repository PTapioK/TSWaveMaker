#include "teamsection.h"
#include "ui_teamsection.h"

TeamSection::TeamSection(QWidget *parent) :
	QDockWidget(parent),
	ui(new Ui::TeamSection)
{
	ui->setupUi(this);
}

TeamSection::~TeamSection()
{
	delete ui;
}

void TeamSection::on_TeamList_itemSelectionChanged()
{

	ui->scriptBox->clear();
	for(scriptIT = scripts.begin(); scriptIT != scripts.end(); ++scriptIT) {
		ui->scriptBox->addItem(scriptIT->second->getName().c_str());
	}

	ui->AOSBox->clear();
	for(scriptIT = scripts.begin(); scriptIT != scripts.end(); ++scriptIT) {
		ui->AOSBox->addItem(scriptIT->second->getName().c_str());
	}
	ui->AOEBox->clear();
	for(scriptIT = scripts.begin(); scriptIT != scripts.end(); ++scriptIT) {
		ui->AOEBox->addItem(scriptIT->second->getName().c_str());
	}

	ui->taskforceBox->clear();
	for(taskforceIT = taskforces.begin(); taskforceIT != taskforces.end(); ++taskforceIT) {
		ui->taskforceBox->addItem(taskforceIT->second->getName().c_str());
	}

	ui->TNameEdit->setText(ui->TeamList->currentItem()->text());

	ui->isSuicde->setChecked(GetTeamByName(ui->TeamList->currentItem()->text().toStdString())->suicide);
	ui->isLoadable->setChecked(GetTeamByName(ui->TeamList->currentItem()->text().toStdString())->loadable);
	ui->isAreTeamMembersRecruitable->setChecked(GetTeamByName(ui->TeamList->currentItem()->text().toStdString())->areteammembersrecruitable);
	ui->isAggressive->setChecked(GetTeamByName(ui->TeamList->currentItem()->text().toStdString())->aggressive);
	ui->isAutocreate->setChecked(GetTeamByName(ui->TeamList->currentItem()->text().toStdString())->autocreate);
	ui->isAvoidThreats->setChecked(GetTeamByName(ui->TeamList->currentItem()->text().toStdString())->avoidthreats);
	ui->isDroppod->setChecked(GetTeamByName(ui->TeamList->currentItem()->text().toStdString())->droppod);
	ui->isFull->setChecked(GetTeamByName(ui->TeamList->currentItem()->text().toStdString())->full);
	ui->isIsBaseDefense->setChecked(GetTeamByName(ui->TeamList->currentItem()->text().toStdString())->isbasedefense);
	ui->isOnlyTargetHouseEnemy->setChecked(GetTeamByName(ui->TeamList->currentItem()->text().toStdString())->onlytargethousenemy);
	ui->isReinforce->setChecked(GetTeamByName(ui->TeamList->currentItem()->text().toStdString())->reinforce);
	ui->isTransportsReturnOnUnload->setChecked(GetTeamByName(ui->TeamList->currentItem()->text().toStdString())->transportsreturnonunload);

	ui->scriptBox->setCurrentIndex(ui->scriptBox->findText(GetScriptNameByID(GetTeamByName(ui->TeamList->currentItem()->text().toStdString())->scriptID).c_str()));
	ui->taskforceBox->setCurrentIndex(ui->taskforceBox->findText(GetTaskforceNameByID(GetTeamByName(ui->TeamList->currentItem()->text().toStdString())->taskForceID).c_str()));
}

// New team
void TeamSection::on_New_clicked()
{
	if(ui->TeamList->findItems(ui->TNameEdit->text(), Qt::MatchExactly).count() == 0) {
		string name = ui->TNameEdit->text().toStdString();
		ui->TeamList->addItem(ui->TNameEdit->text());
		string nID = fffID();
		teams[nID] = new Team(nID, name);

	}
}

// Delete team
void TeamSection::on_Delete_clicked()
{
	if(ui->TeamList->currentRow() != -1) {
		string name = ui->TeamList->currentItem()->text().toStdString();
		string ID = GetTeamIDByName(name);
		delete GetTeamByName(name);
		teams.erase(ID);

		delete ui->TeamList->item(ui->TeamList->currentRow());
	}
}

// Edit team's name
void TeamSection::on_EditName_clicked()
{
	if(ui->TeamList->findItems(ui->TNameEdit->text(), Qt::MatchExactly).count() == 0) {
		string cur_name = ui->TeamList->currentItem()->text().toStdString();
		string cur_ID = GetTeamIDByName(cur_name);

		teams[cur_ID]->setName(ui->TNameEdit->text().toStdString());

		ui->TeamList->currentItem()->setText(ui->TNameEdit->text());
	}
}

// Clone team
void TeamSection::on_Clone_clicked()
{
	if(ui->TeamList->currentRow() != -1) {
		string newName = "Clone Of " + ui->TeamList->currentItem()->text().toStdString();

		int i = 0;
		while(ui->TeamList->findItems(newName.c_str(), Qt::MatchExactly).count() != 0) {
			++i;
			stringstream ssI;
			ssI << i;
			newName = "Clone Of " + ui->TeamList->currentItem()->text().toStdString() + " " + ssI.str();
		}
		string newID = fffID();
		teams[newID] = new Team(newID, teams[GetTeamIDByName(ui->TeamList->currentItem()->text().toStdString())]);
		teams[newID]->setName(newName);
		ui->TeamList->addItem(newName.c_str());
	}
}

void TeamSection::on_isSuicde_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->suicide = ui->isSuicde->isChecked();
	}
}

void TeamSection::on_isLoadable_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->loadable = ui->isLoadable->isChecked();
	}
}
void TeamSection::on_isAreTeamMembersRecruitable_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->areteammembersrecruitable = ui->isAreTeamMembersRecruitable->isChecked();
	}
}
void TeamSection::on_isTransportsReturnOnUnload_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->transportsreturnonunload = ui->isTransportsReturnOnUnload->isChecked();
	}
}
void TeamSection::on_isReinforce_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->reinforce = ui->isReinforce->isChecked();
	}
}
void TeamSection::on_isDroppod_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->droppod = ui->isDroppod->isChecked();
	}
}
void TeamSection::on_isAutocreate_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->autocreate = ui->isAutocreate->isChecked();
	}
}
void TeamSection::on_isOnlyTargetHouseEnemy_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->onlytargethousenemy = ui->isOnlyTargetHouseEnemy->isChecked();
	}
}
void TeamSection::on_isAggressive_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->aggressive = ui->isAggressive->isChecked();
	}
}
void TeamSection::on_isFull_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->full = ui->isFull->isChecked();
	}
}
void TeamSection::on_isAvoidThreats_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->avoidthreats = ui->isAvoidThreats->isChecked();
	}
}
void TeamSection::on_isIsBaseDefense_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->isbasedefense = ui->isIsBaseDefense->isChecked();
	}
}


// Script for teams
void TeamSection::on_scriptBox_activated()
{
	if(ui->TeamList->currentRow() != -1) {
		for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
			GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->scriptID = GetScriptIDByName(ui->scriptBox->currentText().toStdString());
		}
	}
}

// Taskforce for teams
void TeamSection::on_taskforceBox_activated()
{
	if(ui->TeamList->currentRow() != -1) {
		for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
			GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->taskForceID = GetTaskforceIDByName(ui->taskforceBox->currentText().toStdString());
		}
	}
}

// Make Teams use scripts in ascending order
void TeamSection::on_SAOButton_clicked()
{
	if(ui->TeamList->currentRow() != -1) {

		vector<Script*> temp;
		vector<Script*>::iterator tempIT;

		map<string, Script*>::iterator scriptI = scripts.find(GetScriptIDByName(ui->AOSBox->currentText().toStdString()));
		do {
			temp.push_back(scriptI->second);
			if(scriptI == scripts.find(GetScriptIDByName(ui->AOEBox->currentText().toStdString()))) { break; }
			++scriptI;
		} while (1);

		tempIT = temp.begin();

		for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {

			Team *cur_team = GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString());

			cur_team->scriptID = (*tempIT)->getID();

			if(tempIT != temp.end()-1) {
				++tempIT;
			} else {
				tempIT = temp.begin();
			}
		}
	}
}

void TeamSection::UpdateUi() {
	ui->TeamList->clear();
	for(teamIT = teams.begin(); teamIT != teams.end(); ++teamIT) {
		ui->TeamList->addItem(teamIT->second->getName().c_str());
	}
}
