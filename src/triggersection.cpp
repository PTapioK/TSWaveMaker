#include "triggersection.h"
#include "ui_triggersection.h"

TriggerSection::TriggerSection(QWidget *parent) :
	QDockWidget(parent),
	ui(new Ui::TriggerSection)
{
	ui->setupUi(this);

	sWPoint = 8; // Starting waypoint for "Make waypoints grow in ascending order in all actions"

	ui->isOtherAction->setVisible(false);
}

TriggerSection::~TriggerSection()
{
	delete ui;
}


void TriggerSection::on_TriggerList_itemSelectionChanged()
{
	ui->WaveTimer->setTime(QTime(0, 0, 0));
	ui->WaveTimer->setTime(QTime(-1, -1));

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

		if(cur_trig->hasActionType(27)) {
			int32_t secs = atoi(cur_trig->getActionByType(27)->p2.c_str());
			QTime time(0, 0, 0);
			time = time.addSecs(secs);
			ui->WaveTimer->setTime(time);
		}

		int i = 0;
		for(actionIT IT = cur_trig->actions.begin(); IT != cur_trig->actions.end(); ++IT) {
			++i;
			stringstream iSS;
			iSS << i;
			QString text = "Action ";
			text += iSS.str().c_str();

			ui->ActionList->addItem(text);
		}
		ui->isTimedWave->setChecked(cur_trig->hasEventType(14));
		ui->anyEventWave->setChecked(cur_trig->hasEventType(8));

	} else {
		ui->NEdit->setText("");
	}

	ui->WaypointBox->clear();
	ui->SWaypointBox->clear();
	for(waypointIT IT = waypoints.begin(); IT != waypoints.end(); ++IT) {
		stringstream wSS;
		wSS << (*IT);
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
}

// Edit trigger name
void TriggerSection::on_EditTriggerName_clicked()
{
	if(ui->TriggerList->currentRow() != -1) {
		if(ui->TriggerList->findItems(ui->NEdit->text(), Qt::MatchExactly).count() == 0) {
			string cur_name = ui->TriggerList->currentItem()->text().toStdString();
			string cur_ID = GetTriggerIDByName(cur_name);

			triggers[cur_ID]->setName(ui->NEdit->text().toStdString());

			ui->TriggerList->currentItem()->setText(ui->NEdit->text());
		}
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
		string tagName = FindTag(ID)->getName();
		delete FindTag(ID);
		tags.erase(tagName);

		delete ui->TriggerList->item(ui->TriggerList->currentRow());
	}

}

// Clone trigger
void TriggerSection::on_CloneTrigger_clicked()
{
	if(ui->TriggerList->currentRow() != -1) {
		string newName = GetNameWithNextMark(ui->TriggerList->currentItem()->text().toStdString());

		int i = 0;
		while(ui->TriggerList->findItems(newName.c_str(), Qt::MatchExactly).count() != 0) {
			++i;
			newName = GetNameWithNextMark(ui->TriggerList->currentItem()->text().toStdString(), i);
		}

		string newID = fffID();
		triggers[newID] = new Trigger(newID, GetTriggerByName(ui->TriggerList->currentItem()->text().toStdString()));
		triggers[newID]->setName(newName);
		ui->TriggerList->addItem(newName.c_str());
		Tag *cTag = FindTag(GetTriggerByName(ui->TriggerList->currentItem()->text().toStdString())->getID());
		tags[newName + " 1"] = new Tag(cTag, triggers[newID]->getID());
		tags[newName + " 1"]->setName(newName + " 1");
	}
}

