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
		void newFile();
		void openFile();
		void saveFile();
		void saveFileAs();

		void infoDialog();
		void settingsDialog();
	private:
		Ui::MainWindow *ui;

		TriggerSection * triggerSct;
		TeamSection * teamSct;
		ScriptSection * scriptSct;
		TaskforceSection * taskforceSct;

};

#endif // MAINWINDOW_H
