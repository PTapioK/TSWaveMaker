#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	LoadSettings();

	ui->setupUi(this);

	connect(ui->actionNew_file, SIGNAL(triggered()), this, SLOT(NewFile()));
	connect(ui->actionOpen_file, SIGNAL(triggered()), this, SLOT(OpenFile()));
	connect(ui->actionSave_file, SIGNAL(triggered()), this, SLOT(SaveFile()));
	connect(ui->actionSave_As, SIGNAL(triggered()), this, SLOT(SaveFileAs()));

	connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));

	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(Info()));
	connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(Settings()));

	trgS = new TriggerSection(this);
	tamS = new TeamSection(this);
	srtS = new ScriptSection(this);
	tskS = new TaskforceSection(this);

	addDockWidget(Qt::LeftDockWidgetArea, trgS);
	addDockWidget(Qt::RightDockWidgetArea, tamS);
	addDockWidget(Qt::BottomDockWidgetArea, srtS);
	addDockWidget(Qt::BottomDockWidgetArea, tskS);

	trgS->setFloating(false);
	tamS->setFloating(false);
	srtS->setFloating(false);
	tskS->setFloating(false);

	NewFile();
}

MainWindow::~MainWindow()
{
	settings_data.SetValue("last_path", last_path);
	settings_data.Save();
	delete ui;
}

void MainWindow::NewFile() {
	this->setWindowTitle(CAPTIONBASE);

	ClearContainers();

	ParseRules();

	trgS->UpdateUi();
	tamS->UpdateUi();
	srtS->UpdateUi();
	tskS->UpdateUi();
}

void MainWindow::OpenFile() {
	QFileDialog fDG(this);

	cur_file = fDG.getOpenFileName(this, tr("Open Tiberian Sun map or text file"), last_path.c_str(), tr("Compatible Files (*.map *.mpr *.txt)")).toStdString();

	if(cur_file.empty()) {
		return;
	}

	NewFile();

	ReadFileToBuffer();
	ParseSections();

	trgS->UpdateUi();
	tamS->UpdateUi();
	srtS->UpdateUi();
	tskS->UpdateUi();

	this->setWindowTitle(CAPTIONBASE + tr(" | ") + cur_file.c_str());
	last_path = QFileInfo(cur_file.c_str()).path().toStdString();
}

void MainWindow::SaveFile() {
	if(cur_file.empty()) {
		SaveFileAs();
		return;
	}
	curdata.SetFileName(cur_file);
	SaveAllToBuffer();
	curdata.Save();
}

void MainWindow::SaveFileAs() {
	QFileDialog fDG(this);
	cur_file = fDG.getSaveFileName(this, tr("Save Tiberian Sun map or text file"), last_path.c_str(), tr("Compatible Files (*.map *.mpr *.txt)")).toStdString();
	if(cur_file.empty()) {
		return;
	}
	SaveFile();
	this->setWindowTitle(CAPTIONBASE + tr(" | ") + cur_file.c_str());
	last_path = QFileInfo(cur_file.c_str()).path().toStdString();
}

void MainWindow::Info() {
	InfoDialog * dlg = new InfoDialog;
	dlg->show();
}

void MainWindow::Settings()
{
	SettingsDialog * dlg = new SettingsDialog;
	dlg->show();
}

