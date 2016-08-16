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
		Taskforce *curTaskforce = getTaskforceByName(ui->TaskforceList->selectedItems().last()->text());
		ui->taskforceNameEdit->setText(ui->TaskforceList->selectedItems().last()->text());

		for(std::vector <Taskforce::TaskforceLine*>::iterator taskforceLineIT = curTaskforce->taskforceLines.begin(); taskforceLineIT != curTaskforce->taskforceLines.end(); ++taskforceLineIT) {
			ui->UnitList->addItem(QString(QString::number((*taskforceLineIT)->amount) + " " + getUnitNameByUnitID((*taskforceLineIT)->type)));
		}
	}
}

// New taskforce
void TaskforceSection::on_NewTaskforce_clicked()
{
	if(ui->TaskforceList->findItems(ui->taskforceNameEdit->text(), Qt::MatchExactly).count() == 0) {
		QString name = ui->taskforceNameEdit->text();
		ui->TaskforceList->addItem(ui->taskforceNameEdit->text());
		QString nID = findFirstFreeID();
		taskforces[nID] = new Taskforce(nID, name);
	}
}

// Delete taskforce
void TaskforceSection::on_DeleteTaskforce_clicked()
{
	if(ui->TaskforceList->selectedItems().size() != 0) {
		for (int a = 0; a != ui->TaskforceList->selectedItems().size(); ++a) {
			QString name = ui->TaskforceList->selectedItems().at(a)->text();
			QString ID = getTaskforceIDByName(name);
			delete getTaskforceByName(name);
			taskforces.erase(ID);
		}
		updateUi();
	}
}

// Edit taskforce name
void TaskforceSection::on_editTaskforceName_clicked()
{
	if(ui->TaskforceList->selectedItems().size() != 0) {
		if(ui->TaskforceList->findItems(ui->taskforceNameEdit->text(), Qt::MatchExactly).count() == 0) {
			QString curName = ui->TaskforceList->selectedItems().last()->text();
			QString curID = getTaskforceIDByName(curName);

			taskforces[curID]->setName(ui->taskforceNameEdit->text());

			ui->TaskforceList->selectedItems().last()->setText(ui->taskforceNameEdit->text());
		}
	}
}

// Clone taskforce(s)
void TaskforceSection::on_cloneTaskforce_clicked()
{
	if(ui->TaskforceList->selectedItems().size() != 0) {
		for(int a = 0; a != ui->TaskforceList->selectedItems().size(); ++a) {
			QString newName = getNameWithNextMark(ui->TaskforceList->selectedItems().at(a)->text(), a, 0);

			int i = 0;
			while(ui->TaskforceList->findItems(newName, Qt::MatchExactly).count() != 0) {
				++i;
				newName = getNameWithNextMark(ui->TaskforceList->selectedItems().at(a)->text(), i);
			}
			QString newID = findFirstFreeID();
			taskforces[newID] = new Taskforce(newID, getTaskforceByName(ui->TaskforceList->selectedItems().at(a)->text()));
			taskforces[newID]->setName(newName);
			ui->TaskforceList->addItem(newName);
		}
	}
}

// Taskforce line selected
void TaskforceSection::on_UnitList_itemSelectionChanged()
{
	if(ui->TaskforceList->selectedItems().size() != 0 && ui->UnitList->currentRow() != -1) {
		Taskforce *curTaskforce = getTaskforceByName(ui->TaskforceList->selectedItems().last()->text());
		QString unitID = curTaskforce->taskforceLines[ui->UnitList->currentRow()]->type;
		int index = ui->UnitBox->findText(QString("["+unitID+"] "+getUnitNameByUnitID(unitID)));
		if(index != -1) {
			ui->UnitBox->setCurrentIndex(index);
		}
		ui->UnitNumberBox->setValue(curTaskforce->taskforceLines[ui->UnitList->currentRow()]->amount);

	}
}

