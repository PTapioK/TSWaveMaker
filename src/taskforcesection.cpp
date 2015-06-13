#include "taskforcesection.h"
#include "ui_taskforcesection.h"

TaskforceSection::TaskforceSection(QWidget *parent) :
	QDockWidget(parent),
	ui(new Ui::TaskforceSection)
{
	ui->setupUi(this);
}

TaskforceSection::~TaskforceSection()
{
	delete ui;
}

void TaskforceSection::on_TaskforceList_itemSelectionChanged()
{
	ui->UnitList->setCurrentRow(-1);
	ui->UnitList->clear();
	ui->UnitBox->setCurrentIndex(-1);
	ui->UnitNumberBox->setValue(0);
	if(ui->TaskforceList->selectedItems().size() != NULL) {
		Taskforce *cur_taskforce = GetTaskforceByName(ui->TaskforceList->selectedItems().last()->text().toStdString());
		ui->taskforceNameEdit->setText(ui->TaskforceList->selectedItems().last()->text());

		for(std::vector <Taskforce::TaskforceLine*>::iterator tlineIT = cur_taskforce->tlines.begin(); tlineIT != cur_taskforce->tlines.end(); ++tlineIT) {
			ui->UnitList->addItem(string(IntToStr((*tlineIT)->amount) + " " + GetUnitNameByUnitID((*tlineIT)->type)).c_str());
		}
	}
}

// New taskforce
void TaskforceSection::on_NewTaskforce_clicked()
{
	if(ui->TaskforceList->findItems(ui->taskforceNameEdit->text(), Qt::MatchExactly).count() == 0) {
		string name = ui->taskforceNameEdit->text().toStdString();
		ui->TaskforceList->addItem(ui->taskforceNameEdit->text());
		string nID = fffID();
		taskforces[nID] = new Taskforce(nID, name);
	}
}

// Delete taskforce
void TaskforceSection::on_DeleteTaskforce_clicked()
{
	if(ui->TaskforceList->selectedItems().size() != 0) {
		for (int a = 0; a != ui->TaskforceList->selectedItems().size(); ++a) {
			string name = ui->TaskforceList->selectedItems().at(a)->text().toStdString();
			string ID = GetTaskforceIDByName(name);
			delete GetTaskforceByName(name);
			taskforces.erase(ID);
		}
		UpdateUi();
	}
}

// Edit taskforce name
void TaskforceSection::on_editTaskforceName_clicked()
{
	if(ui->TaskforceList->selectedItems().size() != 0) {
		if(ui->TaskforceList->findItems(ui->taskforceNameEdit->text(), Qt::MatchExactly).count() == 0) {
			string cur_name = ui->TaskforceList->selectedItems().last()->text().toStdString();
			string cur_ID = GetTaskforceIDByName(cur_name);

			taskforces[cur_ID]->setName(ui->taskforceNameEdit->text().toStdString());

			ui->TaskforceList->selectedItems().last()->setText(ui->taskforceNameEdit->text());
		}
	}
}

// Clone taskforce(s)
void TaskforceSection::on_cloneTaskforce_clicked()
{
	if(ui->TaskforceList->selectedItems().size() != 0) {
		for(int a = 0; a != ui->TaskforceList->selectedItems().size(); ++a) {
			string newName = GetNameWithNextMark(ui->TaskforceList->selectedItems().at(a)->text().toStdString(), a);

			int i = 0;
			while(ui->TaskforceList->findItems(newName.c_str(), Qt::MatchExactly).count() != 0) {
				++i;
				newName = GetNameWithNextMark(ui->TaskforceList->selectedItems().at(a)->text().toStdString(), i);
			}
			string newID = fffID();
			taskforces[newID] = new Taskforce(newID, GetTaskforceByName(ui->TaskforceList->selectedItems().at(a)->text().toStdString()));
			taskforces[newID]->setName(newName);
			ui->TaskforceList->addItem(newName.c_str());
		}
	}
}

// Taskforce line selected
void TaskforceSection::on_UnitList_itemSelectionChanged()
{
	if(ui->TaskforceList->selectedItems().size() != 0 && ui->UnitList->currentRow() != -1) {
		Taskforce *cur_taskforce = GetTaskforceByName(ui->TaskforceList->selectedItems().last()->text().toStdString());
		string unitID = cur_taskforce->tlines[ui->UnitList->currentRow()]->type;
		int index = ui->UnitBox->findText(string("["+unitID+"] "+GetUnitNameByUnitID(unitID)).c_str());
		if(index != -1) {
			ui->UnitBox->setCurrentIndex(index);
		}
		ui->UnitNumberBox->setValue(cur_taskforce->tlines[ui->UnitList->currentRow()]->amount);

	}
}

