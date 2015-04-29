#include "triggersection.h"
#include "ui_triggersection.h"

TriggerSection::TriggerSection(QWidget *parent) :
	QDockWidget(parent),
	ui(new Ui::TriggerSection)
{
	ui->setupUi(this);
	sWPoint = 8; // Starting waypoint for "Make waypoints grow in ascending order in all actions"
}

TriggerSection::~TriggerSection()
{
	delete ui;
}


void TriggerSection::on_TriggerList_itemSelectionChanged()
{
	ui->TimerSetLabel->setText("Not set");
	ui->WaveTimer->setTime(QTime(0, 0, 0));

	clearActionList();
	if(ui->TriggerList->currentRow() != -1) {
		string trig_name = ui->TriggerList->currentItem()->text().toStdString();
		Trigger *cur_trig = GetTriggerByName(trig_name);
		if(cur_trig == NULL) {
			if(QMessageBox::question(this, "Fatal Error!", "Fatal Error occured! Continue?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::No) {
				exit(EXIT_FAILURE);
			}
		}

		ui->NEdit->setText(ui->TriggerList->currentItem()->text());
		ui->isDisabledCheck->setChecked(cur_trig->isDis());

		if(!isFirstTrigger(cur_trig->getID()) && cur_trig->hasEventType(14)) {
			Trigger* prev_trig = FindNearestTimerTrigger(cur_trig->getID());
			if(prev_trig != NULL) {
				int32_t secs = atoi(prev_trig->getActionByType(27)->p2.c_str());
				QTime time(0, 0, 0);
				time = time.addSecs(secs);
				ui->WaveTimer->setTime(time);
				ui->TimerSetLabel->setText("Set");
			}
		}

		int i = 0;
		for(actionIT = cur_trig->actions.begin(); actionIT != cur_trig->actions.end(); ++actionIT) {
			++i;
			stringstream iSS;
			iSS << i;
			QString text = "Action ";
			text += iSS.str().c_str();

			ui->ActionList->addItem(text);
		}

	} else {
		ui->NEdit->setText("");
	}

	ui->WaypointBox->clear();
	ui->SWaypointBox->clear();
	for(waypointIT = waypoints.begin(); waypointIT != waypoints.end(); ++waypointIT) {
		stringstream wSS;
		wSS << (*waypointIT);
		ui->WaypointBox->addItem(wSS.str().c_str());
		ui->SWaypointBox->addItem(wSS.str().c_str());
	}

}

// New trigger
void TriggerSection::on_NewTrigger_clicked()
{
	if(ui->TriggerList->findItems(ui->NEdit->text(), Qt::MatchExactly).count() == 0) {
		string name = ui->NEdit->text().toStdString();
		ui->TriggerList->addItem(ui->NEdit->text());
		string nID = fffID();
		triggers[nID] = new Trigger(nID, name);
		tags[name + " 1"] = new Tag(name + " 1", triggers[nID]->getID());
	}
	UpdateUi();
}

// Edit trigger name
void TriggerSection::on_EditTriggerName_clicked()
{
	if(ui->TriggerList->findItems(ui->NEdit->text(), Qt::MatchExactly).count() == 0) {
		string cur_name = ui->TriggerList->currentItem()->text().toStdString();
		string cur_ID = GetTriggerIDByName(cur_name);

		triggers[cur_ID]->setName(ui->NEdit->text().toStdString());

		ui->TriggerList->currentItem()->setText(ui->NEdit->text());
	}
}

// Is disabled
void TriggerSection::on_isDisabledCheck_clicked()
{
	if(ui->TriggerList->currentRow() != -1) {
		GetTriggerByName(ui->TriggerList->currentItem()->text().toStdString())->setDis(ui->isDisabledCheck->isChecked());
	}
}

// Delete trigger
void TriggerSection::on_DeleteTrigger_clicked()
{
	if(ui->TriggerList->currentRow() != -1) {
		string name = ui->TriggerList->currentItem()->text().toStdString();
		string ID = GetTriggerIDByName(name);
		delete GetTriggerByName(name);
		triggers.erase(ID);
		delete tags[name + " 1"];
		tags.erase(name + " 1");

		delete ui->TriggerList->item(ui->TriggerList->currentRow());
	}

}

// Clone trigger
void TriggerSection::on_CloneTrigger_clicked()
{
	if(ui->TriggerList->currentRow() != -1) {
		string newName = "Clone Of " + ui->TriggerList->currentItem()->text().toStdString();

		int i = 0;
		while(ui->TriggerList->findItems(newName.c_str(), Qt::MatchExactly).count() != 0) {
			++i;
			stringstream ssI;
			ssI << i;
			newName = "Clone Of " + ui->TriggerList->currentItem()->text().toStdString() + " " + ssI.str();
		}
		string newID = fffID();
		triggers[newID] = new Trigger(newID, GetTriggerByName(ui->TriggerList->currentItem()->text().toStdString()));
		triggers[newID]->setName(newName);
		ui->TriggerList->addItem(newName.c_str());
		Tag *cTag = FindTag(GetTriggerByName(ui->TriggerList->currentItem()->text().toStdString())->getID());
		tags[newName + " 1"] = new Tag(cTag, triggers[newID]->getID());
		tags[newName + " 1"]->setName(newName + " 1");
	}
	UpdateUi();
}

void TriggerSection::on_WaveTimer_editingFinished()
{
	if(ui->TriggerList->currentRow() != -1) {
		string trig_name = ui->TriggerList->currentItem()->text().toStdString();
		string trig_ID = GetTriggerIDByName(trig_name);
		int32_t secs = 0;
		secs = abs(ui->WaveTimer->time().secsTo(QTime(0, 0)));

		Trigger *cur_trig = GetTriggerByName(trig_name);

		if(isFirstTrigger(trig_ID)) {

			if(GetTriggerByName("TimerFor1stWave") == NULL) {

				int32_t curTrigID = atoi(trig_ID.c_str());
				stringstream idForNewTrig;
				idForNewTrig << "0" << (curTrigID-2);
				stringstream idForNewTag;
				idForNewTag << "0" << (curTrigID-1);

				triggers[idForNewTrig.str().c_str()] = new Trigger(idForNewTrig.str().c_str(), "Neutral", "<none>", "TimerFor1stWave", false, true, true, true);
				tags["TimerFor1stWave 1"] = new Tag(idForNewTag.str().c_str(), "TimerFor1stWave 1", triggers[idForNewTrig.str().c_str()]->getID(), 0);
				Event *nEvent = new Event(8, 0, triggers[idForNewTrig.str().c_str()]->getID());
				triggers[idForNewTrig.str().c_str()]->addEvent(nEvent);
				Action *nAction = new Action(triggers[idForNewTrig.str().c_str()]->getID(), 27, 0, 0, secs, 0, 0, 0, 0);
				triggers[idForNewTrig.str().c_str()]->addAction(nAction);

				if(!cur_trig->hasEventType(14)) {

					Event *nEvent = new Event(14, 0, cur_trig->getID());
					cur_trig->addEvent(nEvent);
				}

				ui->TriggerList->addItem("TimerFor1stWave");
				ui->TimerSetLabel->setText("Set");
				UpdateUi();
			}
		} else {

			map <string, Trigger*>::iterator triggerIT = triggers.find(trig_ID);
			if(triggerIT == triggers.end()) {
				if(QMessageBox::question(this, "Fatal Error!", "Fatal Error occured! Continue?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::No) {
					exit(EXIT_FAILURE);
				}
			}
			--triggerIT;
			Trigger *prev_trig = (*triggerIT).second;

			if(!cur_trig->hasEventType(14)) {

				Event *nEvent = new Event(14, 0, cur_trig->getID());
				cur_trig->addEvent(nEvent);
			}
			if(!prev_trig->hasActionType(27)) {
				Action *nAction = new Action(prev_trig->getID(), 27, 0, 0, secs, 0, 0, 0, 0);
				prev_trig->addAction(nAction);
			} else {
				prev_trig->getActionByType(27)->editP2(secs);
			}

			ui->TimerSetLabel->setText("Set");
		}
	}

}

// New action
void TriggerSection::on_NewAction_clicked()
{
	if(ui->TriggerList->currentRow() != -1) {
		Trigger *cur_trig = GetTriggerByName(ui->TriggerList->currentItem()->text().toStdString());

		Action *nAction = new Action(cur_trig->getID(), 0, 0, 0, 0, 0, 0, 0, 0);
		cur_trig->addAction(nAction);

		ui->ActionList->clear();
		int i = 0;
		for(actionIT = cur_trig->actions.begin(); actionIT != cur_trig->actions.end(); ++actionIT) {
			++i;
			stringstream iSS;
			iSS << i;
			QString text = "Action ";
			text += iSS.str().c_str();

			ui->ActionList->addItem(text);
		}
	}
}

// Delete action
void TriggerSection::on_DeleteAction_clicked()
{
	if(ui->ActionList->currentRow() != -1) {
		Trigger *cur_trig = GetTriggerByName(ui->TriggerList->currentItem()->text().toStdString());

		for(int i = ui->ActionList->selectedItems().size()-1; i != -1; --i) {
			cur_trig->eraseAction(ui->ActionList->row(ui->ActionList->selectedItems().at(i)));
		}

		clearActionList();
		int i = 0;
		for(actionIT = cur_trig->actions.begin(); actionIT != cur_trig->actions.end(); ++actionIT) {
			++i;
			stringstream iSS;
			iSS << i;
			QString text = "Action ";
			text += iSS.str().c_str();

			ui->ActionList->addItem(text);
		}
	}
}

// Clone action
void TriggerSection::on_CloneAction_clicked()
{
	if(ui->ActionList->currentRow() != -1) {
		int i = 1;
		Trigger *cur_trig = GetTriggerByName(ui->TriggerList->currentItem()->text().toStdString());
		for(actionIT = cur_trig->actions.begin(); actionIT != cur_trig->actions.end(); ++actionIT) {
			++i;
		}

		for(int a = 0; a != ui->ActionList->selectedItems().size(); ++a) {
			Action *nAct = new Action(cur_trig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().at(a))), cur_trig->getID());
			cur_trig->addAction(nAct);

			stringstream iSS;
			iSS << i;
			QString text = "Action ";
			text += iSS.str().c_str();

			ui->ActionList->addItem(text);

			++i;
		}
	}
}

