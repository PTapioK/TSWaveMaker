#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "main.h"

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

	Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
