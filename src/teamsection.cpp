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
	if(ui->TeamList->selectedItems().size() != 0) {
		ui->scriptBox->clear();
		for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
			ui->scriptBox->addItem(IT->second->getName().c_str());
		}

		ui->AOSBox->clear();
		for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
			ui->AOSBox->addItem(IT->second->getName().c_str());
		}
		ui->AOEBox->clear();
		for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
			ui->AOEBox->addItem(IT->second->getName().c_str());
		}

		ui->taskforceBox->clear();
		for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
			ui->taskforceBox->addItem(IT->second->getName().c_str());
		}

		ui->TNameEdit->setText(ui->TeamList->selectedItems().last()->text());

		Team *cur_team = getTeamByName(ui->TeamList->selectedItems().last()->text().toStdString());

		ui->isSuicide->setChecked(cur_team->suicide);
		ui->isLoadable->setChecked(cur_team->loadable);
		ui->isAreTeamMembersRecruitable->setChecked(cur_team->areteammembersrecruitable);
		ui->isAggressive->setChecked(cur_team->aggressive);
		ui->isAutocreate->setChecked(cur_team->autocreate);
		ui->isAvoidThreats->setChecked(cur_team->avoidthreats);
		ui->isDroppod->setChecked(cur_team->droppod);
		ui->isFull->setChecked(cur_team->full);
		ui->isIsBaseDefense->setChecked(cur_team->isbasedefense);
		ui->isOnlyTargetHouseEnemy->setChecked(cur_team->onlytargethousenemy);
		ui->isReinforce->setChecked(cur_team->reinforce);
		ui->isTransportsReturnOnUnload->setChecked(cur_team->transportsreturnonunload);
		ui->isAnnoyance->setChecked(cur_team->annoyance);
		ui->isGuardSlower->setChecked(cur_team->guardslower);
		ui->isIonImmune->setChecked(cur_team->ionimmune);
		ui->isLooseRecruit->setChecked(cur_team->looserecruit);
		ui->isOnTransOnly->setChecked(cur_team->ontransonly);
		ui->isPrebuild->setChecked(cur_team->prebuild);
		ui->isRecruiter->setChecked(cur_team->recruiter);
		ui->isWhiner->setChecked(cur_team->whiner);

		ui->scriptBox->setCurrentIndex(ui->scriptBox->findText(getScriptNameByID(cur_team->scriptID).c_str()));
		ui->taskforceBox->setCurrentIndex(ui->taskforceBox->findText(getTaskforceNameByID(cur_team->taskForceID).c_str()));
	}
}

// New team
void TeamSection::on_New_clicked()
{
	if(ui->TeamList->findItems(ui->TNameEdit->text(), Qt::MatchExactly).count() == 0) {
		std::string name = ui->TNameEdit->text().toStdString();
		ui->TeamList->addItem(ui->TNameEdit->text());
		std::string nID = fffID();
		teams[nID] = new Team(nID, name);

	}
}

// Delete team(s)
void TeamSection::on_Delete_clicked()
{
	if(ui->TeamList->selectedItems().size() != 0) {
		for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
			std::string name = ui->TeamList->selectedItems().at(a)->text().toStdString();
			std::string ID = getTeamIDByName(name);
			delete getTeamByName(name);
			teams.erase(ID);
		}
		updateUi();
	}
}

// Edit team's name
void TeamSection::on_EditName_clicked()
{
	if(ui->TeamList->findItems(ui->TNameEdit->text(), Qt::MatchExactly).count() == 0) {
		std::string cur_name = ui->TeamList->selectedItems().last()->text().toStdString();
		std::string cur_ID = getTeamIDByName(cur_name);

		teams[cur_ID]->setName(ui->TNameEdit->text().toStdString());

		ui->TeamList->selectedItems().last()->setText(ui->TNameEdit->text());
	}
}

// Clone team(s)
void TeamSection::on_Clone_clicked()
{
	if(ui->TeamList->selectedItems().size() != 0) {
		for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
			std::string newName = getNameWithNextMark(ui->TeamList->selectedItems().at(a)->text().toStdString(), a, 0);

			int i = 0;
			while(ui->TeamList->findItems(newName.c_str(), Qt::MatchExactly).count() != 0) {
				++i;
				newName = getNameWithNextMark(ui->TeamList->selectedItems().at(a)->text().toStdString(), i);
			}
			std::string newID = fffID();
			teams[newID] = new Team(newID, getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString()));
			teams[newID]->setName(newName);
			ui->TeamList->addItem(newName.c_str());
		}
	}
}

