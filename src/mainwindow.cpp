#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connect(ui->actionNew_file, SIGNAL(triggered()), this, SLOT(NewFile()));
	connect(ui->actionOpen_file, SIGNAL(triggered()), this, SLOT(OpenFile()));
	connect(ui->actionSave_file, SIGNAL(triggered()), this, SLOT(SaveFile()));
	connect(ui->actionSave_As, SIGNAL(triggered()), this, SLOT(SaveFileAs()));

	connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));

	connect(ui->actionInfo, SIGNAL(triggered()), this, SLOT(Info()));

}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::NewFile() {
	clearTriggerList();
	clearActionList();
}

void MainWindow::OpenFile() {
	QFileDialog fDG(this);

	cur_file = fDG.getOpenFileName(this, tr("Open Tiberian Sun Map Or AttackWaveFile"), ".", tr("Compatible Files (*.map *.mpr *.awf)")).toStdString();

	triggers.clear();
	tags.clear();
	teams.clear();
	clearTriggerList();

	ParseBuffer();

	for(triggerIT = triggers.begin(); triggerIT != triggers.end(); ++triggerIT) {
		ui->listWidget->addItem(QString((*triggerIT).first.c_str()));
	}

}

void MainWindow::SaveFile() {
	if(cur_file.empty()) {
		SaveFileAs();
		return;
	}
	SaveAllToFile();
}

void MainWindow::SaveFileAs() {
	QFileDialog fDG(this);
	cur_file = fDG.getSaveFileName(this, tr("Save Tiberian Sun Map Or AttackWaveFile"), ".", tr("Compatible Files (*.map *.mpr *.awf)")).toStdString();
	SaveFile();
}

void MainWindow::Info() {
	InfoDialog * dlg = new InfoDialog;
	dlg->show();
}

void MainWindow::on_listWidget_itemSelectionChanged()
{
	ui->label_8->setText("Not set");
	ui->timeEdit->setTime(QTime(0, 0, 0));

	clearActionList();
	if(ui->listWidget->currentRow() != -1) {
		string trig_name = ui->listWidget->currentItem()->text().toStdString();
		Trigger *cur_trig = triggers[trig_name];
		ui->lineEdit->setText(ui->listWidget->currentItem()->text());
		ui->checkBox->setChecked(cur_trig->isDis());

		if(!isFirstWave(cur_trig->getID())) {
			triggerIT = triggers.find(trig_name);
			--triggerIT;
			Trigger *prev_trig = (*triggerIT).second;
			if(prev_trig->hasActionType(27)) {
				int32_t secs = atoi(prev_trig->getActionByType(27)->p2.c_str());
				QTime time(0, 0, 0);
				time = time.addSecs(secs);
				ui->timeEdit->setTime(time);
				ui->label_8->setText("Set");
			}
		}

		int i = 0;
		for(actionIT = cur_trig->actions.begin(); actionIT != cur_trig->actions.end(); ++actionIT) {
			++i;
			stringstream iSS;
			iSS << i;
			QString text = "Action ";
			text += iSS.str().c_str();

			ui->listWidget_2->addItem(text);
		}

	} else {
		ui->lineEdit->setText("");
	}

	ui->comboBox_2->clear();
	ui->comboBox_3->clear();
	for(waypointIT = waypoints.begin(); waypointIT != waypoints.end(); ++waypointIT) {
		stringstream wSS;
		wSS << (*waypointIT);
		ui->comboBox_2->addItem(wSS.str().c_str());
		ui->comboBox_3->addItem(wSS.str().c_str());
	}

}

// New trigger
void MainWindow::on_pushButton_clicked()
{
	if(ui->listWidget->findItems(ui->lineEdit->text(), Qt::MatchExactly).count() == 0) {
		string name = ui->lineEdit->text().toStdString();
		ui->listWidget->addItem(ui->lineEdit->text());
		triggers[name] = new Trigger(name);
		tags[name + " 1"] = new Tag(name + " 1", triggers[name]->getID());
	}
}

// Edit trigger name
void MainWindow::on_pushButton_2_clicked()
{
	if(ui->listWidget->findItems(ui->lineEdit->text(), Qt::MatchExactly).count() == 0) {
		string cur_name = ui->listWidget->currentItem()->text().toStdString();
		triggers[cur_name]->setName(ui->lineEdit->text().toStdString());

		map <string, Trigger*> tempMap;
		for(triggerIT = triggers.begin(); triggerIT != triggers.end(); ++triggerIT) {
			if((*triggerIT).first == cur_name) {
				tempMap[ui->lineEdit->text().toStdString()] = (*triggerIT).second;
			} else {
				tempMap[(*triggerIT).first] = (*triggerIT).second;
			}
		}

		triggers.swap(tempMap);

		ui->listWidget->currentItem()->setText(ui->lineEdit->text());
	}
}

