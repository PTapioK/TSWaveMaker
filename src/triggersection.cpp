#include "triggersection.h"
#include "ui_triggersection.h"
#include "main.h"

using namespace Settings;

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
	ui->WaveTimer->setTime(QTime(0, 0, 0));
	ui->EventList->clear();
	ui->ActionList->clear();
	ui->TagOr->toggle();

	if(ui->TriggerList->selectedItems().size() != 0) {
		QString trigName = ui->TriggerList->selectedItems().last()->text();
		Trigger *curTrig = getTriggerByName(trigName);
		Tag *curTrigTag = getTagByTriggerID(curTrig->getID());

		ui->NameEdit->setText(trigName);
		ui->isDisabledCheck->setChecked(curTrig->isDisabled());

		switch (curTrigTag->getMode()) {
			case 0:
			{
				ui->TagOr->toggle();
				break;
			}
			case 1:
			{
				ui->TagAnd->toggle();
				break;
			}
			case 2:
			{
				ui->TagRepeatingOr->toggle();
				break;
			}
			default:
				ui->TagOr->toggle();
		}

		if(curTrig->hasActionType(27)) {
			int32_t secs = curTrig->getActionByType(27)->getParameter(1).toInt();
			QTime time(0, 0, 0);
			time = time.addSecs(secs);
			ui->WaveTimer->setTime(time);
		}

		int i = 0;
		for(auto IT = curTrig->events.begin(); IT != curTrig->events.end(); ++IT) {
			++i;
			ui->EventList->addItem(QString::number(i));
		}

		i = 0;
		for(auto IT = curTrig->actions.begin(); IT != curTrig->actions.end(); ++IT) {
			++i;
			ui->ActionList->addItem(QString::number(i));
		}
	} else {
		ui->NameEdit->setText("");
	}
}

// New trigger
void TriggerSection::on_NewTrigger_clicked()
{
	if(ui->TriggerList->findItems(ui->NameEdit->text(), Qt::MatchExactly).count() == 0) {
		QString name = ui->NameEdit->text();
		QString newID = findFirstFreeID();
		triggers[newID] = new Trigger(newID, name);
		QString newTagID = findFirstFreeID();
		tags[newTagID] = new Tag(name + " 1", newID, newTagID);
		updateUi();
		ui->TriggerList->setCurrentItem(ui->TriggerList->findItems(name, Qt::MatchExactly).last());
	}
}

// Edit trigger's name
void TriggerSection::on_EditTriggerName_clicked()
{
	if(ui->TriggerList->selectedItems().size() != 0) {
		QString curName = ui->TriggerList->selectedItems().last()->text();
		QString newName = ui->NameEdit->text();
		if(ui->TriggerList->findItems(newName, Qt::MatchExactly).count() == 0) {
			QString curID = getTriggerIDByName(curName);

			triggers[curID]->setName(newName);
			getTagByTriggerID(curID)->setName(newName + " 1");

			ui->TriggerList->selectedItems().last()->setText(newName);
		}
	}
}

// Disable trigger(s)
void TriggerSection::on_isDisabledCheck_clicked()
{
	if(ui->TriggerList->selectedItems().size() != 0) {
		for (int a = 0; a != ui->TriggerList->selectedItems().size(); ++a) {
			QString name = ui->TriggerList->selectedItems().at(a)->text();
			getTriggerByName(name)->setDis(ui->isDisabledCheck->isChecked());
		}
	}
}

// Delete trigger(s)
void TriggerSection::on_DeleteTrigger_clicked()
{
	if(ui->TriggerList->selectedItems().size() != 0) {
		for (int a = 0; a != ui->TriggerList->selectedItems().size(); ++a) {
			QString name = ui->TriggerList->selectedItems().at(a)->text();
			QString ID = getTriggerIDByName(name);
			delete getTriggerByName(name);
			triggers.erase(ID);
			QString tagID = getTagByTriggerID(ID)->getID();
			delete getTagByTriggerID(ID);
			tags.erase(tagID);
		}
		updateUi();
	}
}

// Clone trigger(s)
void TriggerSection::on_CloneTrigger_clicked()
{
	if(ui->TriggerList->selectedItems().size() != 0) {
		for (int a = 0; a != ui->TriggerList->selectedItems().size(); ++a) {
			QString curName = ui->TriggerList->selectedItems().at(a)->text();
			Trigger *curTrig = getTriggerByName(curName);

			QString newName = getNameWithNextMark(ui->TriggerList->selectedItems().at(a)->text(), a, 0);
			int i = 0;
			while(ui->TriggerList->findItems(newName, Qt::MatchExactly).count() != 0) {
				++i;
				newName = getNameWithNextMark(curName, i);
			}

			QString newID = findFirstFreeID();
			triggers[newID] = new Trigger(newID, curTrig);
			triggers[newID]->setName(newName);
			ui->TriggerList->addItem(newName);

			Tag *cTag = getTagByTriggerID(curTrig->getID());
			QString tagNewName = newName + " 1";
			i = 0;
			while(tags.find(tagNewName) != tags.end()) {
				++i;
				tagNewName = getNameWithNextMark(newName + " 1", i);
			}

			QString newTagID = findFirstFreeID();
			tags[newTagID] = new Tag(cTag, newID, newTagID, tagNewName);
		}
	}
}

void TriggerSection::on_WaveTimer_editingFinished()
{
	if(ui->TriggerList->selectedItems().size() != 0) {
		for (int a = 0; a != ui->TriggerList->selectedItems().size(); ++a) {
			QString curName = ui->TriggerList->selectedItems().at(a)->text();
			Trigger *curTrig = getTriggerByName(curName);

			int32_t secs = 0;
			secs = abs(ui->WaveTimer->time().secsTo(QTime(0, 0, 0)));

			if(!curTrig->hasActionType(27)) {
				Action *nAction = new Action(curTrig->getID(), 27, 0, "0", QString::number(secs), "0", "0", "0", "0");
				curTrig->addAction(nAction);
				ui->ActionList->addItem(QString::number(curTrig->actions.size()));
			} else {
				curTrig->getActionByType(27)->setParameter(1, secs);
			}
		}
	}
}

// New event
void TriggerSection::on_NewEvent_clicked()
{
	if(ui->TriggerList->selectedItems().size() != 0) {
		for (int a = 0; a != ui->TriggerList->selectedItems().size(); ++a) {
			Trigger *curTrig = getTriggerByName(ui->TriggerList->selectedItems().at(a)->text());

			Event *nEvent = new Event(curTrig->getID());
			curTrig->addEvent(nEvent);
		}
		Trigger *curTrig = getTriggerByName(ui->TriggerList->selectedItems().last()->text());
		ui->EventList->addItem(QString::number(curTrig->events.size()));
	}
}

