#include "scriptsection.h"
#include "ui_scriptsection.h"

using namespace Settings;

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

	if(ui->ScriptList->selectedItems().size() != 0) {
		Script *curScript = getScriptByName(ui->ScriptList->selectedItems().last()->text());

		ui->SNameEdit->setText(ui->ScriptList->selectedItems().last()->text());

		for(std::vector <Script::ScriptLine*>::iterator IT = curScript->scriptLines.begin(); IT != curScript->scriptLines.end(); ++IT) {
			ui->ScriptActionList->addItem(QString::number((*IT)->ID));
		}
	}
}

void ScriptSection::on_ScriptActionList_itemSelectionChanged()
{
	if(ui->ScriptList->selectedItems().size() != 0 && ui->ScriptActionList->currentRow() != -1) {
		int16_t index = getScriptByName(ui->ScriptList->selectedItems().last()->text())->scriptLines[ui->ScriptActionList->currentRow()]->type;
		if(ui->SATypeBox->count() > index) {
			ui->SATypeBox->setCurrentIndex(index);
			updateSATargeBox();
		}
	}
}

// Script Action type box activated
void ScriptSection::on_SATypeBox_activated()
{
	if(ui->ScriptActionList->currentRow() != -1 && ui->ScriptList->selectedItems().size() != 0) {
		for (int a = 0; a != ui->ScriptList->selectedItems().size(); ++a) {
			Script *curScript = getScriptByName(ui->ScriptList->selectedItems().at(a)->text());
			uint32_t rowNum = ui->ScriptActionList->currentRow();
			if(curScript->getLineAmount() >= rowNum+1) {
				curScript->scriptLines[ui->ScriptActionList->currentRow()]->type = ui->SATypeBox->currentIndex();
			}
		}
		updateSATargeBox();
	}
}

// Script Action target box activated
void ScriptSection::on_SATargetBox_activated()
{
	if(ui->ScriptActionList->currentRow() != -1 && ui->SATargetBox->currentIndex() != -1 && ui->ScriptList->selectedItems().size() != 0) {
		int16_t type, curtype;
		uint32_t rowNum = ui->ScriptActionList->currentRow();
		for (int a = 0; a != ui->ScriptList->selectedItems().size(); ++a) {
			Script *curScript = getScriptByName(ui->ScriptList->selectedItems().at(a)->text());
			if(curScript->getLineAmount() >= rowNum+1) {
				type = getScriptByName(ui->ScriptList->selectedItems().last()->text())->scriptLines[rowNum]->type;
				curtype = getScriptByName(ui->ScriptList->selectedItems().at(a)->text())->scriptLines[rowNum]->type;
				if(curtype == type) {
					switch(getScriptActionTargetType(type)) {
						case SATargetType::NONE:
							curScript->scriptLines[rowNum]->param = 0;
							break;
						case SATargetType::WAYPOINT:
							curScript->scriptLines[rowNum]->param = waypoints[ui->SATargetBox->currentIndex()];
							break;
						case SATargetType::EDITABLE:
							curScript->scriptLines[rowNum]->param = ui->SATargetBox->currentText().toInt();
							break;
						case SATargetType::BUILDING:
							if(ui->defaultTarget->isChecked()) {
								curScript->scriptLines[rowNum]->param = buildings[uint16_t(ui->SATargetBox->currentIndex())].key;
							} else if(ui->lowThreat->isChecked()) {
								curScript->scriptLines[rowNum]->param = 65536 + ui->SATargetBox->currentIndex();
							} else if (ui->bigThreat->isChecked()) {
								curScript->scriptLines[rowNum]->param = 131072 + ui->SATargetBox->currentIndex();
							} else if (ui->nearTarget->isChecked()) {
								curScript->scriptLines[rowNum]->param = 196608 + ui->SATargetBox->currentIndex();
							} else if (ui->farTarget->isChecked()) {
								curScript->scriptLines[rowNum]->param = 262144 + ui->SATargetBox->currentIndex();
							}
							break;
						case SATargetType::BALLOON:
							curScript->scriptLines[rowNum]->param = ui->SATargetBox->currentIndex()+1;
							break;
						case SATargetType::HOUSE:
							for(auto IT = houses.begin(); IT != houses.end(); ++IT) {
								if((*IT).second == ui->SATargetBox->currentText()) {
									curScript->scriptLines[rowNum]->param = (*IT).first;
									break;
								}
							}
							break;
						default:
							curScript->scriptLines[rowNum]->param = ui->SATargetBox->currentIndex();
					}
				}
			}
		}
	}
}

