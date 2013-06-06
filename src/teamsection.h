#ifndef TEAMSECTION_H
#define TEAMSECTION_H

#include <QDockWidget>

#include "main.h"

class TeamSection : public QDockWidget
{
	Q_OBJECT
	
public:
	explicit TeamSection(QWidget *parent = 0);
	~TeamSection();

	void UpdateUi();
	
private slots:
	void on_New_clicked();

	void on_TeamList_itemSelectionChanged();

	void on_Delete_clicked();

	void on_isSuicde_stateChanged(int arg1);

	void on_isLoadable_stateChanged(int arg1);

	void on_isTransportsReturnOnUnload_stateChanged(int arg1);

	void on_isAreTeamMembersRecruitable_stateChanged(int arg1);

	void on_isReinforce_stateChanged(int arg1);

	void on_isDroppod_stateChanged(int arg1);

	void on_isAutocreate_stateChanged(int arg1);

	void on_isOnlyTargetHouseEnemy_stateChanged(int arg1);

	void on_isAggressive_stateChanged(int arg1);

	void on_isFull_stateChanged(int arg1);

	void on_isAvoidThreats_stateChanged(int arg1);

	void on_isIsBaseDefense_stateChanged(int arg1);

	void on_EditName_clicked();

	void on_Clone_clicked();

	void on_scriptBox_activated();

private:
	Ui::TeamSection *ui;
};

#endif // TEAMSECTION_H