// Delete event
void TriggerSection::on_DeleteEvent_clicked()
{
	if(ui->TriggerList->selectedItems().size() != 0) {
		for (int a = 0; a != ui->TriggerList->selectedItems().size(); ++a) {
			Trigger *curTrig = getTriggerByName(ui->TriggerList->selectedItems().at(a)->text());

			for(int32_t i = ui->EventList->selectedItems().size()-1; i != -1; --i) {
				if(int32_t(curTrig->events.size()) > i) {
					curTrig->eraseEvent(ui->EventList->row(ui->EventList->selectedItems().at(i)));
				}
			}
		}
		cleanEventList();
	}
}

// Clone event
void TriggerSection::on_CloneEvent_clicked()
{
	if(ui->TriggerList->selectedItems().size() != 0) {
		for (int32_t a = 0; a != ui->TriggerList->selectedItems().size(); ++a) {
			Trigger *curTrig = getTriggerByName(ui->TriggerList->selectedItems().at(a)->text());

			size_t eventsCount = curTrig->events.size();
			size_t i = eventsCount;
			for(int32_t b = 0; b != ui->EventList->selectedItems().size(); ++b) {
				int32_t eventID = ui->EventList->row(ui->EventList->selectedItems().at(b));
				if (eventID < int32_t(eventsCount)) {
					Event *nEve = new Event(curTrig->getEvent(eventID), curTrig->getID());
					curTrig->addEvent(nEve);

					if (ui->TriggerList->selectedItems().at(a)->text() == ui->TriggerList->selectedItems().last()->text()) {
						++i;
						ui->EventList->addItem(QString::number(i));
					}
				}
			}
		}
	}
}

void TriggerSection::on_EventList_itemSelectionChanged()
{
	ui->EventTypeBox->setCurrentIndex(0);
	ui->EventParamBox->clear();
	if (ui->EventList->selectedItems().size() != 0 && ui->TriggerList->selectedItems().size() != 0) {
		Trigger *curTrig = getTriggerByName(ui->TriggerList->selectedItems().last()->text());
		int16_t index = curTrig->getEvent(ui->EventList->row(ui->EventList->selectedItems().last()))->getType();
		if (index < ui->EventTypeBox->count()) {
			ui->EventTypeBox->setCurrentIndex(index);
			updateEventParamBox();
		}
		ui->EventTypeBox->view()->setMinimumWidth(getComboBoxMaxWidth(ui->EventTypeBox) + 50);
	}
}

void TriggerSection::on_EventTypeBox_activated()
{
	if(ui->TriggerList->selectedItems().size() != 0 && ui->EventList->selectedItems().size() != 0) {
		for (int a = 0; a != ui->TriggerList->selectedItems().size(); ++a) {
			Trigger *curTrig = getTriggerByName(ui->TriggerList->selectedItems().at(a)->text());
			for(int32_t b = 0; b != ui->EventList->selectedItems().size(); ++b) {
				size_t index = ui->EventList->row(ui->EventList->selectedItems().at(b));
				if(index < curTrig->events.size()) {
					curTrig->getEvent(index)->setType(ui->EventTypeBox->currentIndex());
				}
			}
		}
		updateEventParamBox();
	}
}

void TriggerSection::on_EventParamBox_activated()
{
	if(ui->TriggerList->selectedItems().size() != 0 && ui->EventList->selectedItems().size() != 0) {
		Trigger *curTrig = getTriggerByName(ui->TriggerList->selectedItems().last()->text());
		Event *curEvent = curTrig->getEvent(ui->EventList->row(ui->EventList->selectedItems().last()));
		int32_t curEventType = curEvent->getType();
		for (int32_t a = 0; a != ui->TriggerList->selectedItems().size(); ++a) {
			Trigger *trig = getTriggerByName(ui->TriggerList->selectedItems().at(a)->text());
			for(int32_t b = 0; b != ui->EventList->selectedItems().size(); ++b) {
				if (b < int32_t(trig->events.size())) {
					Event *event = trig->getEvent(ui->EventList->row(ui->EventList->selectedItems().at(b)));
					int32_t eventType = event->getType();
					if (curEventType == eventType) {
						switch(getEventTargetType(eventType)) {
							case TargetType::NONE:
								event->setParameter("0");
								break;
							case TargetType::WAYPOINT:
								event->setParameter(QString::number(waypoints[ui->EventParamBox->currentIndex()]));
								break;
							case TargetType::HOUSE:
								for(auto IT = houses.begin(); IT != houses.end(); ++IT) {
									if((*IT).second == ui->EventParamBox->currentText()) {
										event->setParameter(QString::number((*IT).first));
										break;
									}
								}
								break;
							case TargetType::TEAM:
								event->setUnknown(1);
								event->setParameter(getTeamByName(ui->EventParamBox->currentText())->getID());
								break;
							case TargetType::TRIGGER:
								event->setParameter(getTriggerByName(ui->EventParamBox->currentText())->getID());
								break;
							case TargetType::EDITABLE:
								event->setParameter(ui->EventParamBox->currentText());
								break;
							case TargetType::TEXT:
								event->setParameter(QString::number(getTutorialKeyByText(ui->EventParamBox->currentText())));
								break;
							case TargetType::TAG:
								event->setParameter(getTagByName(ui->EventParamBox->currentText())->getID());
								break;
							case TargetType::BUILDING:
								for(auto IT = buildings.begin(); IT != buildings.end(); ++IT) {
									if((*IT).second.name == ui->EventParamBox->currentText()) {
										event->setParameter(QString::number((*IT).first));
										break;
									}
								}
								break;
							case TargetType::INFANTRY:
								event->setParameter(QString::number(getUnitKeyByName(ui->EventParamBox->currentText(), infantry)));
								break;
							case TargetType::VEHICLE:
								event->setParameter(QString::number(getUnitKeyByName(ui->EventParamBox->currentText(), vehicles)));
								break;
							case TargetType::AIRCRAFT:
								event->setParameter(QString::number(getUnitKeyByName(ui->EventParamBox->currentText(), aircraft)));
								break;
							default:
								event->setParameter(QString::number(ui->EventParamBox->currentIndex()));
						}
					}
				}
			}
		}
	}
}

