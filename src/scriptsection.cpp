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

	if(ui->ScriptList->selectedItems().size() != 0) {

		Script *cur_script = GetScriptByName(ui->ScriptList->selectedItems().last()->text().toStdString());
		if(cur_script == NULL) {
			if(QMessageBox::question(this, "Fatal Error!", "Fatal Error occured! Continue?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::No) {
				exit(EXIT_FAILURE);
			}
		}

		ui->SNameEdit->setText(ui->ScriptList->selectedItems().last()->text());

		for(std::vector <Script::ScriptLine*>::iterator IT = cur_script->slines.begin(); IT != cur_script->slines.end(); ++IT) {
			ui->ScriptActionList->addItem(IntToStr((*IT)->ID).c_str());
		}
	}
}

void ScriptSection::on_ScriptActionList_itemSelectionChanged()
{
	if(ui->ScriptList->selectedItems().size() != 0 && ui->ScriptActionList->currentRow() != -1) {
		int index = ui->SATypeBox->findText(GetScriptActionMeaning(GetScriptByName(ui->ScriptList->selectedItems().last()->text().toStdString())->slines[ui->ScriptActionList->currentRow()]->type));
		if(index != -1) {
			ui->SATypeBox->setCurrentIndex(index);
			on_SATypeBox_activated();
		}
	}
}

// Script Action type - box activated
void ScriptSection::on_SATypeBox_activated()
{
	ui->SATargetBox->clear();
	if(ui->ScriptActionList->currentRow() != -1 && ui->ScriptList->selectedItems().size() != 0) {
		for (int a = 0; a != ui->ScriptList->selectedItems().size(); ++a) {
			Script *cur_script = GetScriptByName(ui->ScriptList->selectedItems().at(a)->text().toStdString());
			uint32_t rowNum = ui->ScriptActionList->currentRow();
			if(cur_script->getLineAmount() >= rowNum+1) {
				cur_script->slines[ui->ScriptActionList->currentRow()]->type = ui->SATypeBox->currentIndex();
			}
		}

		QStringList targetList = GetScriptActionTargetStrings(GetScriptActionTargetType(GetScriptByName(ui->ScriptList->selectedItems().last()->text().toStdString())->slines[ui->ScriptActionList->currentRow()]->type));
		ui->SATargetBox->addItems(targetList);
		ui->SATargetBox->view()->setMinimumWidth(GetStringListMaxWidth(targetList, ui->SATargetBox->font())+50);

		short type = GetScriptByName(ui->ScriptList->selectedItems().last()->text().toStdString())->slines[ui->ScriptActionList->currentRow()]->type;
		if(GetScriptActionTargetType(type) == WAYPOINT) {
			stringstream ss;
			ss << GetScriptByName(ui->ScriptList->selectedItems().last()->text().toStdString())->slines[ui->ScriptActionList->currentRow()]->param;
			ui->SATargetBox->setCurrentIndex(ui->SATargetBox->findText(ss.str().c_str()));
		} else {
			ui->SATargetBox->setCurrentIndex(GetScriptByName(ui->ScriptList->selectedItems().last()->text().toStdString())->slines[ui->ScriptActionList->currentRow()]->param);
		}
	}
}