void TriggerSection::on_ActionList_itemClicked()
{
	ui->TeamtypeBox->clear();
	ui->TeamAOBox->clear();
	QStringList teamList;
	for(teamIT = teams.begin(); teamIT != teams.end(); ++teamIT) {
		ui->TeamtypeBox->addItem(teamIT->second->getName().c_str());
		ui->TeamAOBox->addItem(teamIT->second->getName().c_str());
		teamList << teamIT->second->getName().c_str();
	}
	if(!teamList.empty()) {
		ui->TeamtypeBox->view()->setMinimumWidth(GetStringListMaxWidth(teamList, ui->TeamtypeBox->font())+50);
		ui->TeamAOBox->view()->setMinimumWidth(GetStringListMaxWidth(teamList, ui->TeamAOBox->font())+50);
	}
	if(ui->ActionList->currentRow() != -1) {
		Trigger *cTrig = GetTriggerByName(ui->TriggerList->currentItem()->text().toStdString());
		Action *cAct = cTrig->getAction(ui->ActionList->currentRow());
		if(cAct->getType() == 80) {
			ui->isReinforcementCheck->setChecked(true);
			ui->TeamtypeBox->setCurrentIndex(ui->TeamtypeBox->findText(GetTeamNameByID(cAct->getP2()).c_str()));
		} else {
			ui->isReinforcementCheck->setChecked(false);
		}
		stringstream wSS;
		wSS << cAct->getWaypoint();
		ui->WaypointBox->setEditText(wSS.str().c_str());
	} else {
		ui->isReinforcementCheck->setChecked(false);
	}
}