// Is disabled
void MainWindow::on_checkBox_clicked()
{
	triggers[ui->listWidget->currentItem()->text().toStdString()]->setDis(ui->checkBox->isChecked());
}

// Delete trigger
void MainWindow::on_pushButton_4_clicked()
{
	if(ui->listWidget->currentRow() != -1) {
		string name = ui->listWidget->currentItem()->text().toStdString();
		delete triggers[name];
		triggers.erase(name);
		delete tags[name + " 1"];
		tags.erase(name + " 1");

		delete ui->listWidget->item(ui->listWidget->currentRow());
	}

}

// Clone trigger
void MainWindow::on_pushButton_3_clicked()
{
	if(ui->listWidget->currentRow() != -1) {
		string newName = "Clone Of " + ui->listWidget->currentItem()->text().toStdString();

		int i = 0;
		while(ui->listWidget->findItems(newName.c_str(), Qt::MatchExactly).count() != 0) {
			++i;
			stringstream ssI;
			ssI << i;
			newName = "Clone Of " + ui->listWidget->currentItem()->text().toStdString() + " " + ssI.str();
		}
		triggers[newName] = new Trigger(triggers[ui->listWidget->currentItem()->text().toStdString()]);
		triggers[newName]->setName(newName);
		ui->listWidget->addItem(newName.c_str());
		Tag *cTag = FindTag(triggers[ui->listWidget->currentItem()->text().toStdString()]->getID());
		tags[newName + " 1"] = new Tag(cTag, triggers[newName]->getID());
		tags[newName + " 1"]->setName(newName + " 1");
	}

}

