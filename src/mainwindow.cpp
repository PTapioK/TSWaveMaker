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
	connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(settingsDialog()));
	// Connect info menu
	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(infoDialog()));

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
	settings.setValue("lastUsedPath", lastUsedPath);
	settings.sync();

	delete ui;
}

void MainWindow::newFile()
{
	this->setWindowTitle(CAPTIONBASE);

	clearContainers();

	parseRules();

	triggerSct->updateUi();
	teamSct->updateUi();
	scriptSct->updateUi();
	taskforceSct->updateUi();
}

void MainWindow::openFile()
{
	QFileDialog fDG(this);

	currentFilePath = fDG.getOpenFileName(this, tr("Open Tiberian Sun map or text file"), lastUsedPath, tr("Compatible Files (*.map *.mpr *.txt)"));

	if(currentFilePath.isEmpty()) {
		return;
	}

	newFile();

	readFileToBuffer();
	parseSections();

	triggerSct->updateUi();
	teamSct->updateUi();
	scriptSct->updateUi();
	taskforceSct->updateUi();

	this->setWindowTitle(CAPTIONBASE + tr(" | ") + currentFilePath);
	lastUsedPath = QFileInfo(currentFilePath).path();
}

void MainWindow::saveFile()
{
	if(currentFilePath.isEmpty()) {
		saveFileAs();
		return;
	}
	currentFileData.SetFileName(currentFilePath.toStdString());
	saveAllToBuffer();
	currentFileData.Save();
}

void MainWindow::saveFileAs()
{
	QFileDialog fDG(this);
	currentFilePath = fDG.getSaveFileName(this, tr("Save Tiberian Sun map or text file"), lastUsedPath, tr("Compatible Files (*.map *.mpr *.txt)"));
	if(currentFilePath.isEmpty()) {
		return;
	}
	saveFile();
	this->setWindowTitle(CAPTIONBASE + tr(" | ") + currentFilePath);
	lastUsedPath = QFileInfo(currentFilePath).path();
}

void MainWindow::infoDialog()
{
	InfoDialog * dialog = new InfoDialog;
	dialog->show();
}

void MainWindow::settingsDialog()
{
	SettingsDialog * dialog = new SettingsDialog;
	dialog->show();
}