// Update Script Action target box
void ScriptSection::updateSATargeBox()
{
	ui->SATargetBox->setEditable(false);
	ui->SATargetBox->clear();

	ui->lowThreat->setDisabled(true);
	ui->bigThreat->setDisabled(true);
	ui->nearTarget->setDisabled(true);
	ui->farTarget->setDisabled(true);
	ui->defaultTarget->setDisabled(true);
	ui->defaultTarget->toggle();

	if(ui->ScriptActionList->currentRow() != -1 && ui->ScriptList->selectedItems().size() != 0) {
		Script *curScript = getScriptByName(ui->ScriptList->selectedItems().last()->text());
		int16_t type = curScript->scriptLines[ui->ScriptActionList->currentRow()]->type;
		int32_t param = curScript->scriptLines[ui->ScriptActionList->currentRow()]->param;

		QStringList targetList = getScriptActionTargetStrings(getScriptActionTargetType(type));
		ui->SATargetBox->addItems(targetList);
		ui->SATargetBox->view()->setMinimumWidth(getStringListMaxWidth(targetList, ui->SATargetBox->font()) + 50);

		switch(getScriptActionTargetType(type)) {
			case SATargetType::NONE:
				break;
			case SATargetType::WAYPOINT:
				ui->SATargetBox->setCurrentIndex(ui->SATargetBox->findText(QString::number(param)));
				break;
			case SATargetType::EDITABLE:
				ui->SATargetBox->setEditable(true);
				ui->SATargetBox->setCurrentText(QString::number(param));
				break;
			case SATargetType::SCRIPT:
				ui->SATargetBox->setCurrentIndex(ui->SATargetBox->findText(getScriptNameByPosition(param)));
				break;
			case SATargetType::TASKFORCE:
				ui->SATargetBox->setCurrentIndex(ui->SATargetBox->findText(getTaskforceNameByPosition(param)));
				break;
			case SATargetType::BUILDING:
				ui->lowThreat->setDisabled(false);
				ui->bigThreat->setDisabled(false);
				ui->nearTarget->setDisabled(false);
				ui->farTarget->setDisabled(false);
				ui->defaultTarget->setDisabled(false);

				if(param < 65536) {
					ui->SATargetBox->setCurrentIndex(ui->SATargetBox->findText(buildings[getBuildingTypePosByKey(param)].name));
					ui->defaultTarget->toggle();
				} else if (param >= 65536 && param < 131072) {
					ui->SATargetBox->setCurrentIndex(ui->SATargetBox->findText(buildings[param-65536].name));
					ui->lowThreat->toggle();
				} else if (param >= 131072 && param < 196608) {
					ui->SATargetBox->setCurrentIndex(ui->SATargetBox->findText(buildings[param-131072].name));
					ui->bigThreat->toggle();
				} else if (param >= 196608 && param < 262144) {
					ui->SATargetBox->setCurrentIndex(ui->SATargetBox->findText(buildings[param-196608].name));
					ui->nearTarget->toggle();
				} else if (param >= 262144) {
					ui->SATargetBox->setCurrentIndex(ui->SATargetBox->findText(buildings[param-262144].name));
					ui->farTarget->toggle();
				}
				break;
			case SATargetType::BALLOON:
				ui->SATargetBox->setCurrentIndex(param-1);
				break;
			case SATargetType::HOUSE:
				ui->SATargetBox->setCurrentIndex(ui->SATargetBox->findText(houses[param]));
				break;
			default:
				ui->SATargetBox->setCurrentIndex(param);
		}
	}
}

