#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "triggersection.h"
#include "teamsection.h"

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

	trgS = new TriggerSection(this);
	tamS = new TeamSection(this);
	srtS = new ScriptSection(this);
	tskS = new TaskforceSection(this);

}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::NewFile() {
	triggers.clear();
	tags.clear();
	teams.clear();
	taskforces.clear();
}

void MainWindow::OpenFile() {
	QFileDialog fDG(this);

	cur_file = fDG.getOpenFileName(this, tr("Open File"), ".", tr("Compatible Files (*.map *.mpr *.txt)")).toStdString();

	if(cur_file.empty()) {
		return;
	}

	NewFile();

	ParseBuffer();

	trgS->UpdateUi();
	tamS->UpdateUi();
	srtS->UpdateUi();
	tskS->UpdateUi();

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
	if(cur_file.empty()) {
		return;
	}
	SaveFile();
}

void MainWindow::Info() {
	InfoDialog * dlg = new InfoDialog;
	dlg->show();
}