void TriggerSection::on_WaveTimer_editingFinished()
{
	if(ui->TriggerList->currentRow() != -1) {
		string trig_name = ui->TriggerList->currentItem()->text().toStdString();
		int32_t secs = 0;
		secs = abs(ui->WaveTimer->time().secsTo(QTime(0, 0, 0)));

		Trigger *cur_trig = GetTriggerByName(trig_name);

		if(!cur_trig->hasActionType(27)) {
			Action *nAction = new Action(cur_trig->getID(), 27, 0, 0, secs, 0, 0, 0, 0);
			cur_trig->addAction(nAction);
		} else {
			cur_trig->getActionByType(27)->editP2(secs);
		}

		ui->ActionList->clear();
		int i = 0;
		for(actionIT IT = cur_trig->actions.begin(); IT != cur_trig->actions.end(); ++IT) {
			++i;
			QString text = "Action ";
			text += IntToStr(i).c_str();

			ui->ActionList->addItem(text);
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
		for(actionIT IT = cur_trig->actions.begin(); IT != cur_trig->actions.end(); ++IT) {
			++i;
			QString text = "Action ";
			text += IntToStr(i).c_str();

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
		for(actionIT IT = cur_trig->actions.begin(); IT != cur_trig->actions.end(); ++IT) {
			++i;
			QString text = "Action ";
			text += IntToStr(i).c_str();

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
		for(actionIT IT = cur_trig->actions.begin(); IT != cur_trig->actions.end(); ++IT) {
			++i;
		}

		for(int a = 0; a != ui->ActionList->selectedItems().size(); ++a) {
			Action *nAct = new Action(cur_trig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().at(a))), cur_trig->getID());
			cur_trig->addAction(nAct);

			QString text = "Action ";
			text += IntToStr(i).c_str();

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
	for(teamIT IT = teams.begin(); IT != teams.end(); ++IT) {
		ui->TeamtypeBox->addItem(IT->second->getName().c_str());
		ui->TeamAOBox->addItem(IT->second->getName().c_str());
		teamList << IT->second->getName().c_str();
	}
	if(!teamList.empty()) {
		ui->TeamtypeBox->view()->setMinimumWidth(GetStringListMaxWidth(teamList, ui->TeamtypeBox->font())+50);
		ui->TeamAOBox->view()->setMinimumWidth(GetStringListMaxWidth(teamList, ui->TeamAOBox->font())+50);
	}
	ui->TeamAOBox->setEnabled(false);
	ui->TeamAOButton->setEnabled(false);
	ui->TeamtypeBox->setEnabled(false);
	ui->isOtherAction->setEnabled(true);
	if(ui->ActionList->selectedItems().size() != 0) {
		Trigger *cTrig = GetTriggerByName(ui->TriggerList->currentItem()->text().toStdString());
		Action *cAct = cTrig->getAction(ui->ActionList->currentRow());
		switch(cAct->getType()) {
			case 1:
				if(atoi(cAct->getP2().c_str()) == 2)
					ui->isLose->toggle();
				break;
			case 2:
				if(atoi(cAct->getP2().c_str()) == 2)
					ui->isWin->toggle();
				break;
			case 4:
				ui->isCreateTeam->toggle();
				ui->TeamtypeBox->setCurrentIndex(ui->TeamtypeBox->findText(GetTeamNameByID(cAct->getP2()).c_str()));
				ui->TeamAOBox->setEnabled(true);
				ui->TeamAOButton->setEnabled(true);
				ui->TeamtypeBox->setEnabled(true);
				break;
			case 80:
				ui->isReinforcement->toggle();
				ui->TeamtypeBox->setCurrentIndex(ui->TeamtypeBox->findText(GetTeamNameByID(cAct->getP2()).c_str()));
				ui->TeamAOBox->setEnabled(true);
				ui->TeamAOButton->setEnabled(true);
				ui->TeamtypeBox->setEnabled(true);
				break;
			case 95:
				ui->isNukeStrike->toggle();
				break;
			default:
				ui->isOtherAction->toggle();
		}

		stringstream wSS;
		wSS << cAct->getWaypoint();
		ui->WaypointBox->setEditText(wSS.str().c_str());
	}
}

// Is "create team" - action
void TriggerSection::on_isCreateTeam_clicked()
{
	if(ui->ActionList->currentRow() != -1) {
		Trigger *cTrig = GetTriggerByName(ui->TriggerList->currentItem()->text().toStdString());
		if(ui->isCreateTeam->isChecked()) {
			for(int a = 0; a != ui->ActionList->selectedItems().size(); ++a) {
				cTrig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().at(a)))->editType(4);
			}
		}
	}
}

// Is "reinforcement at waypoint" - action
void TriggerSection::on_isReinforcement_clicked()
{
	if(ui->ActionList->currentRow() != -1) {
		Trigger *cTrig = GetTriggerByName(ui->TriggerList->currentItem()->text().toStdString());
		if(ui->isReinforcement->isChecked()) {
			for(int a = 0; a != ui->ActionList->selectedItems().size(); ++a) {
				cTrig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().at(a)))->editType(80);
			}
		}
	}
}