void TaskforceSection::on_UnitBox_activated()
{
	if(ui->TaskforceList->selectedItems().size() != 0 && ui->UnitList->currentRow() != -1 && ui->UnitBox->currentIndex() != -1) {
		for(int a = 0; a != ui->TaskforceList->selectedItems().size(); ++a) {
			Taskforce *curTaskforce = getTaskforceByName(ui->TaskforceList->selectedItems().at(a)->text());
			uint32_t rowNum = ui->UnitList->currentRow();
			if(curTaskforce->getLineAmount() >= rowNum+1) {
				QString newType = ui->UnitBox->currentText();
				curTaskforce->taskforceLines[rowNum]->type = newType.mid(1, newType.indexOf("]")-1);
				ui->UnitList->currentItem()->setText(QString(QString::number(curTaskforce->taskforceLines[rowNum]->amount) + " " + getUnitNameByUnitID(curTaskforce->taskforceLines[rowNum]->type)));
			}
		}
	}
}

void TaskforceSection::on_UnitNumberBox_editingFinished()
{
	if(ui->TaskforceList->selectedItems().size() != 0 && ui->UnitList->currentRow() != -1) {
		for(int a = 0; a != ui->TaskforceList->selectedItems().size(); ++a) {
			Taskforce *curTaskforce = getTaskforceByName(ui->TaskforceList->selectedItems().at(a)->text());
			uint32_t rowNum = ui->UnitList->currentRow();
			if(curTaskforce->getLineAmount() >= rowNum+1) {
				curTaskforce->taskforceLines[rowNum]->amount = ui->UnitNumberBox->value();
				ui->UnitList->currentItem()->setText(QString(QString::number(curTaskforce->taskforceLines[rowNum]->amount) + " " + getUnitNameByUnitID(curTaskforce->taskforceLines[rowNum]->type)));
			}
		}
	}
}

void TaskforceSection::on_AddUnit_clicked()
{
	if(ui->TaskforceList->selectedItems().size() != 0) {
		for(int a = 0; a != ui->TaskforceList->selectedItems().size(); ++a) {
			Taskforce *curTaskforce = getTaskforceByName(ui->TaskforceList->selectedItems().at(a)->text());
			curTaskforce->addLine("APACHE", 0);
		}
		QString ID;
		Taskforce *curTaskforce = getTaskforceByName(ui->TaskforceList->selectedItems().last()->text());
		ID = QString::number((*(curTaskforce->taskforceLines.end()-1))->amount) + " " + getUnitNameByUnitID((*(curTaskforce->taskforceLines.end()-1))->type);
		ui->UnitList->addItem(ID);
	}
}

void TaskforceSection::on_DeleteUnit_clicked()
{
	if(ui->UnitList->currentRow() != -1) {
		uint32_t rowNum = ui->UnitList->currentRow();
		delete ui->UnitList->item(rowNum);
		for(int a = 0; a != ui->TaskforceList->selectedItems().size(); ++a) {
			Taskforce *curTaskforce = getTaskforceByName(ui->TaskforceList->selectedItems().at(a)->text());
			if(curTaskforce->getLineAmount() >= rowNum) {
				curTaskforce->deleteLine(rowNum);
			}
		}
		Taskforce *curTaskforce = getTaskforceByName(ui->TaskforceList->selectedItems().last()->text());
		ui->UnitList->clear();
		for(std::vector <Taskforce::TaskforceLine*>::iterator taskforceLineIT = curTaskforce->taskforceLines.begin(); taskforceLineIT != curTaskforce->taskforceLines.end(); ++taskforceLineIT) {
			ui->UnitList->addItem(QString(QString::number((*taskforceLineIT)->amount) + " " + getUnitNameByUnitID((*taskforceLineIT)->type)));
		}
	}

}

void TaskforceSection::mousePressEvent(QMouseEvent *event)
{
	event->accept();
}

void TaskforceSection::updateUi()
{
	ui->TaskforceList->clearSelection();
	ui->TaskforceList->clear();
	ui->UnitBox->clear();
	for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		ui->TaskforceList->addItem(IT->second->getName());
	}
	for(unitIT IT = aircraft.begin(); IT != aircraft.end(); ++IT) {
		ui->UnitBox->addItem("[" + IT->first + "] " + IT->second.name);
	}
	for(unitIT IT = infantry.begin(); IT != infantry.end(); ++IT) {
		ui->UnitBox->addItem("[" + IT->first + "] " + IT->second.name);
	}
	for(unitIT IT = vehicles.begin(); IT != vehicles.end(); ++IT) {
		ui->UnitBox->addItem("[" + IT->first + "] " + IT->second.name);
	}
	ui->UnitBox->view()->setMinimumWidth(220);
}
