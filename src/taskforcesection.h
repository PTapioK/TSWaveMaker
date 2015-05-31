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

	void UpdateUi();
	
	private slots:

	private:
	Ui::TaskforceSection *ui;

};

#endif // TASKFORCESECTION_H
