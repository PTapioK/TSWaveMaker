#include "triggersection.h"
#include "ui_triggersection.h"

TriggerSection::TriggerSection(QWidget *parent) :
	QDockWidget(parent),
	ui(new Ui::TriggerSection)
{
	ui->setupUi(this);

	ui->isOtherAction->setVisible(false);
}

TriggerSection::~TriggerSection()
{
	delete ui;
}

void TriggerSection::on_TriggerList_itemSelectionChanged()
{
	ui->WaveTimer->setTime(QTime(0, 0, 0));
	ui->ActionList->clear();

	if(ui->TriggerList->currentRow() != -1) {
		QString trig_name = ui->TriggerList->currentItem()->text();
		Trigger *curTrig = getTriggerByName(trig_name);
		if(curTrig == NULL) {
			if(QMessageBox::question(this, "Fatal Error!", "Fatal Error occured! Continue?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::No) {
				exit(EXIT_FAILURE);
			}
		}

		ui->NEdit->setText(ui->TriggerList->currentItem()->text());
		ui->isDisabledCheck->setChecked(curTrig->isDisabled());

		if(curTrig->hasActionType(27)) {
			int32_t secs = curTrig->getActionByType(27)->getParameter(2).toInt();
			QTime time(0, 0, 0);
			time = time.addSecs(secs);
			ui->WaveTimer->setTime(time);
		}

		int i = 0;
		for(actionIT IT = curTrig->actions.begin(); IT != curTrig->actions.end(); ++IT) {
			++i;
			QString str;
			QTextStream iSS(&str);
			iSS << i;
			QString text = "Action ";
			text += iSS.readAll();

			ui->ActionList->addItem(text);
		}

	} else {
		ui->NEdit->setText("");
	}
}

// New trigger
void TriggerSection::on_NewTrigger_clicked()
{
	if(ui->TriggerList->findItems(ui->NEdit->text(), Qt::MatchExactly).count() == 0) {
		QString name = ui->NEdit->text();
		ui->TriggerList->addItem(ui->NEdit->text());
		QString nID = findFirstFreeID();
		triggers[nID] = new Trigger(nID, name);
		tags[name + " 1"] = new Tag(name + " 1", triggers[nID]->getID());
	}
}

// Edit trigger's name
void TriggerSection::on_EditTriggerName_clicked()
{
	if(ui->TriggerList->currentRow() != -1) {
		if(ui->TriggerList->findItems(ui->NEdit->text(), Qt::MatchExactly).count() == 0) {
			QString curName = ui->TriggerList->currentItem()->text();
			QString curID = getTriggerIDByName(curName);

			triggers[curID]->setName(ui->NEdit->text());
			getTagByTriggerID(curID)->setName(ui->NEdit->text() + " 1");

			ui->TriggerList->currentItem()->setText(ui->NEdit->text());
		}
	}
}

// Disable trigger checkbox
void TriggerSection::on_isDisabledCheck_clicked()
{
	if(ui->TriggerList->currentRow() != -1) {
		getTriggerByName(ui->TriggerList->currentItem()->text())->setDis(ui->isDisabledCheck->isChecked());
	}
}

// Delete trigger
void TriggerSection::on_DeleteTrigger_clicked()
{
	if(ui->TriggerList->currentRow() != -1) {
		QString name = ui->TriggerList->currentItem()->text();
		QString ID = getTriggerIDByName(name);
		delete getTriggerByName(name);
		triggers.erase(ID);
		QString tagName = getTagByTriggerID(ID)->getName();
		delete getTagByTriggerID(ID);
		tags.erase(tagName);

		delete ui->TriggerList->item(ui->TriggerList->currentRow());
	}
}

// Clone trigger
void TriggerSection::on_CloneTrigger_clicked()
{
	if(ui->TriggerList->currentRow() != -1) {
		QString newName = getNameWithNextMark(ui->TriggerList->currentItem()->text());

		int i = 0;
		while(ui->TriggerList->findItems(newName, Qt::MatchExactly).count() != 0) {
			++i;
			newName = getNameWithNextMark(ui->TriggerList->currentItem()->text(), i);
		}

		QString newID = findFirstFreeID();
		triggers[newID] = new Trigger(newID, getTriggerByName(ui->TriggerList->currentItem()->text()));
		triggers[newID]->setName(newName);
		ui->TriggerList->addItem(newName);
		Tag *cTag = getTagByTriggerID(getTriggerByName(ui->TriggerList->currentItem()->text())->getID());
		tags[newName + " 1"] = new Tag(cTag, triggers[newID]->getID());
		tags[newName + " 1"]->setName(newName + " 1");
	}
}

void TriggerSection::on_WaveTimer_editingFinished()
{
	if(ui->TriggerList->currentRow() != -1) {
		QString trig_name = ui->TriggerList->currentItem()->text();
		int32_t secs = 0;
		secs = abs(ui->WaveTimer->time().secsTo(QTime(0, 0, 0)));

		Trigger *curTrig = getTriggerByName(trig_name);

		if(!curTrig->hasActionType(27)) {
			Action *nAction = new Action(curTrig->getID(), 27, 0, "0", QString::number(secs), "0", "0", "0", "0");
			curTrig->addAction(nAction);
		} else {
			curTrig->getActionByType(27)->setParameter(2, secs);
		}

		ui->ActionList->clear();
		int i = 0;
		for(actionIT IT = curTrig->actions.begin(); IT != curTrig->actions.end(); ++IT) {
			++i;
			QString text = "Action ";
			text += QString::number(i);

			ui->ActionList->addItem(text);
		}

	}
}

// New action
void TriggerSection::on_NewAction_clicked()
{
	if(ui->TriggerList->currentRow() != -1) {
		Trigger *curTrig = getTriggerByName(ui->TriggerList->currentItem()->text());

		Action *nAction = new Action(curTrig->getID());
		curTrig->addAction(nAction);

		ui->ActionList->clear();
		int i = 0;
		for(actionIT IT = curTrig->actions.begin(); IT != curTrig->actions.end(); ++IT) {
			++i;
			QString text = "Action ";
			text += QString::number(i);

			ui->ActionList->addItem(text);
		}
	}
}

// Delete action
void TriggerSection::on_DeleteAction_clicked()
{
	if(ui->ActionList->currentRow() != -1) {
		Trigger *curTrig = getTriggerByName(ui->TriggerList->currentItem()->text());

		for(int i = ui->ActionList->selectedItems().size()-1; i != -1; --i) {
			curTrig->eraseAction(ui->ActionList->row(ui->ActionList->selectedItems().at(i)));
		}

		clearActionList();
		int i = 0;
		for(actionIT IT = curTrig->actions.begin(); IT != curTrig->actions.end(); ++IT) {
			++i;
			QString text = "Action ";
			text += QString::number(i);

			ui->ActionList->addItem(text);
		}
	}
}

// Clone action
void TriggerSection::on_CloneAction_clicked()
{
	if(ui->ActionList->currentRow() != -1) {
		int i = 1;
		Trigger *curTrig = getTriggerByName(ui->TriggerList->currentItem()->text());
		for(actionIT IT = curTrig->actions.begin(); IT != curTrig->actions.end(); ++IT) {
			++i;
		}

		for(int a = 0; a != ui->ActionList->selectedItems().size(); ++a) {
			Action *nAct = new Action(curTrig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().at(a))), curTrig->getID());
			curTrig->addAction(nAct);

			QString text = "Action ";
			text += QString::number(i);

			ui->ActionList->addItem(text);

			++i;
		}
	}
}

void TriggerSection::on_ActionList_itemSelectionChanged()
{
	ui->isOtherAction->setEnabled(true);
	if(ui->ActionList->selectedItems().size() != 0 && ui->TriggerList->currentRow() != -1) {
		Trigger *curTrig = getTriggerByName(ui->TriggerList->currentItem()->text());
		Action *curAct = curTrig->getAction(ui->ActionList->row(ui->ActionList->selectedItems().last()));
	}
}

void TriggerSection::mousePressEvent(QMouseEvent *event)
{
	event->accept();
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

void TriggerSection::updateUi()
{
	ui->TriggerList->setCurrentRow(-1);
	ui->ActionList->setCurrentRow(-1);
	ui->TriggerList->clear();
	for(triggerIT IT = triggers.begin(); IT != triggers.end(); ++IT) {
		ui->TriggerList->addItem(IT->second->getName());
	}
}