// Is "nuke strike at waypoint" - action
void TriggerSection::on_isNukeStrike_clicked()
{
	if(ui->ActionList->currentRow() != -1) {
		Trigger *cTrig = GetTriggerByName(ui->TriggerList->currentItem()->text().toStdString());
		if(ui->isNukeStrike->isChecked()) {
			for(int a = 0; a != ui->ActionList->selectedItems().size(); ++a) {
				cTrig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().at(a)))->editType(95);
			}
		}
	}
}

// Is "lose" - action
void TriggerSection::on_isLose_clicked()
{
	if(ui->ActionList->currentRow() != -1) {
		Trigger *cTrig = GetTriggerByName(ui->TriggerList->currentItem()->text().toStdString());
		if(ui->isLose->isChecked()) {
			for(int a = 0; a != ui->ActionList->selectedItems().size(); ++a) {
				cTrig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().at(a)))->editType(1);
				cTrig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().at(a)))->editP2(2);
			}
		}
	}
}

// Is "win" - action
void TriggerSection::on_isWin_clicked()
{
	if(ui->ActionList->currentRow() != -1) {
		Trigger *cTrig = GetTriggerByName(ui->TriggerList->currentItem()->text().toStdString());
		if(ui->isWin->isChecked()) {
			for(int a = 0; a != ui->ActionList->selectedItems().size(); ++a) {
				cTrig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().at(a)))->editType(2);
				cTrig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().at(a)))->editP2(2);
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

		for(waypointIT IT = waypoints.begin(); IT != waypoints.end(); ++IT) {
			if((*IT) == sWPoint) {
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
			for(teamIT IT = teams.find(sTeam->getID()); IT != teams.end(); ++IT) {
				cur_trig->getAction(i)->editType(80);
				cur_trig->getAction(i)->editP1(1);
				cur_trig->getAction(i)->editP2(IT->second->getID());
				++i;
				if(i == ui->ActionList->selectedItems().size()) {
					break;
				}
			}
		}
	}
}

// Trigger has "Mission timer expired" -event
void TriggerSection::on_isTimedWave_clicked()
{
	if(ui->TriggerList->currentRow() != -1) {
		Trigger *cur_trig = GetTriggerByName(ui->TriggerList->currentItem()->text().toStdString());
		if(ui->isTimedWave->isChecked()) {
			if(!cur_trig->hasEventType(14)) {
				Event *nEvent = new Event(14, 0, cur_trig->getID());
				cur_trig->addEvent(nEvent);
			}
		} else {
			if(cur_trig->hasEventType(14)) {
				cur_trig->eraseEventByType(14);
			}
		}
	}
}

// Trigger has "Any event" -event
void TriggerSection::on_anyEventWave_clicked()
{
	if(ui->TriggerList->currentRow() != -1) {
		Trigger *cur_trig = GetTriggerByName(ui->TriggerList->currentItem()->text().toStdString());
		if(ui->anyEventWave->isChecked()) {
			if(!cur_trig->hasEventType(8)) {
				Event *nEvent = new Event(8, 0, cur_trig->getID());
				cur_trig->addEvent(nEvent);
			}
		} else {
			if(cur_trig->hasEventType(8)) {
				cur_trig->eraseEventByType(8);
			}
		}
	}
}

void TriggerSection::UpdateUi() {
	ui->TriggerList->setCurrentRow(-1);
	ui->ActionList->setCurrentRow(-1);
	ui->TriggerList->clear();
	for(triggerIT IT = triggers.begin(); IT != triggers.end(); ++IT) {
		ui->TriggerList->addItem(IT->second->getName());
	}
}
