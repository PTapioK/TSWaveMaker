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
			ui->scriptBox->addItem(IT->second->getName());
		}

		ui->AOSBox->clear();
		for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
			ui->AOSBox->addItem(IT->second->getName());
		}
		ui->AOEBox->clear();
		for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
			ui->AOEBox->addItem(IT->second->getName());
		}

		ui->taskforceBox->clear();
		for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
			ui->taskforceBox->addItem(IT->second->getName());
		}

		ui->TNameEdit->setText(ui->TeamList->selectedItems().last()->text());

		Team *curTeam = getTeamByName(ui->TeamList->selectedItems().last()->text());

		ui->isSuicide->setChecked(curTeam->suicide);
		ui->isLoadable->setChecked(curTeam->loadable);
		ui->isAreTeamMembersRecruitable->setChecked(curTeam->areteammembersrecruitable);
		ui->isAggressive->setChecked(curTeam->aggressive);
		ui->isAutocreate->setChecked(curTeam->autocreate);
		ui->isAvoidThreats->setChecked(curTeam->avoidthreats);
		ui->isDroppod->setChecked(curTeam->droppod);
		ui->isFull->setChecked(curTeam->full);
		ui->isIsBaseDefense->setChecked(curTeam->isbasedefense);
		ui->isOnlyTargetHouseEnemy->setChecked(curTeam->onlytargethousenemy);
		ui->isReinforce->setChecked(curTeam->reinforce);
		ui->isTransportsReturnOnUnload->setChecked(curTeam->transportsreturnonunload);
		ui->isAnnoyance->setChecked(curTeam->annoyance);
		ui->isGuardSlower->setChecked(curTeam->guardslower);
		ui->isIonImmune->setChecked(curTeam->ionimmune);
		ui->isLooseRecruit->setChecked(curTeam->looserecruit);
		ui->isOnTransOnly->setChecked(curTeam->ontransonly);
		ui->isPrebuild->setChecked(curTeam->prebuild);
		ui->isRecruiter->setChecked(curTeam->recruiter);
		ui->isWhiner->setChecked(curTeam->whiner);

		ui->scriptBox->setCurrentIndex(ui->scriptBox->findText(getScriptNameByID(curTeam->scriptID)));
		ui->taskforceBox->setCurrentIndex(ui->taskforceBox->findText(getTaskforceNameByID(curTeam->taskForceID)));
	}
}

// New team
void TeamSection::on_New_clicked()
{
	if(ui->TeamList->findItems(ui->TNameEdit->text(), Qt::MatchExactly).count() == 0) {
		QString name = ui->TNameEdit->text();
		ui->TeamList->addItem(ui->TNameEdit->text());
		QString nID = findFirstFreeID();
		teams[nID] = new Team(nID, name);

	}
}

// Delete team(s)
void TeamSection::on_Delete_clicked()
{
	if(ui->TeamList->selectedItems().size() != 0) {
		for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
			QString name = ui->TeamList->selectedItems().at(a)->text();
			QString ID = getTeamIDByName(name);
			delete getTeamByName(name);
			teams.erase(ID);
		}
		updateUi();
	}
}

// Edit team's name
void TeamSection::on_EditName_clicked()
{
	if(ui->TeamList->selectedItems().size() != 0) {
		if(ui->TeamList->findItems(ui->TNameEdit->text(), Qt::MatchExactly).count() == 0) {
			QString curName = ui->TeamList->selectedItems().last()->text();
			QString curID = getTeamIDByName(curName);

			teams[curID]->setName(ui->TNameEdit->text());

			ui->TeamList->selectedItems().last()->setText(ui->TNameEdit->text());
		}
	}
}

// Clone team(s)
void TeamSection::on_Clone_clicked()
{
	if(ui->TeamList->selectedItems().size() != 0) {
		for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
			QString newName = getNameWithNextMark(ui->TeamList->selectedItems().at(a)->text(), a, 0);

			int i = 0;
			while(ui->TeamList->findItems(newName, Qt::MatchExactly).count() != 0) {
				++i;
				newName = getNameWithNextMark(ui->TeamList->selectedItems().at(a)->text(), i);
			}
			QString newID = findFirstFreeID();
			teams[newID] = new Team(newID, getTeamByName(ui->TeamList->selectedItems().at(a)->text()));
			teams[newID]->setName(newName);
			ui->TeamList->addItem(newName);
		}
	}
}