void TriggerSection::cleanEventList() {
	for(int i = 0; i < ui->EventList->selectedItems().size(); ++i) {
		delete ui->EventList->selectedItems().at(i);
	}
	ui->EventList->clear();
	if(ui->TriggerList->selectedItems().size() != 0) {
		Trigger *curTrig = getTriggerByName(ui->TriggerList->selectedItems().last()->text());
		int i = 0;
		for(auto IT = curTrig->events.begin(); IT != curTrig->events.end(); ++IT) {
			++i;
			ui->EventList->addItem(QString::number(i));
		}
	}
}

void TriggerSection::updateEventTypeBox()
{
	QStringList values;
	uint32_t i = 0;
	values = triggerStrings.value("Events/" + QString::number(i)).toStringList();
	while (!values.isEmpty()) {
		ui->EventTypeBox->addItem(values[0]);
		++i;
		values = triggerStrings.value("Events/" + QString::number(i)).toStringList();
	}
}

void TriggerSection::updateEventParamBox()
{
	ui->EventParamBox->setEditable(false);
	ui->EventParamBox->clear();
	ui->EEParameterBox->clear();
	ui->SEParameterBox->clear();

	if(ui->EventList->selectedItems().size() != 0 && ui->TriggerList->selectedItems().size() != 0) {
		Trigger *curTrig = getTriggerByName(ui->TriggerList->selectedItems().last()->text());
		Event *curEvent = curTrig->getEvent(ui->EventList->row(ui->EventList->selectedItems().last()));
		int32_t type = curEvent->getType();
		QString param = curEvent->getParameter();

		TargetType tType = getEventTargetType(type);
		QStringList targetList = getTargetStrings(tType);
		ui->EventParamBox->addItems(targetList);
		ui->SEParameterBox->addItems(targetList);
		ui->EEParameterBox->addItems(targetList);
		ui->EventParamBox->view()->setMinimumWidth(getComboBoxMaxWidth(ui->EventParamBox) + 50);
		ui->SEParameterBox->view()->setMinimumWidth(getComboBoxMaxWidth(ui->SEParameterBox) + 50);
		ui->EEParameterBox->view()->setMinimumWidth(getComboBoxMaxWidth(ui->EEParameterBox) + 50);

		switch(getEventTargetType(type)) {
			case TargetType::NONE:
				break;
			case TargetType::WAYPOINT:
				ui->EventParamBox->setCurrentIndex(ui->EventParamBox->findText(param));
				break;
			case TargetType::HOUSE:
				ui->EventParamBox->setCurrentIndex(ui->EventParamBox->findText(houses[param.toShort()]));
				break;
			case TargetType::TEAM:
			{
				auto IT = teams.find(param);
				if (IT != teams.end()) {
					ui->EventParamBox->setCurrentIndex(ui->EventParamBox->findText(IT->second->getName()));
				}
				break;
			}
			case TargetType::EDITABLE:
				ui->EventParamBox->setEditable(true);
				ui->EventParamBox->setCurrentText(param);
				break;
			case TargetType::BUILDING:
				ui->EventParamBox->setCurrentIndex(ui->EventParamBox->findText(getBuildingNameByKey(param.toShort())));
				break;
			case TargetType::INFANTRY:
				ui->EventParamBox->setCurrentIndex(ui->EventParamBox->findText(getUnitNameByKey(param.toShort(), infantry)));
				break;
			case TargetType::VEHICLE:
				ui->EventParamBox->setCurrentIndex(ui->EventParamBox->findText(getUnitNameByKey(param.toShort(), vehicles)));
				break;
			case TargetType::AIRCRAFT:
				ui->EventParamBox->setCurrentIndex(ui->EventParamBox->findText(getUnitNameByKey(param.toShort(), aircraft)));
				break;
			default:
				ui->EventParamBox->setCurrentIndex(param.toInt());
		}
	}
}

