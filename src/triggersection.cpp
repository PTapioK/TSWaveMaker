#include "triggersection.h"
#include "ui_triggersection.h"

TriggerSection::TriggerSection(QWidget *parent) :
	QDockWidget(parent),
	ui(new Ui::TriggerSection)
{
	ui->setupUi(this);
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
		Trigger *cur_trig = triggers[trig_name];
		ui->NEdit->setText(ui->TriggerList->currentItem()->text());
		ui->isDisabledCheck->setChecked(cur_trig->isDis());

		if(!isFirstWave(cur_trig->getID())) {
			triggerIT = triggers.find(trig_name);
			--triggerIT;
			Trigger *prev_trig = (*triggerIT).second;
			if(prev_trig->hasActionType(27)) {
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
		triggers[name] = new Trigger(name);
		tags[name + " 1"] = new Tag(name + " 1", triggers[name]->getID());
	}
}

// Edit trigger name
void TriggerSection::on_EditTriggerName_clicked()
{
	if(ui->TriggerList->findItems(ui->NEdit->text(), Qt::MatchExactly).count() == 0) {
		string cur_name = ui->TriggerList->currentItem()->text().toStdString();
		triggers[cur_name]->setName(ui->NEdit->text().toStdString());

		map <string, Trigger*> tempMap;
		for(triggerIT = triggers.begin(); triggerIT != triggers.end(); ++triggerIT) {
			if((*triggerIT).first == cur_name) {
				tempMap[ui->NEdit->text().toStdString()] = (*triggerIT).second;
			} else {
				tempMap[(*triggerIT).first] = (*triggerIT).second;
			}
		}

		triggers.swap(tempMap);

		ui->TriggerList->currentItem()->setText(ui->NEdit->text());
	}
}

// Is disabled
void TriggerSection::on_isDisabledCheck_clicked()
{
	if(ui->TriggerList->currentRow() != -1) {
		triggers[ui->TriggerList->currentItem()->text().toStdString()]->setDis(ui->isDisabledCheck->isChecked());
	}
}

// Delete trigger
void TriggerSection::on_DeleteTrigger_clicked()
{
	if(ui->TriggerList->currentRow() != -1) {
		string name = ui->TriggerList->currentItem()->text().toStdString();
		delete triggers[name];
		triggers.erase(name);
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
		triggers[newName] = new Trigger(triggers[ui->TriggerList->currentItem()->text().toStdString()]);
		triggers[newName]->setName(newName);
		ui->TriggerList->addItem(newName.c_str());
		Tag *cTag = FindTag(triggers[ui->TriggerList->currentItem()->text().toStdString()]->getID());
		tags[newName + " 1"] = new Tag(cTag, triggers[newName]->getID());
		tags[newName + " 1"]->setName(newName + " 1");
	}

}

void TriggerSection::on_WaveTimer_editingFinished()
{
	if(ui->TriggerList->currentRow() != -1) {
		string trig_name = ui->TriggerList->currentItem()->text().toStdString();
		int32_t secs = 0;
		secs = abs(ui->WaveTimer->time().secsTo(QTime(0, 0)));
		if(isFirstWave(triggers[trig_name]->getID())) {

			if(triggers["TimerFor1stWave"] == NULL) {

				triggers["TimerFor1stWave"] = new Trigger("01000000", "Neutral", "<none>", "TimerFor1stWave", false, true, true, true);
				tags["TimerFor1stWave 1"] = new Tag("TimerFor1stWave 1", triggers["TimerFor1stWave"]->getID());
				tags["TimerFor1stWave 1"]->setID("01000001");
				Event *nEvent = new Event(8, 0, triggers["TimerFor1stWave"]->getID());
				triggers["TimerFor1stWave"]->addEvent(nEvent);
				Action *nAction = new Action(triggers["TimerFor1stWave"]->getID(), 27, 0, 0, secs, 0, 0, 0, 0);
				triggers["TimerFor1stWave"]->addAction(nAction);

				ui->TriggerList->addItem("TimerFor1stWave");
				ui->TimerSetLabel->setText("Set");

			}
		} else {

			Trigger *cur_trig = triggers[trig_name];

			triggerIT = triggers.find(trig_name);
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
		Trigger *cur_trig = triggers[ui->TriggerList->currentItem()->text().toStdString()];

		int32_t lastWPoint = 0;
		if(!cur_trig->actions.empty())
			lastWPoint = (*(cur_trig->actions.end()-1))->getWaypoint();
		int32_t nextWPoint = 0;

		if(ui->WPointAOBox->isChecked()) {
			if(lastWPoint != waypoints.size()) {
				for(waypointIT = waypoints.begin(); waypointIT != waypoints.end(); ++waypointIT) {
					if(lastWPoint == *waypointIT) {
						++waypointIT;
						nextWPoint = *waypointIT;
						break;
					}
				}
			} else {
				nextWPoint = (*(waypoints.begin()));
			}
		}

		Action *nAction = new Action(cur_trig->getID(), 0, nextWPoint, 0, 0, 0, 0, 0, 0);
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
		Trigger *cur_trig = triggers[ui->TriggerList->currentItem()->text().toStdString()];

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
		Trigger *cur_trig = triggers[ui->TriggerList->currentItem()->text().toStdString()];
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
	for(teamIT = teams.begin(); teamIT != teams.end(); ++teamIT) {
		ui->TeamtypeBox->addItem((*teamIT).first.c_str());
	}
	if(ui->ActionList->currentRow() != -1) {
		Trigger *cTrig = triggers[ui->TriggerList->currentItem()->text().toStdString()];
		Action *cAct = cTrig->getAction(ui->ActionList->currentRow());
		if(cAct->getType() == 80) {
			ui->isReinforcementCheck->setChecked(true);
			ui->TeamtypeBox->setCurrentIndex(ui->TeamtypeBox->findText(cAct->getP2().c_str()));
		} else {
			ui->isReinforcementCheck->setChecked(false);
		}
		stringstream wSS;
		wSS << cAct->getWaypoint();
		ui->WaypointBox->setEditText(wSS.str().c_str());
	} else {
		ui->isReinforcementCheck->setChecked(false);
		ui->WPointAOBox->setChecked(false);
	}
}

// Is "reinforcement at waypoint" - action
void TriggerSection::on_isReinforcementCheck_stateChanged()
{
	if(ui->ActionList->currentRow() != -1) {
		Trigger *cTrig = triggers[ui->TriggerList->currentItem()->text().toStdString()];
		if(ui->isReinforcementCheck->isChecked()) {
			for(int a = 0; a != ui->ActionList->selectedItems().size(); ++a) {
				cTrig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().at(a)))->editType(80);
			}
			ui->TeamtypeBox->setEnabled(true);
		} else {
			for(int a = 0; a != ui->ActionList->selectedItems().size(); ++a) {
				cTrig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().at(a)))->editType(0);
			}
		}
	}
}