// Is "reinforcement at waypoint" - action
void TriggerSection::on_isReinforcementCheck_clicked()
{
	if(ui->ActionList->currentRow() != -1) {
		Trigger *cTrig = GetTriggerByName(ui->TriggerList->currentItem()->text().toStdString());
		if(ui->isReinforcementCheck->isChecked()) {
			for(int a = 0; a != ui->ActionList->selectedItems().size(); ++a) {
				cTrig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().at(a)))->editType(80);
			}
		} else {
			for(int a = 0; a != ui->ActionList->selectedItems().size(); ++a) {
				cTrig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().at(a)))->editType(0);
			}
		}
	}
}

// Action's waypoint
void TriggerSection::on_WaypointBox_currentIndexChanged()
{
	if(ui->ActionList->currentItem() != NULL) {
		Trigger *cTrig = GetTriggerByName(ui->TriggerList->currentItem()->text().toStdString());
		for(int a = 0; a != ui->ActionList->selectedItems().size(); ++a) {
			cTrig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().at(a)))->editWPoint(atoi(ui->WaypointBox->currentText().toStdString().c_str()));
		}
	}
}

void TriggerSection::clearTriggerList() {
	delete ui->TriggerList->item(ui->TriggerList->currentRow());
	ui->TriggerList->clear();
}