// Make selected triggers selected events grow in ascending order
void TriggerSection::on_TEParamAOButton_clicked()
{
	if(ui->EventList->selectedItems().size() != 0 && ui->TriggerList->selectedItems().size() != 0) {
		Trigger *curTrig = getTriggerByName(ui->TriggerList->selectedItems().last()->text());
		Event *curEvent = curTrig->getEvent(ui->EventList->row(ui->EventList->selectedItems().last()));
		int32_t curEventType = curEvent->getType();
		size_t ITPlus = 0;
		for (int32_t a = 0; a != ui->TriggerList->selectedItems().size(); ++a) {
			Trigger *trig = getTriggerByName(ui->TriggerList->selectedItems().at(a)->text());
			for(int32_t b = 0; b != ui->EventList->selectedItems().size(); ++b) {
				if (b < int32_t(trig->events.size())) {
					Event *event = trig->getEvent(ui->EventList->row(ui->EventList->selectedItems().at(b)));
					int32_t eventType = event->getType();
					if (curEventType == eventType) {
						switch(getEventTargetType(eventType)) {
							case TargetType::NONE:
								break;
							case TargetType::WAYPOINT:
							{
								auto IT = std::find(waypoints.begin(), waypoints.end(), ui->SEParameterBox->currentIndex());
								auto endIT = std::find(waypoints.begin(), waypoints.end(), ui->EEParameterBox->currentIndex());
								++endIT;
								IT += ITPlus;
								if (IT != waypoints.end() && IT != endIT) {
									event->setParameter(QString::number(*IT));
								}
								break;
							}
							case TargetType::HOUSE:
							{
								auto IT = houses.begin();
								auto endIT = houses.end();
								for(auto iterIT = houses.begin(); iterIT != houses.end(); ++iterIT) {
									if((*iterIT).second == ui->SEParameterBox->currentText()) {
										IT = iterIT;
									}
									if((*iterIT).second == ui->EEParameterBox->currentText()) {
										endIT = iterIT;
									}
								}
								++endIT;
								for(size_t i = 0; i < ITPlus; ++i) {
									++IT;
								}
								if (IT != houses.end() && IT != endIT) {
									event->setParameter(QString::number((*IT).first));
								}
								break;
							}
							case TargetType::TEAM:
							{
								event->setUnknown(1);
								auto IT = teams.begin();
								auto endIT = teams.begin();
								IT = teams.find(getTeamByName(ui->SEParameterBox->currentText())->getID());
								endIT = teams.find(getTeamByName(ui->EEParameterBox->currentText())->getID());
								++endIT;
								for(size_t i = 0; i < ITPlus; ++i) {
									++IT;
								}
								if (IT != teams.end() && IT != endIT) {
									event->setParameter(IT->second->getID());
								}
								break;
							}
							case TargetType::BUILDING:
							{
								auto IT = buildings.begin();
								auto endIT = buildings.end();
								for(auto iterIT = buildings.begin(); iterIT != buildings.end(); ++iterIT) {
									if((*iterIT).second.name == ui->SEParameterBox->currentText()) {
										IT = iterIT;
									}
									if((*iterIT).second.name == ui->EEParameterBox->currentText()) {
										endIT = iterIT;
									}
								}
								++endIT;
								for(size_t i = 0; i < ITPlus; ++i) {
									++IT;
								}
								if (IT != buildings.end() && IT != endIT) {
									event->setParameter(QString::number((*IT).first));
								}
								break;
							}
							case TargetType::INFANTRY:
							{
								auto IT = infantry.begin();
								auto endIT = infantry.begin();
								for(auto iterIT = infantry.begin(); iterIT != infantry.end(); ++iterIT) {
									if((*iterIT).second.name == ui->SEParameterBox->currentText()) {
										IT = iterIT;
									}
									if((*iterIT).second.name == ui->EEParameterBox->currentText()) {
										endIT = iterIT;
									}
								}
								++endIT;
								for(size_t i = 0; i < ITPlus; ++i) {
									++IT;
								}
								if (IT != infantry.end() && IT != endIT) {
									event->setParameter(QString::number((*IT).second.key));
								}
								break;
							}
							case TargetType::VEHICLE:
							{
								auto IT = vehicles.begin();
								auto endIT = vehicles.begin();
								for(auto iterIT = vehicles.begin(); iterIT != vehicles.end(); ++iterIT) {
									if((*iterIT).second.name == ui->SEParameterBox->currentText()) {
										IT = iterIT;
									}
									if((*iterIT).second.name == ui->EEParameterBox->currentText()) {
										endIT = iterIT;
									}
								}
								++endIT;
								for(size_t i = 0; i < ITPlus; ++i) {
									++IT;
								}
								if (IT != vehicles.end() && IT != endIT) {
									event->setParameter(QString::number((*IT).second.key));
								}
								break;
							}
							case TargetType::AIRCRAFT:
							{
								auto IT = aircraft.begin();
								auto endIT = aircraft.begin();
								for(auto iterIT = aircraft.begin(); iterIT != aircraft.end(); ++iterIT) {
									if((*iterIT).second.name == ui->SEParameterBox->currentText()) {
										IT = iterIT;
									}
									if((*iterIT).second.name == ui->EEParameterBox->currentText()) {
										endIT = iterIT;
									}
								}
								++endIT;
								for(size_t i = 0; i < ITPlus; ++i) {
									++IT;
								}
								if (IT != aircraft.end() && IT != endIT) {
									event->setParameter(QString::number((*IT).second.key));
								}
								break;
							}
							default:
								event->setParameter(QString::number(std::min(ui->SEParameterBox->currentIndex() + ITPlus, size_t(ui->EEParameterBox->currentIndex()))));
								break;
						}
					}
				}
			}
			++ITPlus;
		}
	}
}

// New action
void TriggerSection::on_NewAction_clicked()
{
	if(ui->TriggerList->selectedItems().size() != 0) {
		for (int a = 0; a != ui->TriggerList->selectedItems().size(); ++a) {
			Trigger *curTrig = getTriggerByName(ui->TriggerList->selectedItems().at(a)->text());

			Action *nAction = new Action(curTrig->getID());
			curTrig->addAction(nAction);
		}
		Trigger *curTrig = getTriggerByName(ui->TriggerList->selectedItems().last()->text());
		ui->ActionList->addItem(QString::number(curTrig->actions.size()));
	}
}

// Delete action
void TriggerSection::on_DeleteAction_clicked()
{
	if(ui->TriggerList->selectedItems().size() != 0) {
		for (int a = 0; a != ui->TriggerList->selectedItems().size(); ++a) {
			Trigger *curTrig = getTriggerByName(ui->TriggerList->selectedItems().at(a)->text());

			for(int32_t i = ui->ActionList->selectedItems().size()-1; i != -1; --i) {
				if(int32_t(curTrig->actions.size()) > i) {
					curTrig->eraseAction(ui->ActionList->row(ui->ActionList->selectedItems().at(i)));
				}
			}
		}
		cleanActionList();
	}
}

// Clone action
void TriggerSection::on_CloneAction_clicked()
{
	if(ui->TriggerList->selectedItems().size() != 0) {
		for (int32_t a = 0; a != ui->TriggerList->selectedItems().size(); ++a) {
			Trigger *curTrig = getTriggerByName(ui->TriggerList->selectedItems().at(a)->text());

			size_t actionsCount = curTrig->actions.size();
			size_t i = actionsCount;
			for(int32_t b = 0; b != ui->ActionList->selectedItems().size(); ++b) {
				int32_t actionID = ui->ActionList->row(ui->ActionList->selectedItems().at(b));
				if (actionID < int32_t(actionsCount)) {
					Action *nAct = new Action(curTrig->getAction(actionID), curTrig->getID());
					curTrig->addAction(nAct);

					if (ui->TriggerList->selectedItems().at(a)->text() == ui->TriggerList->selectedItems().last()->text()) {
						++i;
						ui->ActionList->addItem(QString::number(i));
					}
				}
			}
		}
	}
}

void TriggerSection::on_ActionList_itemSelectionChanged()
{
	ui->ActionTypeBox->setCurrentIndex(0);
	ui->ActionParamNameBox->clear();
	ui->ActionParamValueBox->clear();
	if (ui->ActionList->selectedItems().size() != 0 && ui->TriggerList->selectedItems().size() != 0) {
		Trigger *curTrig = getTriggerByName(ui->TriggerList->selectedItems().last()->text());
		int16_t index = curTrig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().last()))->getType();
		if (index < ui->ActionTypeBox->count()) {
			ui->ActionTypeBox->setCurrentIndex(index);
		}
		updateActionParamNameBox();
	}
	ui->ActionTypeBox->view()->setMinimumWidth(getComboBoxMaxWidth(ui->ActionTypeBox) + 50);
}

void TriggerSection::mousePressEvent(QMouseEvent *event)
{
	event->accept();
}

void TriggerSection::cleanActionList() {
	for(int i = 0; i < ui->ActionList->selectedItems().size(); ++i) {
		delete ui->ActionList->selectedItems().at(i);
	}
	ui->ActionList->clear();
	if(ui->TriggerList->selectedItems().size() != 0) {
		Trigger *curTrig = getTriggerByName(ui->TriggerList->selectedItems().last()->text());
		int i = 0;
		for(auto IT = curTrig->actions.begin(); IT != curTrig->actions.end(); ++IT) {
			++i;
			ui->ActionList->addItem(QString::number(i));
		}
	}
}

