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

	void on_listWidget_itemSelectionChanged();

	void on_pushButton_clicked();

	void on_pushButton_2_clicked();

	void on_checkBox_clicked();

	void on_pushButton_4_clicked();

	void on_pushButton_3_clicked();

	void on_timeEdit_editingFinished();

	void on_pushButton_5_clicked();

	void on_pushButton_6_clicked();

	void on_pushButton_7_clicked();

	void on_listWidget_2_itemClicked();

	void on_checkBox_5_stateChanged();

	void on_comboBox_2_currentIndexChanged();

	void on_checkBox_2_clicked();

	void on_comboBox_3_currentIndexChanged();

	void on_comboBox_activated();

	void on_checkBox_4_stateChanged();

private:

	Ui::MainWindow *ui;
	void clearTriggerList();
	void clearActionList();

};

#endif // MAINWINDOW_H