void TeamSection::on_isSuicide_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->suicide = ui->isSuicide->isChecked();
	}
}

void TeamSection::on_isLoadable_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->loadable = ui->isLoadable->isChecked();
	}
}
void TeamSection::on_isAreTeamMembersRecruitable_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->areteammembersrecruitable = ui->isAreTeamMembersRecruitable->isChecked();
	}
}
void TeamSection::on_isTransportsReturnOnUnload_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->transportsreturnonunload = ui->isTransportsReturnOnUnload->isChecked();
	}
}
void TeamSection::on_isReinforce_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->reinforce = ui->isReinforce->isChecked();
	}
}
void TeamSection::on_isDroppod_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->droppod = ui->isDroppod->isChecked();
	}
}
void TeamSection::on_isAutocreate_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->autocreate = ui->isAutocreate->isChecked();
	}
}
void TeamSection::on_isOnlyTargetHouseEnemy_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->onlytargethousenemy = ui->isOnlyTargetHouseEnemy->isChecked();
	}
}
void TeamSection::on_isAggressive_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->aggressive = ui->isAggressive->isChecked();
	}
}
void TeamSection::on_isFull_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->full = ui->isFull->isChecked();
	}
}
void TeamSection::on_isAvoidThreats_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->avoidthreats = ui->isAvoidThreats->isChecked();
	}
}
void TeamSection::on_isIsBaseDefense_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->isbasedefense = ui->isIsBaseDefense->isChecked();
	}
}

void TeamSection::on_isAnnoyance_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->annoyance = ui->isAnnoyance->isChecked();
	}
}

void TeamSection::on_isGuardSlower_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->guardslower = ui->isGuardSlower->isChecked();
	}
}

void TeamSection::on_isIonImmune_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->ionimmune = ui->isIonImmune->isChecked();
	}
}

void TeamSection::on_isLooseRecruit_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->looserecruit = ui->isLooseRecruit->isChecked();
	}
}

void TeamSection::on_isOnTransOnly_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->ontransonly = ui->isOnTransOnly->isChecked();
	}
}

void TeamSection::on_isPrebuild_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->prebuild = ui->isPrebuild->isChecked();
	}
}

void TeamSection::on_isRecruiter_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->recruiter = ui->isRecruiter->isChecked();
	}
}

void TeamSection::on_isWhiner_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->whiner = ui->isWhiner->isChecked();
	}
}

void TeamSection::mousePressEvent(QMouseEvent *event)
{
	event->accept();
	ui->TeamList->clearSelection();
}

// Script for teams
void TeamSection::on_scriptBox_activated()
{
	if(ui->TeamList->selectedItems().size() != 0) {
		for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
			getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->scriptID = getScriptIDByName(ui->scriptBox->currentText().toStdString());
		}
	}
}

// Taskforce for teams
void TeamSection::on_taskforceBox_activated()
{
	if(ui->TeamList->selectedItems().size() != 0) {
		for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
			getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString())->taskForceID = getTaskforceIDByName(ui->taskforceBox->currentText().toStdString());
		}
	}
}

// Make Teams use scripts in ascending order
void TeamSection::on_SAOButton_clicked()
{
	if(ui->TeamList->selectedItems().size() != 0) {

		std::vector<Script*> temp;
		std::vector<Script*>::iterator tempIT;

		scriptIT IT = scripts.find(getScriptIDByName(ui->AOSBox->currentText().toStdString()));
		do {
			temp.push_back(IT->second);
			if(IT == scripts.find(getScriptIDByName(ui->AOEBox->currentText().toStdString()))) { break; }
			++IT;
		} while (1);

		tempIT = temp.begin();

		for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {

			Team *cur_team = getTeamByName(ui->TeamList->selectedItems().at(a)->text().toStdString());

			cur_team->scriptID = (*tempIT)->getID();

			if(tempIT != temp.end()-1) {
				++tempIT;
			} else {
				tempIT = temp.begin();
			}
		}
	}
}

void TeamSection::updateUi()
{
	ui->TeamList->clearSelection();
	ui->TeamList->clear();
	for(teamIT IT = teams.begin(); IT != teams.end(); ++IT) {
		ui->TeamList->addItem(IT->second->getName().c_str());
	}
}
