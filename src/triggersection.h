#ifndef TRIGGERSECTION_H
#define TRIGGERSECTION_H

#include <QDockWidget>

#include "main.h"

class TriggerSection : public QDockWidget
{
	Q_OBJECT
	
public:
	explicit TriggerSection(QWidget *parent = 0);
	~TriggerSection();

public slots:

	void UpdateUi();

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

	void on_ActionList_itemClicked();

	void on_WaypointBox_currentIndexChanged();

	void on_SWaypointBox_currentIndexChanged();

	void on_TeamtypeBox_activated();

	void on_WPointAOButton_clicked();

	void on_isReinforcementCheck_clicked();

	void on_TeamAOButton_clicked();

private:
	Ui::TriggerSection *ui;

	void clearTriggerList();
	void clearActionList();

};

#endif // TRIGGERSECTION_H
