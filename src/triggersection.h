#ifndef TRIGGERSECTION_H
#define TRIGGERSECTION_H

#include <QtWidgets/QDockWidget>

#include "main.h"

class TriggerSection : public QDockWidget
{
	Q_OBJECT
	
	public:
		explicit TriggerSection(QWidget *parent = 0);
		~TriggerSection();
	public slots:
		void updateUi();
	private slots:
		void on_TriggerList_itemSelectionChanged();

		void on_NewTrigger_clicked();

		void on_EditTriggerName_clicked();

		void on_isDisabledCheck_clicked();

		void on_DeleteTrigger_clicked();

		void on_CloneTrigger_clicked();

		void on_WaveTimer_editingFinished();

		void on_NewAction_clicked();

		void on_DeleteAction_clicked();

		void on_CloneAction_clicked();

		void on_ActionList_itemSelectionChanged();

		void mousePressEvent(QMouseEvent *event);
	private:
		Ui::TriggerSection *ui;

		void clearTriggerList();
		void clearActionList();
};

#endif // TRIGGERSECTION_H