void TriggerSection::updateActionTypeBox()
{
	QStringList values;
	uint32_t i = 0;
	values = triggerStrings.value("Actions/" + QString::number(i)).toStringList();
	while (!values.isEmpty()) {
		ui->ActionTypeBox->addItem(values[0]);
		++i;
		values = triggerStrings.value("Actions/" + QString::number(i)).toStringList();
	}
}

void TriggerSection::on_ActionTypeBox_activated()
{
	if(ui->TriggerList->selectedItems().size() != 0 && ui->ActionList->selectedItems().size() != 0) {
		for (int a = 0; a != ui->TriggerList->selectedItems().size(); ++a) {
			Trigger *curTrig = getTriggerByName(ui->TriggerList->selectedItems().at(a)->text());
			for(int32_t b = 0; b != ui->ActionList->selectedItems().size(); ++b) {
				size_t index = ui->ActionList->row(ui->ActionList->selectedItems().at(b));
				if(index < curTrig->actions.size()) {
					curTrig->getAction(index)->setType(ui->ActionTypeBox->currentIndex());
					resetActionLine(curTrig->getAction(index));
				}
			}
		}
		updateActionParamNameBox();
	}
}

void TriggerSection::updateActionParamNameBox()
{
	ui->ActionParamNameBox->clear();
	ui->EAParameterBox->clear();
	ui->SAParameterBox->clear();
	if(ui->TriggerList->selectedItems().size() != 0 && ui->ActionList->selectedItems().size() != 0) {
		Trigger *curTrig = getTriggerByName(ui->TriggerList->selectedItems().last()->text());
		Action *curAct = curTrig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().last()));
		int32_t curType = curAct->getType();
		QVariant value = triggerStrings.value("Actions/" + QString::number(curType));
		if (!value.isNull()) {
			QStringList values = value.toStringList();
			bool rowSet = false;
			for (int i = 1; i < 7; ++i) {
				ui->ActionParamNameBox->addItem(getTargetTypeString(values[i].toInt()));
				if (values[i].toInt() == 0 || values[i].toInt() < 0) {
					ui->ActionParamNameBox->setItemData(i - 1, QSize(0,0), Qt::SizeHintRole);
				} else if(!rowSet) {
					ui->ActionParamNameBox->setCurrentIndex(i - 1);
					rowSet = true;
				}
			}
			if (values[7].toInt()) {
				ui->ActionParamNameBox->addItem(getTargetTypeString(30));
			}
			if (rowSet) {
				updateActionParamValueBox();
			} else {
				ui->ActionParamNameBox->clear();
			}
			ui->ActionParamNameBox->view()->setMinimumWidth(getComboBoxMaxWidth(ui->ActionParamNameBox) + 50);
		}
	}
}

QString TriggerSection::getTargetTypeString(int32_t ID)
{
	QVariant value;
	value = triggerStrings.value("ParamTypes/" + QString::number(ID));
	if (!value.isNull()) {
		return value.toStringList()[0];
	} else {
		if (ID < 0) {
			return QString("Unknown");
		} else {
			return QString("Invalid");
		}
	}
}

TargetType TriggerSection::getEventTargetType(int32_t ID)
{
	QVariant value;
	value = triggerStrings.value("Events/" + QString::number(ID));
	if (!value.isNull()) {
		value = triggerStrings.value("ParamTypes/" + QString::number(value.toStringList()[2].toInt()));
		if (!value.isNull()) {
			return static_cast<TargetType>(value.toStringList()[1].toInt());
		}
	}
	return TargetType::NONE;
}

TargetType TriggerSection::getActionTargetType(int32_t ID, uint8_t paramID)
{
	QVariant value;
	value = triggerStrings.value("Actions/" + QString::number(ID));
	if (!value.isNull()) {
		if (paramID > 5 && value.toStringList()[paramID + 1].toInt()) {
			return TargetType::WAYPOINT;
		} else if (value.toStringList()[paramID + 1].toInt() < 0) {
			return TargetType::CONSTANT;
		}
		value = triggerStrings.value("ParamTypes/" + QString::number(value.toStringList()[paramID + 1].toInt()));
		if (!value.isNull()) {
			return static_cast<TargetType>(value.toStringList()[1].toInt());
		}
	}
	return TargetType::NONE;
}

void TriggerSection::on_ActionParamNameBox_activated()
{
	updateActionParamValueBox();
}

void TriggerSection::updateActionParamValueBox()
{
	ui->ActionParamValueBox->setEditable(false);
	ui->ActionParamValueBox->clear();
	ui->EAParameterBox->clear();
	ui->SAParameterBox->clear();

	if(ui->ActionList->selectedItems().size() != 0 && ui->TriggerList->selectedItems().size() != 0) {
		Trigger *curTrig = getTriggerByName(ui->TriggerList->selectedItems().last()->text());
		Action *curAction = curTrig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().last()));
		int32_t type = curAction->getType();
		QString param;
		if (ui->ActionParamNameBox->currentIndex() < 6) {
			param = curAction->getParameter(ui->ActionParamNameBox->currentIndex());
		} else {
			param = curAction->getWaypoint();
		}

		TargetType tType = getActionTargetType(type, ui->ActionParamNameBox->currentIndex());
		QStringList targetList = getTargetStrings(tType);
		ui->ActionParamValueBox->addItems(targetList);
		ui->SAParameterBox->addItems(targetList);
		ui->EAParameterBox->addItems(targetList);
		ui->ActionParamValueBox->view()->setMinimumWidth(getComboBoxMaxWidth(ui->ActionParamValueBox) + 50);
		ui->SAParameterBox->view()->setMinimumWidth(getComboBoxMaxWidth(ui->SAParameterBox) + 50);
		ui->EAParameterBox->view()->setMinimumWidth(getComboBoxMaxWidth(ui->EAParameterBox) + 50);

		switch(getActionTargetType(type, ui->ActionParamNameBox->currentIndex())) {
			case TargetType::NONE:
				break;
			case TargetType::WAYPOINT:
				ui->ActionParamValueBox->setCurrentIndex(ui->ActionParamValueBox->findText(param));
				break;
			case TargetType::HOUSE:
				ui->ActionParamValueBox->setCurrentIndex(ui->ActionParamValueBox->findText(houses[param.toShort()]));
				break;
			case TargetType::TEAM:
			{
				auto IT = teams.find(param);
				if (IT != teams.end()) {
					ui->ActionParamValueBox->setCurrentIndex(ui->ActionParamValueBox->findText(IT->second->getName()));
				}
				break;
			}
			case TargetType::TRIGGER:
			{
				auto IT = triggers.find(param);
				if (IT != triggers.end())
					ui->ActionParamValueBox->setCurrentIndex(ui->ActionParamValueBox->findText(IT->second->getName()));
				break;
			}
			case TargetType::EDITABLE:
				ui->ActionParamValueBox->setEditable(true);
				ui->ActionParamValueBox->setCurrentText(param);
				break;
			case TargetType::TEXT:
				ui->ActionParamValueBox->setCurrentIndex(ui->ActionParamValueBox->findText(tutorial[param.toInt()]));
				break;
			case TargetType::TAG:
			{
				auto IT = tags.find(param);
				if (IT != tags.end()) {
					ui->ActionParamValueBox->setCurrentIndex(ui->ActionParamValueBox->findText(IT->second->getName()));
				}
				break;
			}
			case TargetType::BUILDING:
				ui->ActionParamValueBox->setCurrentIndex(ui->ActionParamValueBox->findText(getBuildingNameByKey(param.toShort())));
				break;
			case TargetType::INFANTRY:
				ui->ActionParamValueBox->setCurrentIndex(ui->ActionParamValueBox->findText(getUnitNameByKey(param.toShort(), infantry)));
				break;
			case TargetType::VEHICLE:
				ui->ActionParamValueBox->setCurrentIndex(ui->ActionParamValueBox->findText(getUnitNameByKey(param.toShort(), vehicles)));
				break;
			case TargetType::AIRCRAFT:
				ui->ActionParamValueBox->setCurrentIndex(ui->ActionParamValueBox->findText(getUnitNameByKey(param.toShort(), aircraft)));
				break;
			default:
				ui->ActionParamValueBox->setCurrentIndex(param.toInt());
		}
	}
}