// Action waypoint
void TriggerSection::on_WaypointBox_currentIndexChanged()
{
	if(ui->ActionList->currentItem() != NULL) {
		Trigger *cTrig = triggers[ui->TriggerList->currentItem()->text().toStdString()];
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

// Make waypoints grow in ascending order to selected actions
void TriggerSection::on_WPointAOBox_clicked()
{
	if(ui->TriggerList->currentRow() != -1) {
		if(ui->WPointAOBox->isChecked()) {

			Trigger *cur_trig = triggers[ui->TriggerList->currentItem()->text().toStdString()];

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

			ui->SWaypointBox->setEnabled(true);

		} else {
			ui->SWaypointBox->setEnabled(false);
		}
	}
}

// Starting waypoint to "Make waypoints grow in ascending order in all actions"
void TriggerSection::on_SWaypointBox_currentIndexChanged()
{
	sWPoint = atoi(ui->SWaypointBox->currentText().toStdString().c_str());
	on_WPointAOBox_clicked();
}

// TeamType for actions
void TriggerSection::on_TeamtypeBox_activated()
{
	if(ui->ActionList->currentRow() != -1) {
		Trigger *cur_trig = triggers[ui->TriggerList->currentItem()->text().toStdString()];
		for(int a = 0; a != ui->ActionList->selectedItems().size(); ++a) {
			cur_trig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().at(a)))->editP1(1);
			cur_trig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().at(a)))->editP2(ui->TeamtypeBox->currentText().toStdString());
		}
	}
}

void TriggerSection::UpdateUi() {
	ui->TriggerList->clear();
	for(triggerIT = triggers.begin(); triggerIT != triggers.end(); ++triggerIT) {
		ui->TriggerList->addItem(triggerIT->second->getName());
	}
}
