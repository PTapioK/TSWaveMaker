#ifndef TEAMSECTION_H
#define TEAMSECTION_H

#include <QtWidgets/QDockWidget>

#include "main.h"

class TeamSection : public QDockWidget
{
	Q_OBJECT
	
public:
	explicit TeamSection(QWidget *parent = 0);
	~TeamSection();

public slots:
	void UpdateUi();
	void on_New_clicked();

signals:
	void NewUnit();

private slots:

	void on_TeamList_itemSelectionChanged();

	void on_Delete_clicked();

	void on_EditName_clicked();

	void on_Clone_clicked();

	void on_scriptBox_activated();

	void on_taskforceBox_activated();

	void on_SAOButton_clicked();

	void on_isLoadable_clicked();

	void on_isAreTeamMembersRecruitable_clicked();

	void on_isTransportsReturnOnUnload_clicked();

	void on_isReinforce_clicked();

	void on_isDroppod_clicked();

	void on_isAutocreate_clicked();

	void on_isOnlyTargetHouseEnemy_clicked();

	void on_isAggressive_clicked();

	void on_isFull_clicked();

	void on_isAvoidThreats_clicked();

	void on_isIsBaseDefense_clicked();

	void on_isAnnoyance_clicked();

	void on_isGuardSlower_clicked();

	void on_isIonImmune_clicked();

	void on_isLooseRecruit_clicked();

	void on_isOnTransOnly_clicked();

	void on_isPrebuild_clicked();

	void on_isRecruiter_clicked();

	void on_isSuicide_clicked();

	void on_isWhiner_clicked();

	void mousePressEvent(QMouseEvent *event);

	private:
	Ui::TeamSection *ui;
};

#endif // TEAMSECTION_H