// Script Action target - box activated
void ScriptSection::on_SATargetBox_activated()
{
	if(ui->ScriptActionList->currentRow() != -1 && ui->SATargetBox->currentIndex() != -1 && ui->ScriptList->selectedItems().size() != 0) {
		short type, curtype;
		for (int a = 0; a != ui->ScriptList->selectedItems().size(); ++a) {
			Script *cur_script = GetScriptByName(ui->ScriptList->selectedItems().at(a)->text().toStdString());
			uint32_t rowNum = ui->ScriptActionList->currentRow();
			if(cur_script->getLineAmount() >= rowNum+1) {
				type = GetScriptByName(ui->ScriptList->selectedItems().last()->text().toStdString())->slines[ui->ScriptActionList->currentRow()]->type;
				curtype = GetScriptByName(ui->ScriptList->selectedItems().at(a)->text().toStdString())->slines[ui->ScriptActionList->currentRow()]->type;
				if(curtype == type) {
					if(GetScriptActionTargetType(type) == WAYPOINT) {
						GetScriptByName(ui->ScriptList->selectedItems().at(a)->text().toStdString())->slines[ui->ScriptActionList->currentRow()]->param = waypoints[ui->SATargetBox->currentIndex()];
					} else {
						GetScriptByName(ui->ScriptList->selectedItems().at(a)->text().toStdString())->slines[ui->ScriptActionList->currentRow()]->param = ui->SATargetBox->currentIndex();
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
			string newName = "Clone Of " + ui->ScriptList->selectedItems().at(a)->text().toStdString();

			int i = 0;
			while(ui->ScriptList->findItems(newName.c_str(), Qt::MatchExactly).count() != 0) {
				++i;
				newName = "Clone Of " + ui->ScriptList->selectedItems().at(a)->text().toStdString() + " " + IntToStr(i);
			}

			Script *cur_script = GetScriptByName(ui->ScriptList->selectedItems().at(a)->text().toStdString());

			string newID = fffID();
			scripts[newID] = new Script(newID, cur_script);
			scripts[newID]->setName(newName);
			ui->ScriptList->addItem(newName.c_str());

			vector<Script::ScriptLine*> slines;

			slines = scripts[newID]->GetLinesByType(WAYPOINT);

			for(vector<Script::ScriptLine*>::iterator IT = slines.begin(); IT != slines.end(); ++IT) {
				(*IT)->param = (*IT)->param + short(ui->ScriptList->selectedItems().size() + 1);
			}
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
	if(ui->ScriptList->selectedItems().size() != 0) {
		for (int a = 0; a != ui->ScriptList->selectedItems().size(); ++a) {
			string name = ui->ScriptList->selectedItems().at(a)->text().toStdString();
			string ID = GetScriptIDByName(name);
			delete GetScriptByName(name);
			scripts.erase(ID);
		}
		for (int a = 0; a < ui->ScriptList->selectedItems().size(); ++a) {
			delete ui->ScriptList->selectedItems().at(a);
		}
	}
}

// Edit script mame
void ScriptSection::on_editSN_clicked()
{
	if(ui->ScriptList->findItems(ui->SNameEdit->text(), Qt::MatchExactly).count() == 0) {
		string cur_name = ui->ScriptList->selectedItems().last()->text().toStdString();
		string cur_ID = GetScriptIDByName(cur_name);

		scripts[cur_ID]->setName(ui->SNameEdit->text().toStdString());

		ui->ScriptList->selectedItems().last()->setText(ui->SNameEdit->text());
	}
}

// Clone script
void ScriptSection::on_cloneS_clicked()
{
	if(ui->ScriptList->selectedItems().size() != 0) {
		for(int a = 0; a != ui->ScriptList->selectedItems().size(); ++a) {
			string newName = "Clone Of " + ui->ScriptList->selectedItems().at(a)->text().toStdString();

			int i = 0;
			while(ui->ScriptList->findItems(newName.c_str(), Qt::MatchExactly).count() != 0) {
				++i;
				newName = "Clone Of " + ui->ScriptList->selectedItems().at(a)->text().toStdString() + " " + IntToStr(i);
			}
			string newID = fffID();
			scripts[newID] = new Script(newID, GetScriptByName(ui->ScriptList->selectedItems().at(a)->text().toStdString()));
			scripts[newID]->setName(newName);
			ui->ScriptList->addItem(newName.c_str());
		}
	}
}

// New script action
void ScriptSection::on_newSA_clicked()
{
	if(ui->ScriptList->selectedItems().size() != 0) {
		for(int a = 0; a != ui->ScriptList->selectedItems().size(); ++a) {
			Script *cur_script = GetScriptByName(ui->ScriptList->selectedItems().at(a)->text().toStdString());
			cur_script->NewLine(0, 0);
			string ID;
			ID = IntToStr((*(cur_script->slines.end()-1))->ID);
			ui->ScriptActionList->addItem(ID.c_str());
		}
	}
}

// Delete script action
void ScriptSection::on_delSA_clicked()
{
	if(ui->ScriptActionList->currentRow() != -1) {
		uint32_t rowNum = ui->ScriptActionList->currentRow();
		delete ui->ScriptActionList->item(rowNum);
		for(int a = 0; a != ui->ScriptList->selectedItems().size(); ++a) {
			Script *cur_script = GetScriptByName(ui->ScriptList->selectedItems().at(a)->text().toStdString());

			if(cur_script->getLineAmount() >= rowNum) {
				cur_script->DeleteLine(rowNum);
			}
		}
		Script *cur_script = GetScriptByName(ui->ScriptList->selectedItems().last()->text().toStdString());
		ui->ScriptActionList->clear();
		for(std::vector <Script::ScriptLine*>::iterator IT = cur_script->slines.begin(); IT != cur_script->slines.end(); ++IT) {
			ui->ScriptActionList->addItem(IntToStr((*IT)->ID).c_str());
		}
	}
}

void ScriptSection::UpdateUi() {
	ui->ScriptList->clearSelection();
	ui->ScriptActionList->setCurrentRow(-1);
	ui->ScriptList->clear();
	ui->SATypeBox->clear();
	ui->SATargetBox->clear();
	for(scriptIT IT = scripts.begin(); IT != scripts.end(); ++IT) {
		ui->ScriptList->addItem(IT->second->getName().c_str());
	}
	for(int i = 0; i != 54; ++i) {
		ui->SATypeBox->addItem(GetScriptActionMeaning(i));
	}
}
