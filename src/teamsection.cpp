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
		delete GetTeamByName(ID);
		teams.erase(GetTeamIDByName(ID));

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

void TeamSection::on_isSuicde_stateChanged(int arg1)
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->suicide = arg1;
	}
}
void TeamSection::on_isLoadable_stateChanged(int arg1)
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->loadable = arg1;
	}
}
void TeamSection::on_isAreTeamMembersRecruitable_stateChanged(int arg1)
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->areteammembersrecruitable = arg1;
	}
}
void TeamSection::on_isTransportsReturnOnUnload_stateChanged(int arg1)
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->transportsreturnonunload = arg1;
	}
}
void TeamSection::on_isReinforce_stateChanged(int arg1)
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->reinforce = arg1;
	}
}

void TeamSection::on_isDroppod_stateChanged(int arg1)
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->droppod = arg1;
	}
}
void TeamSection::on_isAutocreate_stateChanged(int arg1)
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->autocreate = arg1;
	}
}
void TeamSection::on_isOnlyTargetHouseEnemy_stateChanged(int arg1)
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->onlytargethousenemy = arg1;
	}
}
void TeamSection::on_isAggressive_stateChanged(int arg1)
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->aggressive = arg1;
	}
}
void TeamSection::on_isFull_stateChanged(int arg1)
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->full = arg1;
	}
}
void TeamSection::on_isAvoidThreats_stateChanged(int arg1)
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->avoidthreats = arg1;
	}
}
void TeamSection::on_isIsBaseDefense_stateChanged(int arg1)
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		GetTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->isbasedefense = arg1;
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

void TeamSection::UpdateUi() {
	ui->TeamList->clear();
	for(teamIT = teams.begin(); teamIT != teams.end(); ++teamIT) {
		ui->TeamList->addItem(teamIT->second->getName().c_str());
	}
}
