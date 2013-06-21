#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "main.h"
#include "triggersection.h"
#include "teamsection.h"
#include "scriptsection.h"
#include "taskforcesection.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void NewFile();
	void OpenFile();
	void SaveFile();
	void SaveFileAs();

	void Info();

private:

	friend class TriggerSection;
	friend class TeamSection;
	friend class ScriptSection;
	friend class TaskforceSection;

	Ui::MainWindow *ui;

	TriggerSection * trgS;
	TeamSection * tamS;
	ScriptSection * srtS;
	TaskforceSection * tskS;

};

#endif // MAINWINDOW_H