void TriggerSection::clearActionList() {
	for(int i = 0; i < ui->ActionList->selectedItems().size(); ++i) {
		delete ui->ActionList->selectedItems().at(i);
	}
	ui->ActionList->clear();
}

// Make waypoints grow in ascending order in selected actions
void TriggerSection::on_WPointAOButton_clicked()
{
	if(ui->TriggerList->currentRow() != -1 && !waypoints.empty()) {

		Trigger *cur_trig = GetTriggerByName(ui->TriggerList->currentItem()->text().toStdString());

		unsigned int j = 0;
		unsigned int i = 0;

		for(waypointIT = waypoints.begin(); waypointIT != waypoints.end(); ++waypointIT) {
			if((*waypointIT) == sWPoint) {
				i = j;
				break;
			}
			++j;
			if(j == waypoints.size()) {
				j = 0;
				break;
			}
		}

		for(int a = 0; a != ui->ActionList->selectedItems().size(); ++a) {
			Action *cur_act = cur_trig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().at(a)));
			if(i == waypoints.size()) { i = j; }
			cur_act->editWPoint((*(waypoints.begin()+i)));
			++i;
		}

	}
}


// Starting waypoint control for "Make waypoints grow in ascending order in all actions"
void TriggerSection::on_SWaypointBox_currentIndexChanged()
{
	sWPoint = atoi(ui->SWaypointBox->currentText().toStdString().c_str());
	on_WPointAOButton_clicked();
}

// TeamType for actions
void TriggerSection::on_TeamtypeBox_activated()
{
	if(ui->ActionList->currentRow() != -1) {
		Trigger *cur_trig = GetTriggerByName(ui->TriggerList->currentItem()->text().toStdString());
		for(int a = 0; a != ui->ActionList->selectedItems().size(); ++a) {
			cur_trig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().at(a)))->editP1(1);
			cur_trig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().at(a)))->editP2(GetTeamByName(ui->TeamtypeBox->currentText().toStdString())->getID().c_str());
		}
	}
}

// Make teams grow as actions in selected actions
void TriggerSection::on_TeamAOButton_clicked()
{
	if(ui->ActionList->currentRow() != -1) {
		Trigger *cur_trig = GetTriggerByName(ui->TriggerList->currentItem()->text().toStdString());
		Team *sTeam = GetTeamByName(ui->TeamAOBox->currentText().toStdString());
		if(sTeam != NULL) {
			int i = 0;
			for(std::map <std::string, Team*>::iterator teamIT = teams.find(sTeam->getID()); teamIT != teams.end(); ++teamIT) {
				cur_trig->getAction(i)->editType(80);
				cur_trig->getAction(i)->editP1(1);
				cur_trig->getAction(i)->editP2(teamIT->second->getID());
				++i;
				if(i == ui->ActionList->selectedItems().size()) {
					break;
				}
			}
		}
	}
}

void TriggerSection::UpdateUi() {
	ui->TriggerList->clear();
	for(map <string, Trigger*>::iterator triggerIT = triggers.begin(); triggerIT != triggers.end(); ++triggerIT) {
		ui->TriggerList->addItem(triggerIT->second->getName());
	}
}
