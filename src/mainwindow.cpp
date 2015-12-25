#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	loadSettings();

	ui->setupUi(this);

	// Connect file menu
	connect(ui->actionNewFile, SIGNAL(triggered()), this, SLOT(newFile()));
	connect(ui->actionOpenFile, SIGNAL(triggered()), this, SLOT(openFile()));
	connect(ui->actionSaveFile, SIGNAL(triggered()), this, SLOT(saveFile()));
	connect(ui->actionSaveFileAs, SIGNAL(triggered()), this, SLOT(saveFileAs()));
	connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
	// Connect edit menu
	connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(settings()));
	// Connect info menu
	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(info()));

	triggerSct		= new TriggerSection(this);
	teamSct			= new TeamSection(this);
	scriptSct		= new ScriptSection(this);
	taskforceSct	= new TaskforceSection(this);

	addDockWidget(Qt::LeftDockWidgetArea, triggerSct);
	addDockWidget(Qt::RightDockWidgetArea, teamSct);
	addDockWidget(Qt::BottomDockWidgetArea, scriptSct);
	addDockWidget(Qt::BottomDockWidgetArea, taskforceSct);

	newFile();
}

MainWindow::~MainWindow()
{
	// Save settings before quitting
	settingsFileData.SetValue("lastUsedPath", lastUsedPath);
	settingsFileData.Save();

	delete ui;
}

void MainWindow::newFile() {
	this->setWindowTitle(CAPTIONBASE);

	clearContainers();

	parseRules();

	triggerSct->UpdateUi();
	teamSct->updateUi();
	scriptSct->UpdateUi();
	taskforceSct->updateUi();
}

void MainWindow::openFile() {
	QFileDialog fDG(this);

	currentFilePath = fDG.getOpenFileName(this, tr("Open Tiberian Sun map or text file"), lastUsedPath.c_str(), tr("Compatible Files (*.map *.mpr *.txt)")).toStdString();

	if(currentFilePath.empty()) {
		return;
	}

	newFile();

	readFileToBuffer();
	parseSections();

	triggerSct->UpdateUi();
	teamSct->updateUi();
	scriptSct->UpdateUi();
	taskforceSct->updateUi();

	this->setWindowTitle(CAPTIONBASE + tr(" | ") + currentFilePath.c_str());
	lastUsedPath = QFileInfo(currentFilePath.c_str()).path().toStdString();
}

void MainWindow::saveFile() {
	if(currentFilePath.empty()) {
		saveFileAs();
		return;
	}
	currentFileData.SetFileName(currentFilePath);
	saveAllToBuffer();
	currentFileData.Save();
}

void MainWindow::saveFileAs() {
	QFileDialog fDG(this);
	currentFilePath = fDG.getSaveFileName(this, tr("Save Tiberian Sun map or text file"), lastUsedPath.c_str(), tr("Compatible Files (*.map *.mpr *.txt)")).toStdString();
	if(currentFilePath.empty()) {
		return;
	}
	saveFile();
	this->setWindowTitle(CAPTIONBASE + tr(" | ") + currentFilePath.c_str());
	lastUsedPath = QFileInfo(currentFilePath.c_str()).path().toStdString();
}

void MainWindow::info() {
	InfoDialog * dialog = new InfoDialog;
	dialog->show();
}

void MainWindow::settings()
{
	SettingsDialog * dialog = new SettingsDialog;
	dialog->show();
}