void TriggerSection::resetActionLine(Action *action)
{
	std::array<QString, 6> params = action->getParameters();
	for (int8_t i = 0; i < 6; ++i) {
		QVariant value = triggerStrings.value("Actions/" + QString::number(action->getType()));
		if (!value.isNull()) {
			int32_t val = value.toStringList()[i + 1].toInt();
			if (val < 0) {
				params[i] = QString::number(abs(val));
			}
		}
	}
	action->setParameters(params);
}

void TriggerSection::on_ActionParamValueBox_activated()
{
	if(ui->TriggerList->selectedItems().size() != 0 && ui->ActionList->selectedItems().size() != 0) {
		Trigger *curTrig = getTriggerByName(ui->TriggerList->selectedItems().last()->text());
		Action *curAction = curTrig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().last()));
		int32_t curActionType = curAction->getType();
		for (int32_t a = 0; a != ui->TriggerList->selectedItems().size(); ++a) {
			Trigger *trig = getTriggerByName(ui->TriggerList->selectedItems().at(a)->text());
			for(int32_t b = 0; b != ui->ActionList->selectedItems().size(); ++b) {
				if (b < int32_t(trig->actions.size())) {
					Action *action = trig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().at(b)));
					int32_t actionType = action->getType();
					int32_t paramID = ui->ActionParamNameBox->currentIndex();
					if (curActionType == actionType) {
						if (paramID < 6) {
							switch(getActionTargetType(actionType, paramID)) {
								case TargetType::NONE:
									action->setWaypoint(0);
									break;
								case TargetType::WAYPOINT:
									action->setParameter(paramID, QString::number(waypoints[ui->ActionParamValueBox->currentIndex()]));
									break;
								case TargetType::HOUSE:
									for(auto IT = houses.begin(); IT != houses.end(); ++IT) {
										if((*IT).second == ui->ActionParamValueBox->currentText()) {
											action->setParameter(paramID, QString::number((*IT).first));
											break;
										}
									}
									break;
								case TargetType::TEAM:
									action->setParameter(paramID, getTeamByName(ui->ActionParamValueBox->currentText())->getID());
									break;
								case TargetType::TRIGGER:
									action->setParameter(paramID, getTriggerByName(ui->ActionParamValueBox->currentText())->getID());
									break;
								case TargetType::EDITABLE:
									action->setParameter(paramID, ui->ActionParamValueBox->currentText());
									break;
								case TargetType::TEXT:
									action->setParameter(paramID, QString::number(getTutorialKeyByText(ui->ActionParamValueBox->currentText())));
									break;
								case TargetType::TAG:
									action->setParameter(paramID, getTagByName(ui->ActionParamValueBox->currentText())->getID());
									break;
								case TargetType::BUILDING:
									for(auto IT = buildings.begin(); IT != buildings.end(); ++IT) {
										if((*IT).second.name == ui->ActionParamValueBox->currentText()) {
											action->setParameter(paramID, QString::number((*IT).first));
											break;
										}
									}
									break;
								case TargetType::INFANTRY:
									action->setParameter(paramID, QString::number(getUnitKeyByName(ui->ActionParamValueBox->currentText(), infantry)));
									break;
								case TargetType::VEHICLE:
									action->setParameter(paramID, QString::number(getUnitKeyByName(ui->ActionParamValueBox->currentText(), vehicles)));
									break;
								case TargetType::AIRCRAFT:
									action->setParameter(paramID, QString::number(getUnitKeyByName(ui->ActionParamValueBox->currentText(), aircraft)));
									break;
								default:
									action->setParameter(paramID, QString::number(ui->ActionParamValueBox->currentIndex()));
							}
						} else {
							action->setWaypoint(waypoints[ui->ActionParamValueBox->currentIndex()]);
						}
					}
				}
			}
		}
	}
}