// Lowest threat target for BUILDING target type
void ScriptSection::on_lowThreat_clicked()
{
	if(ui->ScriptActionList->currentRow() != -1 && ui->ScriptList->selectedItems().size() != 0) {
		short type, curtype;
		for (int a = 0; a != ui->ScriptList->selectedItems().size(); ++a) {
			Script *curScript = getScriptByName(ui->ScriptList->selectedItems().at(a)->text());
			uint32_t rowNum = ui->ScriptActionList->currentRow();
			if(curScript->getLineAmount() >= rowNum+1) {
				type = getScriptByName(ui->ScriptList->selectedItems().last()->text())->scriptLines[ui->ScriptActionList->currentRow()]->type;
				curtype = getScriptByName(ui->ScriptList->selectedItems().at(a)->text())->scriptLines[ui->ScriptActionList->currentRow()]->type;
				if(curtype == type) {
					curScript->scriptLines[rowNum]->param = 65536 + ui->SATargetBox->currentIndex();
				}
			}
		}
	}
}

// Biggest threat target for BUILDING target type
void ScriptSection::on_bigThreat_clicked()
{
	if(ui->ScriptActionList->currentRow() != -1 && ui->ScriptList->selectedItems().size() != 0) {
		short type, curtype;
		for (int a = 0; a != ui->ScriptList->selectedItems().size(); ++a) {
			Script *curScript = getScriptByName(ui->ScriptList->selectedItems().at(a)->text());
			uint32_t rowNum = ui->ScriptActionList->currentRow();
			if(curScript->getLineAmount() >= rowNum+1) {
				type = getScriptByName(ui->ScriptList->selectedItems().last()->text())->scriptLines[ui->ScriptActionList->currentRow()]->type;
				curtype = getScriptByName(ui->ScriptList->selectedItems().at(a)->text())->scriptLines[ui->ScriptActionList->currentRow()]->type;
				if(curtype == type) {
					curScript->scriptLines[rowNum]->param = 131072 + ui->SATargetBox->currentIndex();
				}
			}
		}
	}
}

// Nearest target for BUILDING target type
void ScriptSection::on_nearTarget_clicked()
{
	if(ui->ScriptActionList->currentRow() != -1 && ui->ScriptList->selectedItems().size() != 0) {
		short type, curtype;
		for (int a = 0; a != ui->ScriptList->selectedItems().size(); ++a) {
			Script *curScript = getScriptByName(ui->ScriptList->selectedItems().at(a)->text());
			uint32_t rowNum = ui->ScriptActionList->currentRow();
			if(curScript->getLineAmount() >= rowNum+1) {
				type = getScriptByName(ui->ScriptList->selectedItems().last()->text())->scriptLines[ui->ScriptActionList->currentRow()]->type;
				curtype = getScriptByName(ui->ScriptList->selectedItems().at(a)->text())->scriptLines[ui->ScriptActionList->currentRow()]->type;
				if(curtype == type) {
					curScript->scriptLines[rowNum]->param = 196608 + ui->SATargetBox->currentIndex();
				}
			}
		}
	}
}

// Farthest target for BUILDING target type
void ScriptSection::on_farTarget_clicked()
{
	if(ui->ScriptActionList->currentRow() != -1 && ui->ScriptList->selectedItems().size() != 0) {
		short type, curtype;
		for (int a = 0; a != ui->ScriptList->selectedItems().size(); ++a) {
			Script *curScript = getScriptByName(ui->ScriptList->selectedItems().at(a)->text());
			uint32_t rowNum = ui->ScriptActionList->currentRow();
			if(curScript->getLineAmount() >= rowNum+1) {
				type = getScriptByName(ui->ScriptList->selectedItems().last()->text())->scriptLines[ui->ScriptActionList->currentRow()]->type;
				curtype = getScriptByName(ui->ScriptList->selectedItems().at(a)->text())->scriptLines[ui->ScriptActionList->currentRow()]->type;
				if(curtype == type) {
					curScript->scriptLines[rowNum]->param = 262144 + ui->SATargetBox->currentIndex();
				}
			}
		}
	}
}

