#ifndef TASKFORCESECTION_H
#define TASKFORCESECTION_H

#include <QtWidgets/QDockWidget>

#include "main.h"

class TaskforceSection : public QDockWidget
{
	Q_OBJECT
	
	public:
		explicit TaskforceSection(QWidget *parent = 0);
		~TaskforceSection();

		void updateUi();

		private slots:

		void on_TaskforceList_itemSelectionChanged();

		void on_NewTaskforce_clicked();

		void on_DeleteTaskforce_clicked();

		void on_editTaskforceName_clicked();

		void on_cloneTaskforce_clicked();

		void on_UnitList_itemSelectionChanged();

		void on_UnitBox_activated();

		void on_UnitNumberBox_editingFinished();

		void on_AddUnit_clicked();

		void on_DeleteUnit_clicked();

		void mousePressEvent(QMouseEvent *event);

	private:

		Ui::TaskforceSection *ui;

};

#endif // TASKFORCESECTION_H