void TaskforceSection::on_UnitBox_activated()
{
	if(ui->TaskforceList->selectedItems().size() != 0 && ui->UnitList->currentRow() != -1 && ui->UnitBox->currentIndex() != -1) {
		for(int a = 0; a != ui->TaskforceList->selectedItems().size(); ++a) {
			Taskforce *cur_taskforce = GetTaskforceByName(ui->TaskforceList->selectedItems().at(a)->text().toStdString());
			uint32_t rowNum = ui->UnitList->currentRow();
			if(cur_taskforce->getLineAmount() >= rowNum+1) {
				string newType = ui->UnitBox->currentText().toStdString();
				cur_taskforce->tlines[rowNum]->type = newType.substr(1, newType.find("]")-1);
				ui->UnitList->currentItem()->setText(string(IntToStr(cur_taskforce->tlines[rowNum]->amount) + " " + GetUnitNameByUnitID(cur_taskforce->tlines[rowNum]->type)).c_str());
			}
		}
	}
}

void TaskforceSection::on_UnitNumberBox_editingFinished()
{
	if(ui->TaskforceList->selectedItems().size() != 0 && ui->UnitList->currentRow() != -1) {
		for(int a = 0; a != ui->TaskforceList->selectedItems().size(); ++a) {
			Taskforce *cur_taskforce = GetTaskforceByName(ui->TaskforceList->selectedItems().at(a)->text().toStdString());
			uint32_t rowNum = ui->UnitList->currentRow();
			if(cur_taskforce->getLineAmount() >= rowNum+1) {
				cur_taskforce->tlines[rowNum]->amount = ui->UnitNumberBox->value();
				ui->UnitList->currentItem()->setText(string(IntToStr(cur_taskforce->tlines[rowNum]->amount) + " " + GetUnitNameByUnitID(cur_taskforce->tlines[rowNum]->type)).c_str());
			}
		}
	}
}

void TaskforceSection::on_AddUnit_clicked()
{
	if(ui->TaskforceList->selectedItems().size() != 0) {
		for(int a = 0; a != ui->TaskforceList->selectedItems().size(); ++a) {
			Taskforce *cur_taskforce = GetTaskforceByName(ui->TaskforceList->selectedItems().at(a)->text().toStdString());
			cur_taskforce->NewLine("APACHE", 0);
		}
		string ID;
		Taskforce *cur_taskforce = GetTaskforceByName(ui->TaskforceList->selectedItems().last()->text().toStdString());
		ID = IntToStr((*(cur_taskforce->tlines.end()-1))->amount) + " " + GetUnitNameByUnitID((*(cur_taskforce->tlines.end()-1))->type);
		ui->UnitList->addItem(ID.c_str());
	}
}

void TaskforceSection::on_DeleteUnit_clicked()
{
	if(ui->UnitList->currentRow() != -1) {
		uint32_t rowNum = ui->UnitList->currentRow();
		delete ui->UnitList->item(rowNum);
		for(int a = 0; a != ui->TaskforceList->selectedItems().size(); ++a) {
			Taskforce *cur_taskforce = GetTaskforceByName(ui->TaskforceList->selectedItems().at(a)->text().toStdString());
			if(cur_taskforce->getLineAmount() >= rowNum) {
				cur_taskforce->DeleteLine(rowNum);
			}
		}
		Taskforce *cur_taskforce = GetTaskforceByName(ui->TaskforceList->selectedItems().last()->text().toStdString());
		ui->UnitList->clear();
		for(std::vector <Taskforce::TaskforceLine*>::iterator tlineIT = cur_taskforce->tlines.begin(); tlineIT != cur_taskforce->tlines.end(); ++tlineIT) {
			ui->UnitList->addItem(string(IntToStr((*tlineIT)->amount) + " " + GetUnitNameByUnitID((*tlineIT)->type)).c_str());
		}
	}

}

void TaskforceSection::UpdateUi()
{
	ui->TaskforceList->clearSelection();
	ui->TaskforceList->clear();
	ui->UnitBox->clear();
	for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		ui->TaskforceList->addItem(IT->second->getName().c_str());
	}
	for(unitIT IT = aircraftnames.begin(); IT != aircraftnames.end(); ++IT) {
		ui->UnitBox->addItem(string("["+IT->first+"] "+IT->second.name).c_str());
	}
	for(unitIT IT = infantrynames.begin(); IT != infantrynames.end(); ++IT) {
		ui->UnitBox->addItem(string("["+IT->first+"] "+IT->second.name).c_str());
	}
	for(unitIT IT = vehiclenames.begin(); IT != vehiclenames.end(); ++IT) {
		ui->UnitBox->addItem(string("["+IT->first+"] "+IT->second.name).c_str());
	}
	ui->UnitBox->view()->setMinimumWidth(220);
}