void TriggerSection::on_AParamAOButton_clicked()
{
	if(ui->ActionList->selectedItems().size() != 0 && ui->TriggerList->selectedItems().size() != 0) {
		Trigger *curTrig = getTriggerByName(ui->TriggerList->selectedItems().last()->text());
		Action *curAction = curTrig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().last()));
		int32_t curActionType = curAction->getType();

		size_t ITPlus = 0;
		for (int32_t a = 0; a != ui->TriggerList->selectedItems().size(); ++a) {
			Trigger *trig = getTriggerByName(ui->TriggerList->selectedItems().at(a)->text());
			for(int32_t b = 0; b != ui->ActionList->selectedItems().size(); ++b) {
				if (b < int32_t(trig->actions.size())) {
					Action *action = trig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().at(b)));
					int32_t actionType = action->getType();
					int32_t paramID = ui->ActionParamNameBox->currentIndex();
					if (curActionType == actionType) {
						switch(getActionTargetType(actionType, paramID)) {
							case TargetType::NONE:
								break;
							case TargetType::WAYPOINT:
							{
								auto IT = std::find(waypoints.begin(), waypoints.end(), ui->SAParameterBox->currentIndex());
								auto endIT = std::find(waypoints.begin(), waypoints.end(), ui->EAParameterBox->currentIndex());
								++endIT;
								IT += ITPlus;
								if (IT != waypoints.end() && IT != endIT) {
									if (paramID < 6) {
										action->setParameter(paramID, QString::number(*IT));
									} else {
										action->setWaypoint(*IT);
									}
								}
								break;
							}
							case TargetType::HOUSE:
							{
								auto IT = houses.begin();
								auto endIT = houses.end();
								for(auto iterIT = houses.begin(); iterIT != houses.end(); ++iterIT) {
									if((*iterIT).second == ui->SAParameterBox->currentText()) {
										IT = iterIT;
									}
									if((*iterIT).second == ui->EAParameterBox->currentText()) {
										endIT = iterIT;
									}
								}
								++endIT;
								for(size_t i = 0; i < ITPlus; ++i) {
									++IT;
								}
								if (IT != houses.end() && IT != endIT) {
									action->setParameter(paramID, QString::number((*IT).first));
								}
								break;
							}
							case TargetType::TEAM:
							{
								auto IT = teams.begin();
								auto endIT = teams.begin();
								IT = teams.find(getTeamByName(ui->SAParameterBox->currentText())->getID());
								endIT = teams.find(getTeamByName(ui->EAParameterBox->currentText())->getID());
								++endIT;
								for(size_t i = 0; i < ITPlus; ++i) {
									++IT;
								}
								if (IT != teams.end() && IT != endIT) {
									action->setParameter(paramID, IT->second->getID());
								}
								break;
							}
							case TargetType::TRIGGER:
							{
								auto IT = triggers.begin();
								auto endIT = triggers.begin();
								IT = triggers.find(getTriggerByName(ui->SAParameterBox->currentText())->getID());
								endIT = triggers.find(getTriggerByName(ui->EAParameterBox->currentText())->getID());
								++endIT;
								for(size_t i = 0; i < ITPlus; ++i) {
									++IT;
								}
								if (IT != triggers.end() && IT != endIT) {
									action->setParameter(paramID, IT->second->getID());
								}
								break;
							}
							case TargetType::TAG:
							{
								auto IT = tags.begin();
								auto endIT = tags.begin();
								IT = tags.find(getTagByName(ui->SAParameterBox->currentText())->getID());
								endIT = tags.find(getTagByName(ui->EAParameterBox->currentText())->getID());
								++endIT;
								for(size_t i = 0; i < ITPlus; ++i) {
									++IT;
								}
								if (IT != tags.end() && IT != endIT) {
									action->setParameter(paramID, IT->second->getID());
								}
								break;
							}
							case TargetType::TEXT:
							{
								auto IT = tutorial.begin();
								auto endIT = tutorial.begin();
								IT = tutorial.find(getTutorialKeyByText(ui->SAParameterBox->currentText()));
								endIT = tutorial.find(getTutorialKeyByText(ui->SEParameterBox->currentText()));
								++endIT;
								for(size_t i = 0; i < ITPlus; ++i) {
									++IT;
								}
								if (IT != tutorial.end() && IT != endIT) {
									action->setParameter(paramID, IT->first);
								}
								break;
							}
							case TargetType::BUILDING:
							{
								auto IT = buildings.begin();
								auto endIT = buildings.end();
								for(auto iterIT = buildings.begin(); iterIT != buildings.end(); ++iterIT) {
									if((*iterIT).second.name == ui->SAParameterBox->currentText()) {
										IT = iterIT;
									}
									if((*iterIT).second.name == ui->EAParameterBox->currentText()) {
										endIT = iterIT;
									}
								}
								++endIT;
								for(size_t i = 0; i < ITPlus; ++i) {
									++IT;
								}
								if (IT != buildings.end() && IT != endIT) {
									action->setParameter(paramID, QString::number((*IT).first));
								}
								break;
							}
							case TargetType::INFANTRY:
							{
								auto IT = infantry.begin();
								auto endIT = infantry.begin();
								for(auto iterIT = infantry.begin(); iterIT != infantry.end(); ++iterIT) {
									if((*iterIT).second.name == ui->SAParameterBox->currentText()) {
										IT = iterIT;
									}
									if((*iterIT).second.name == ui->EAParameterBox->currentText()) {
										endIT = iterIT;
									}
								}
								++endIT;
								for(size_t i = 0; i < ITPlus; ++i) {
									++IT;
								}
								if (IT != infantry.end() && IT != endIT) {
									action->setParameter(paramID, QString::number((*IT).second.key));
								}
								break;
							}
							case TargetType::VEHICLE:
							{
								auto IT = vehicles.begin();
								auto endIT = vehicles.begin();
								for(auto iterIT = vehicles.begin(); iterIT != vehicles.end(); ++iterIT) {
									if((*iterIT).second.name == ui->SAParameterBox->currentText()) {
										IT = iterIT;
									}
									if((*iterIT).second.name == ui->EAParameterBox->currentText()) {
										endIT = iterIT;
									}
								}
								++endIT;
								for(size_t i = 0; i < ITPlus; ++i) {
									++IT;
								}
								if (IT != vehicles.end() && IT != endIT) {
									action->setParameter(paramID, QString::number((*IT).second.key));
								}
								break;
							}
							case TargetType::AIRCRAFT:
							{
								auto IT = aircraft.begin();
								auto endIT = aircraft.begin();
								for(auto iterIT = aircraft.begin(); iterIT != aircraft.end(); ++iterIT) {
									if((*iterIT).second.name == ui->SAParameterBox->currentText()) {
										IT = iterIT;
									}
									if((*iterIT).second.name == ui->EAParameterBox->currentText()) {
										endIT = iterIT;
									}
								}
								++endIT;
								for(size_t i = 0; i < ITPlus; ++i) {
									++IT;
								}
								if (IT != aircraft.end() && IT != endIT) {
									action->setParameter(paramID, QString::number((*IT).second.key));
								}
								break;
							}
							default:
								action->setParameter(paramID, QString::number(std::min(ui->SAParameterBox->currentIndex() + ITPlus, size_t(ui->EAParameterBox->currentIndex()))));
								break;
						}
					}
				}
			}
			++ITPlus;
		}
	}
}