void MainWindow::on_timeEdit_editingFinished()
{
	if(ui->listWidget->currentRow() != -1) {
		string trig_name = ui->listWidget->currentItem()->text().toStdString();
		int32_t secs = 0;
		secs = abs(ui->timeEdit->time().secsTo(QTime(0, 0)));
		if(isFirstWave(triggers[trig_name]->getID())) {

			if(triggers["TimerFor1stWave"] == NULL) {

				triggers["TimerFor1stWave"] = new Trigger("01000000", "Neutral", "<none>", "TimerFor1stWave", false, true, true, true);
				tags["TimerFor1stWave 1"] = new Tag("TimerFor1stWave 1", triggers["TimerFor1stWave"]->getID());
				tags["TimerFor1stWave 1"]->setID("01000001");
				Event *nEvent = new Event(8, 0, triggers["TimerFor1stWave"]->getID());
				triggers["TimerFor1stWave"]->addEvent(nEvent);
				Action *nAction = new Action(triggers["TimerFor1stWave"]->getID(), 27, 0, 0, secs, 0, 0, 0, 0);
				triggers["TimerFor1stWave"]->addAction(nAction);

				ui->listWidget->addItem("TimerFor1stWave");
				ui->label_8->setText("Set");

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

			ui->label_8->setText("Set");
		}
	}

}

// New action
void MainWindow::on_pushButton_5_clicked()
{
	if(ui->listWidget->currentRow() != -1) {
		Trigger *cur_trig = triggers[ui->listWidget->currentItem()->text().toStdString()];

		int32_t lastWPoint = 0;
		if(!cur_trig->actions.empty())
			lastWPoint = (*(cur_trig->actions.end()-1))->getWaypoint();
		int32_t nextWPoint = 0;

		if(ui->checkBox_2->isChecked()) {
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

		ui->listWidget_2->clear();
		int i = 0;
		for(actionIT = cur_trig->actions.begin(); actionIT != cur_trig->actions.end(); ++actionIT) {
			++i;
			stringstream iSS;
			iSS << i;
			QString text = "Action ";
			text += iSS.str().c_str();

			ui->listWidget_2->addItem(text);
		}
	}
}

// Delete action
void MainWindow::on_pushButton_6_clicked()
{
	if(ui->listWidget_2->currentRow() != -1) {
		Trigger *cur_trig = triggers[ui->listWidget->currentItem()->text().toStdString()];
		cur_trig->eraseAction(ui->listWidget_2->currentRow());

		clearActionList();
		int i = 0;
		for(actionIT = cur_trig->actions.begin(); actionIT != cur_trig->actions.end(); ++actionIT) {
			++i;
			stringstream iSS;
			iSS << i;
			QString text = "Action ";
			text += iSS.str().c_str();

			ui->listWidget_2->addItem(text);
		}
	}
}

// Clone action
void MainWindow::on_pushButton_7_clicked()
{
	if(ui->listWidget_2->currentRow() != -1) {
		int i = 1;
		Trigger *cur_trig = triggers[ui->listWidget->currentItem()->text().toStdString()];
		for(actionIT = cur_trig->actions.begin(); actionIT != cur_trig->actions.end(); ++actionIT) {
			++i;
		}

		Action *nAct = new Action(cur_trig->getAction(ui->listWidget_2->currentRow()), cur_trig->getID());
		cur_trig->addAction(nAct);

		stringstream iSS;
		iSS << i;
		QString text = "Action ";
		text += iSS.str().c_str();

		ui->listWidget_2->addItem(text);
	}
}

void MainWindow::on_listWidget_2_itemClicked()
{
	ui->comboBox->clear();
	for(teamIT = teams.begin(); teamIT != teams.end(); ++teamIT) {
		ui->comboBox->addItem((*teamIT).first.c_str());
		ui->checkBox_4->setEnabled(true);
	}
	if(ui->listWidget_2->currentRow() != -1) {
		Trigger *cTrig = triggers[ui->listWidget->currentItem()->text().toStdString()];
		Action *cAct = cTrig->getAction(ui->listWidget_2->currentRow());
		if(cAct->getType() == 80) {
			ui->checkBox_5->setChecked(true);
			qDebug() << cAct->getP2().c_str();
			qDebug() << ui->comboBox->findText(cAct->getP2().c_str());
			ui->comboBox->setCurrentIndex(ui->comboBox->findText(cAct->getP2().c_str()));
		} else {
			ui->checkBox_5->setChecked(false);
		}
		stringstream wSS;
		wSS << cAct->getWaypoint();
		ui->comboBox_2->setEditText(wSS.str().c_str());
	} else {
		ui->checkBox_5->setChecked(false);
		ui->checkBox_2->setChecked(false);
	}
}

// Is "reinforcement at waypoint" - action
void MainWindow::on_checkBox_5_stateChanged()
{
	if(ui->listWidget_2->currentRow() != -1) {
		Trigger *cTrig = triggers[ui->listWidget->currentItem()->text().toStdString()];
		if(ui->checkBox_5->isChecked()) {
			cTrig->getAction(ui->listWidget_2->currentRow())->editType(80);
			ui->comboBox->setEnabled(true);
		} else {
			cTrig->getAction(ui->listWidget_2->currentRow())->editType(0);
			ui->checkBox_4->setEnabled(false);
		}
	}
}

// Action waypoint
void MainWindow::on_comboBox_2_currentIndexChanged()
{
	if(ui->listWidget_2->currentItem() != NULL) {
		Trigger *cTrig = triggers[ui->listWidget->currentItem()->text().toStdString()];
		cTrig->getAction(ui->listWidget_2->currentRow())->editWPoint(atoi(ui->comboBox_2->currentText().toStdString().c_str()));
	}
}

void MainWindow::clearTriggerList() {
	delete ui->listWidget->item(ui->listWidget->currentRow());
	ui->listWidget->clear();
}

void MainWindow::clearActionList() {
	delete ui->listWidget_2->item(ui->listWidget_2->currentRow());
	ui->listWidget_2->clear();
}

// Make waypoints grow in ascending order to all actions
void MainWindow::on_checkBox_2_clicked()
{
	if(ui->listWidget->currentRow() != -1) {
		if(ui->checkBox_2->isChecked()) {

			Trigger *cur_trig = triggers[ui->listWidget->currentItem()->text().toStdString()];

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

			for(actionIT = cur_trig->actions.begin(); actionIT != cur_trig->actions.end(); ++actionIT) {
				Action *cur_act = (*actionIT);
				if(i == waypoints.size()) { i = j; }
				cur_act->editWPoint((*(waypoints.begin()+i)));
				++i;
			}

			ui->comboBox_3->setEnabled(true);

		} else {
			ui->comboBox_3->setEnabled(false);
		}
	}
}

// Starting waypoint to "Make waypoints grow in ascending order to all actions"
void MainWindow::on_comboBox_3_currentIndexChanged()
{
	sWPoint = atoi(ui->comboBox_3->currentText().toStdString().c_str());
	on_checkBox_2_clicked();
}

// TeamType for trigger
void MainWindow::on_comboBox_activated()
{
	if(ui->listWidget_2->currentRow() != -1) {
		Trigger *cur_trig = triggers[ui->listWidget->currentItem()->text().toStdString()];
		cur_trig->getAction(ui->listWidget_2->currentRow())->editP1(1);
		cur_trig->getAction(ui->listWidget_2->currentRow())->editP2(ui->comboBox->currentText().toStdString());
	}
	if(ui->checkBox_4->isChecked()) { on_checkBox_4_stateChanged(); }
}

// Same team for all actions
void MainWindow::on_checkBox_4_stateChanged()
{
	if(ui->listWidget->currentRow() != -1) {
		Trigger *cur_trig = triggers[ui->listWidget->currentItem()->text().toStdString()];
		for(actionIT = cur_trig->actions.begin(); actionIT != cur_trig->actions.end(); ++actionIT) {
			Action *cur_act = (*actionIT);
			cur_act->editP1(1);
			cur_act->editP2(ui->comboBox->currentText().toStdString());
		}
	}
}