// Default target
void ScriptSection::on_defaultTarget_clicked()
{
	if(ui->ScriptActionList->currentRow() != -1 && ui->ScriptList->selectedItems().size() != 0) {
		short type, curtype;
		for (int a = 0; a != ui->ScriptList->selectedItems().size(); ++a) {
			Script *curScript = getScriptByName(ui->ScriptList->selectedItems().at(a)->text());
			uint32_t rowNum = ui->ScriptActionList->currentRow();
			if(curScript->getLineAmount() >= rowNum+1) {
				type = getScriptByName(ui->ScriptList->selectedItems().last()->text())->scriptLines[ui->ScriptActionList->currentRow()]->type;
				curtype = getScriptByName(ui->ScriptList->selectedItems().at(a)->text())->scriptLines[ui->ScriptActionList->currentRow()]->type;
				if(curtype == type) {
					curScript->scriptLines[rowNum]->param = buildings[uint16_t(ui->SATargetBox->currentIndex())].key;
				}
			}
		}
	}
}

// Type of EDITABLE param editing
void ScriptSection::on_SATargetBox_editTextChanged(const QString &arg1)
{
	if(ui->ScriptActionList->currentRow() != -1 && ui->SATargetBox->currentIndex() != -1 && ui->ScriptList->selectedItems().size() != 0) {
		short type, curtype;
		for (int a = 0; a != ui->ScriptList->selectedItems().size(); ++a) {
			Script *curScript = getScriptByName(ui->ScriptList->selectedItems().at(a)->text());
			uint32_t rowNum = ui->ScriptActionList->currentRow();
			if(curScript->getLineAmount() >= rowNum+1) {
				type = getScriptByName(ui->ScriptList->selectedItems().last()->text())->scriptLines[ui->ScriptActionList->currentRow()]->type;
				curtype = getScriptByName(ui->ScriptList->selectedItems().at(a)->text())->scriptLines[ui->ScriptActionList->currentRow()]->type;
				if(curtype == type) {
					if(getScriptActionTargetType(type) == SATargetType::EDITABLE) {
						curScript->scriptLines[rowNum]->param = arg1.toInt();
					}
				}
			}
		}
	}
}

// Clone script and add 1 for all waypoints of actions of script
void ScriptSection::on_CLastButton_clicked()
{
	if(ui->ScriptList->selectedItems().size() != 0) {
		for(int a = 0; a != ui->ScriptList->selectedItems().size(); ++a) {
			QString newName = getNameWithNextMark(ui->ScriptList->selectedItems().at(a)->text(), a, 0);

			int i = 0;
			while(ui->ScriptList->findItems(newName, Qt::MatchExactly).count() != 0) {
				++i;
				newName = getNameWithNextMark(ui->ScriptList->selectedItems().at(a)->text(), i);
			}

			Script *curScript = getScriptByName(ui->ScriptList->selectedItems().at(a)->text());

			QString newID = findFirstFreeID();
			scripts[newID] = new Script(newID, curScript);
			scripts[newID]->setName(newName);
			ui->ScriptList->addItem(scripts[newID]->getName());

			std::vector<Script::ScriptLine*> slines;

			slines = scripts[newID]->getLinesByType(SATargetType::WAYPOINT);

			for(std::vector<Script::ScriptLine*>::iterator IT = slines.begin(); IT != slines.end(); ++IT) {
				(*IT)->param = (*IT)->param + short(ui->ScriptList->selectedItems().size());
			}
		}

	}
}

// New script
void ScriptSection::on_newS_clicked()
{
	if(ui->ScriptList->findItems(ui->SNameEdit->text(), Qt::MatchExactly).count() == 0) {
		QString name = ui->SNameEdit->text();
		ui->ScriptList->addItem(ui->SNameEdit->text());
		QString nID = findFirstFreeID();
		scripts[nID] = new Script(nID, name);
	}
}

// Delete script(s)
void ScriptSection::on_delS_clicked()
{
	if(ui->ScriptList->selectedItems().size() != 0) {
		for (int a = 0; a != ui->ScriptList->selectedItems().size(); ++a) {
			QString name = ui->ScriptList->selectedItems().at(a)->text();
			QString ID = getScriptIDByName(name);
			delete getScriptByName(name);
			scripts.erase(ID);
		}
		updateUi();
	}
}

// Edit script mame
void ScriptSection::on_editSN_clicked()
{
	if(ui->ScriptList->selectedItems().size() != 0) {
		if(ui->ScriptList->findItems(ui->SNameEdit->text(), Qt::MatchExactly).count() == 0) {
			QString curName = ui->ScriptList->selectedItems().last()->text();
			QString curID = getScriptIDByName(curName);

			scripts[curID]->setName(ui->SNameEdit->text());

			ui->ScriptList->selectedItems().last()->setText(ui->SNameEdit->text());
		}
	}
}