QStringList TriggerSection::getTargetStrings(TargetType type)
{
	QStringList list;
	switch(type) {
		case TargetType::WAYPOINT:
			for(auto IT = waypoints.begin(); IT != waypoints.end(); ++IT) {
				list << QString::number((*IT));
			}
			break;
		case TargetType::LOCAL:
			for(std::map <uint16_t, variableContainer>::iterator IT = localvariables.begin(); IT != localvariables.end(); ++IT) {
				list << (*IT).second.name;
			}
			break;
		case TargetType::GLOBAL:
			for(std::map <uint16_t, variableContainer>::iterator IT = globalvariables.begin(); IT != globalvariables.end(); ++IT) {
				list << (*IT).second.name;
			}
			break;
		case TargetType::HOUSE:
			for(auto IT = houses.begin(); IT != houses.end(); ++IT) {
				list << (*IT).second;
			}
			break;
		case TargetType::TEAM:
			for(auto IT = teams.begin(); IT != teams.end(); ++IT) {
				list << (*IT).second->getName();
			}
			break;
		case TargetType::TRIGGER:
			for(auto IT = triggers.begin(); IT != triggers.end(); ++IT) {
				list << (*IT).second->getName();
			}
			break;
		case TargetType::ONOFF:
			list << "Off";
			list << "On";
			break;
		case TargetType::TEXT:
			for(std::map <uint16_t, QString>::iterator IT = tutorial.begin(); IT != tutorial.end(); ++IT) {
				list << (*IT).second;
			}
			break;
		case TargetType::TAG:
			for(auto IT = tags.begin(); IT != tags.end(); ++IT) {
				list << (*IT).second->getName();
			}
			break;
		case TargetType::BUILDING:
			for(std::map<uint16_t, unitContainer>::iterator IT = buildings.begin(); IT != buildings.end(); ++IT) {
				list << (*IT).second.name;
			}
			break;
		case TargetType::INFANTRY:
			for(auto IT = infantry.begin(); IT != infantry.end(); ++IT) {
				list << (*IT).second.name;
			}
			break;
		case TargetType::VEHICLE:
			for(auto IT = vehicles.begin(); IT != vehicles.end(); ++IT) {
				list << (*IT).second.name;
			}
			break;
		case TargetType::AIRCRAFT:
			for(auto IT = aircraft.begin(); IT != aircraft.end(); ++IT) {
				list << (*IT).second.name;
			}
			break;
		case TargetType::EDITABLE:
		default:
			list << "";
	}
	return list;
}

void TriggerSection::updateUi()
{
	ui->TriggerList->setCurrentRow(-1);
	ui->ActionList->setCurrentRow(-1);
	ui->TriggerList->clear();
	ui->EventTypeBox->clear();
	ui->ActionTypeBox->clear();
	for(auto IT = triggers.begin(); IT != triggers.end(); ++IT) {
		ui->TriggerList->addItem(IT->second->getName());
	}
	updateEventTypeBox();
	updateActionTypeBox();
}

QString TriggerSection::getTriggerNameByPosition(uint32_t pos)
{
	uint32_t i = 0;
	for(auto IT = triggers.begin(); IT != triggers.end(); ++IT) {
		if(i == pos) {
			return IT->second->getName();
		}
		++i;
	}
	return QString("");
}

QString TriggerSection::getTeamNameByPosition(uint32_t pos)
{
	uint32_t i = 0;
	for(auto IT = teams.begin(); IT != teams.end(); ++IT) {
		if(i == pos) {
			return IT->second->getName();
		}
		++i;
	}
	return QString("");
}

QString TriggerSection::getTagNameByPosition(uint32_t pos)
{
	uint32_t i = 0;
	for(auto IT = tags.begin(); IT != tags.end(); ++IT) {
		if(i == pos) {
			return IT->second->getName();
		}
		++i;
	}
	return QString("");
}

QString TriggerSection::getBuildingNameByKey(uint16_t key)
{
	for(std::map<uint16_t, unitContainer>::iterator IT = buildings.begin(); IT != buildings.end(); ++IT) {
		if((*IT).second.key == key) {
			return (*IT).second.name;
		}
	}
	return QString("");
}

QString TriggerSection::getUnitNameByKey(uint16_t key, std::map<QString, unitContainer> &unitMap)
{
	for(auto IT = unitMap.begin(); IT != unitMap.end(); ++IT) {
		if((*IT).second.key == key) {
			return (*IT).second.name;
		}
	}
	return QString("");
}

uint16_t TriggerSection::getTutorialKeyByText(QString text)
{
	for(auto IT = tutorial.begin(); IT != tutorial.end(); ++IT) {
		if ((*IT).second == text) {
			return (*IT).first;
		}
	}
	return 0;
}

uint16_t TriggerSection::getUnitKeyByName(QString name, std::map<QString, unitContainer> &unitMap)
{
	for(auto IT = unitMap.begin(); IT != unitMap.end(); ++IT) {
		if((*IT).second.name == name) {
			return (*IT).second.key;
		}
	}
	return 0;
}

void TriggerSection::on_TagOr_clicked()
{
	if(ui->TriggerList->selectedItems().size() != 0) {
		for (int a = 0; a != ui->TriggerList->selectedItems().size(); ++a) {
			QString trigName = ui->TriggerList->selectedItems().at(a)->text();
			Trigger *curTrig = getTriggerByName(trigName);
			Tag *curTrigTag = getTagByTriggerID(curTrig->getID());
			curTrigTag->setMode(0);
		}
	}
}

void TriggerSection::on_TagAnd_clicked()
{
	if(ui->TriggerList->selectedItems().size() != 0) {
		for (int a = 0; a != ui->TriggerList->selectedItems().size(); ++a) {
			QString trigName = ui->TriggerList->selectedItems().at(a)->text();
			Trigger *curTrig = getTriggerByName(trigName);
			Tag *curTrigTag = getTagByTriggerID(curTrig->getID());
			curTrigTag->setMode(1);
		}
	}
}

void TriggerSection::on_TagRepeatingOr_clicked()
{
	if(ui->TriggerList->selectedItems().size() != 0) {
		for (int a = 0; a != ui->TriggerList->selectedItems().size(); ++a) {
			QString trigName = ui->TriggerList->selectedItems().at(a)->text();
			Trigger *curTrig = getTriggerByName(trigName);
			Tag *curTrigTag = getTagByTriggerID(curTrig->getID());
			curTrigTag->setMode(2);
		}
	}
}
