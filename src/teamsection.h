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
	
private slots:
	void on_New_clicked();

	void on_TeamList_itemSelectionChanged();

private:
	Ui::TeamSection *ui;
};

#endif // TEAMSECTION_H