// Clone script(s)
void ScriptSection::on_cloneS_clicked()
{
	if(ui->ScriptList->selectedItems().size() != 0) {
		for(int a = 0; a != ui->ScriptList->selectedItems().size(); ++a) {
			QString newName = getNameWithNextMark(ui->ScriptList->selectedItems().at(a)->text(), a, 0);

			int i = 0;
			while(ui->ScriptList->findItems(newName, Qt::MatchExactly).count() != 0) {
				++i;
				newName = getNameWithNextMark(ui->ScriptList->selectedItems().at(a)->text(), i);
			}
			QString newID = findFirstFreeID();
			scripts[newID] = new Script(newID, getScriptByName(ui->ScriptList->selectedItems().at(a)->text()));
			scripts[newID]->setName(newName);
			ui->ScriptList->addItem(newName);
		}
	}
}

// New script action
void ScriptSection::on_newSA_clicked()
{
	if(ui->ScriptList->selectedItems().size() != 0) {
		for(int a = 0; a != ui->ScriptList->selectedItems().size(); ++a) {
			Script *curScript = getScriptByName(ui->ScriptList->selectedItems().at(a)->text());
			curScript->addLine(0, 0);
		}
		QString ID;
		ID = QString::number((*(getScriptByName(ui->ScriptList->selectedItems().last()->text())->scriptLines.end()-1))->ID);
		ui->ScriptActionList->addItem(ID);
	}
}

// New script action before current action
void ScriptSection::on_newSA_Bef_clicked()
{
	if(ui->ScriptActionList->currentRow() != -1) {
		uint32_t rowNum = ui->ScriptActionList->currentRow();
		for(int a = 0; a != ui->ScriptList->selectedItems().size(); ++a) {
			Script *curScript = getScriptByName(ui->ScriptList->selectedItems().at(a)->text());
			if(curScript->getLineAmount() >= rowNum) {
				curScript->insertLine(0, 0, rowNum);
			}
		}
		Script *curScript = getScriptByName(ui->ScriptList->selectedItems().last()->text());
		ui->ScriptActionList->clear();
		for(std::vector <Script::ScriptLine*>::iterator IT = curScript->scriptLines.begin(); IT != curScript->scriptLines.end(); ++IT) {
			ui->ScriptActionList->addItem(QString::number((*IT)->ID));
		}
	}
}

void ScriptSection::mousePressEvent(QMouseEvent *event)
{
	event->accept();
}

// Delete script action
void ScriptSection::on_delSA_clicked()
{
	if(ui->ScriptActionList->currentRow() != -1) {
		uint32_t rowNum = ui->ScriptActionList->currentRow();
		delete ui->ScriptActionList->item(rowNum);
		for(int a = 0; a != ui->ScriptList->selectedItems().size(); ++a) {
			Script *curScript = getScriptByName(ui->ScriptList->selectedItems().at(a)->text());

			if(curScript->getLineAmount() >= rowNum) {
				curScript->deleteLine(rowNum);
			}
		}
		Script *curScript = getScriptByName(ui->ScriptList->selectedItems().last()->text());
		ui->ScriptActionList->clear();
		for(std::vector <Script::ScriptLine*>::iterator IT = curScript->scriptLines.begin(); IT != curScript->scriptLines.end(); ++IT) {
			ui->ScriptActionList->addItem(QString::number((*IT)->ID));
		}
	}
}

void ScriptSection::updateSATypeBox()
{
	QStringList values;
	uint32_t i = 0;
	values = scriptStrings.value("Actions/" + QString::number(i)).toStringList();
	while (!values.isEmpty()) {
		ui->SATypeBox->addItem(values[0]);
		++i;
		values = scriptStrings.value("Actions/" + QString::number(i)).toStringList();
	}
}