void TeamSection::on_isSuicide_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text())->suicide = ui->isSuicide->isChecked();
	}
}

void TeamSection::on_isLoadable_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text())->loadable = ui->isLoadable->isChecked();
	}
}
void TeamSection::on_isAreTeamMembersRecruitable_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text())->areteammembersrecruitable = ui->isAreTeamMembersRecruitable->isChecked();
	}
}
void TeamSection::on_isTransportsReturnOnUnload_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text())->transportsreturnonunload = ui->isTransportsReturnOnUnload->isChecked();
	}
}
void TeamSection::on_isReinforce_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text())->reinforce = ui->isReinforce->isChecked();
	}
}
void TeamSection::on_isDroppod_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text())->droppod = ui->isDroppod->isChecked();
	}
}
void TeamSection::on_isAutocreate_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text())->autocreate = ui->isAutocreate->isChecked();
	}
}
void TeamSection::on_isOnlyTargetHouseEnemy_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text())->onlytargethousenemy = ui->isOnlyTargetHouseEnemy->isChecked();
	}
}
void TeamSection::on_isAggressive_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text())->aggressive = ui->isAggressive->isChecked();
	}
}
void TeamSection::on_isFull_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text())->full = ui->isFull->isChecked();
	}
}
void TeamSection::on_isAvoidThreats_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text())->avoidthreats = ui->isAvoidThreats->isChecked();
	}
}
void TeamSection::on_isIsBaseDefense_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text())->isbasedefense = ui->isIsBaseDefense->isChecked();
	}
}

void TeamSection::on_isAnnoyance_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text())->annoyance = ui->isAnnoyance->isChecked();
	}
}

void TeamSection::on_isGuardSlower_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text())->guardslower = ui->isGuardSlower->isChecked();
	}
}

void TeamSection::on_isIonImmune_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text())->ionimmune = ui->isIonImmune->isChecked();
	}
}

void TeamSection::on_isLooseRecruit_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text())->looserecruit = ui->isLooseRecruit->isChecked();
	}
}

void TeamSection::on_isOnTransOnly_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text())->ontransonly = ui->isOnTransOnly->isChecked();
	}
}

void TeamSection::on_isPrebuild_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text())->prebuild = ui->isPrebuild->isChecked();
	}
}

void TeamSection::on_isRecruiter_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text())->recruiter = ui->isRecruiter->isChecked();
	}
}

void TeamSection::on_isWhiner_clicked()
{
	for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
		getTeamByName(ui->TeamList->selectedItems().at(a)->text())->whiner = ui->isWhiner->isChecked();
	}
}

void TeamSection::mousePressEvent(QMouseEvent *event)
{
	event->accept();
}

// Script for teams
void TeamSection::on_scriptBox_activated()
{
	if(ui->TeamList->selectedItems().size() != 0) {
		for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
			getTeamByName(ui->TeamList->selectedItems().at(a)->text())->scriptID = getScriptIDByName(ui->scriptBox->currentText());
		}
	}
}

// Taskforce for teams
void TeamSection::on_taskforceBox_activated()
{
	if(ui->TeamList->selectedItems().size() != 0) {
		for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {
			getTeamByName(ui->TeamList->selectedItems().at(a)->text())->taskForceID = getTaskforceIDByName(ui->taskforceBox->currentText());
		}
	}
}

// Make Teams use scripts in ascending order
void TeamSection::on_SAOButton_clicked()
{
	if(ui->TeamList->selectedItems().size() != 0) {

		std::vector<Script*> temp;
		std::vector<Script*>::iterator tempIT;

		scriptIT IT = scripts.find(getScriptIDByName(ui->AOSBox->currentText()));
		do {
			temp.push_back(IT->second);
			if(IT == scripts.find(getScriptIDByName(ui->AOEBox->currentText()))) { break; }
			++IT;
			if(IT == scripts.end()) { break; }
		} while (1);

		tempIT = temp.begin();

		for(int a = 0; a != ui->TeamList->selectedItems().size(); ++a) {

			Team *curTeam = getTeamByName(ui->TeamList->selectedItems().at(a)->text());

			curTeam->scriptID = (*tempIT)->getID();

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
		ui->TeamList->addItem(IT->second->getName());
	}
}
