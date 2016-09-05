#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	Settings::loadSettings();

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
	Settings::settings.setValue("lastUsedPath", Settings::lastUsedPath);
	Settings::settings.sync();

	delete ui;
}

void MainWindow::newFile()
{
	this->setWindowTitle(CAPTIONBASE);

	file.clear();
	clearContainers();
	file.parseRules();

	triggerSct->updateUi();
	teamSct->updateUi();
	scriptSct->updateUi();
	taskforceSct->updateUi();
}

void MainWindow::openFile()
{
	QFileDialog fDG(this);
	QString newFilePath;

	newFilePath = fDG.getOpenFileName(this, tr("Open Tiberian Sun map or text file"), Settings::lastUsedPath, tr("Compatible Files (*.map *.mpr *.txt)"));

	if(newFilePath.isEmpty()) {
		return;
	}

	newFile();
	file.load(newFilePath);

	triggerSct->updateUi();
	teamSct->updateUi();
	scriptSct->updateUi();
	taskforceSct->updateUi();

	this->setWindowTitle(CAPTIONBASE + tr(" | ") + newFilePath);
	Settings::lastUsedPath = QFileInfo(newFilePath).path();
}

void MainWindow::saveFile()
{
	if(file.getFilePath().isEmpty()) {
		saveFileAs();
		return;
	}
	file.save();
}

void MainWindow::saveFileAs()
{
	QFileDialog fDG(this);
	QString filePath;

	filePath = fDG.getSaveFileName(this, tr("Save Tiberian Sun map or text file"), Settings::lastUsedPath, tr("Compatible Files (*.map *.mpr *.txt)"));
	if(filePath.isEmpty()) {
		return;
	}

	file.save(filePath);
	this->setWindowTitle(CAPTIONBASE + tr(" | ") + filePath);
	Settings::lastUsedPath = QFileInfo(filePath).path();
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