QStringList ScriptSection::getScriptActionTargetStrings(SATargetType type)
{
	QStringList list;
	QStringList strList;

	switch(type) {
	case SATargetType::TARGET:
		scriptStrings.beginGroup("Target");
		strList = scriptStrings.childKeys();
		qSort(strList.begin(), strList.end(), lessThanQString);
		for(QStringList::ConstIterator IT = strList.begin(); IT != strList.end(); ++IT) {
			list << scriptStrings.value((*IT)).toStringList().join(", ");
		}
		scriptStrings.endGroup();
		break;
	case SATargetType::WAYPOINT:
		for(waypointIT IT = waypoints.begin(); IT != waypoints.end(); ++IT) {
			list << QString::number((*IT));
		}
		break;
	case SATargetType::UNLOAD:
		scriptStrings.beginGroup("Unload");
		strList = scriptStrings.childKeys();
		qSort(strList.begin(), strList.end(), lessThanQString);
		for(QStringList::ConstIterator IT = strList.begin(); IT != strList.end(); ++IT) {
			list << scriptStrings.value((*IT)).toStringList().join(", ");
		}
		scriptStrings.endGroup();
		break;
	case SATargetType::MISSION:
		scriptStrings.beginGroup("Mission");
		strList = scriptStrings.childKeys();
		qSort(strList.begin(), strList.end(), lessThanQString);
		for(QStringList::ConstIterator IT = strList.begin(); IT != strList.end(); ++IT) {
			list << scriptStrings.value((*IT)).toStringList().join(", ");
		}
		scriptStrings.endGroup();
		break;
	case SATargetType::BUILDING:
		for(std::map<uint16_t, unitContainer>::iterator IT = buildings.begin(); IT != buildings.end(); ++IT) {
			list << (*IT).second.name;
		}
		break;
	case SATargetType::BALLOON:
		scriptStrings.beginGroup("Balloon");
		strList = scriptStrings.childKeys();
		qSort(strList.begin(), strList.end(), lessThanQString);
		for(QStringList::ConstIterator IT = strList.begin(); IT != strList.end(); ++IT) {
			list << scriptStrings.value((*IT)).toStringList().join(", ");
		}
		scriptStrings.endGroup();
		break;
	case SATargetType::FACING:
		scriptStrings.beginGroup("Facing");
		strList = scriptStrings.childKeys();
		qSort(strList.begin(), strList.end(), lessThanQString);
		for(QStringList::ConstIterator IT = strList.begin(); IT != strList.end(); ++IT) {
			list << scriptStrings.value((*IT)).toStringList().join(", ");
		}
		scriptStrings.endGroup();
		break;
	case SATargetType::LOCAL:
		for(std::map <uint16_t, variableContainer>::iterator IT = localvariables.begin(); IT != localvariables.end(); ++IT) {
			list << (*IT).second.name;
		}
		break;
	case SATargetType::GLOBAL:
		for(std::map <uint16_t, variableContainer>::iterator IT = globalvariables.begin(); IT != globalvariables.end(); ++IT) {
			list << (*IT).second.name;
		}
		break;
	case SATargetType::SCRIPT:
		for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
			list << (*IT).second->getName();
		}
		break;
	case SATargetType::TASKFORCE:
		for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
			list << (*IT).second->getName();
		}
		break;
	case SATargetType::HOUSE:
		for(auto IT = houses.begin(); IT != houses.end(); ++IT) {
			list << (*IT).second;
		}
		break;
	case SATargetType::EDITABLE:
	default:
		list << "";
	}
	return list;
}

QString ScriptSection::getScriptNameByPosition(uint16_t pos)
{
	int i = 0;
	for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		if(i == pos) {
			return IT->second->getName();
		}
		++i;
	}
	return QString("");
}

QString ScriptSection::getTaskforceNameByPosition(uint16_t pos)
{
	int i = 0;
	for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		if(i == pos) {
			return IT->second->getName();
		}
		++i;
	}
	return QString("");
}

void ScriptSection::updateUi()
{
	ui->ScriptList->clearSelection();
	ui->ScriptActionList->setCurrentRow(-1);
	ui->ScriptList->clear();
	ui->SATypeBox->clear();
	ui->SATargetBox->clear();
	for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		ui->ScriptList->addItem(IT->second->getName());
	}
	updateSATypeBox();
	ui->SATypeBox->view()->setMinimumWidth(180);
}
