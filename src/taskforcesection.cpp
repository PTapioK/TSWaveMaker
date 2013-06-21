#include "taskforcesection.h"
#include "ui_taskforcesection.h"

TaskforceSection::TaskforceSection(QWidget *parent) :
	QDockWidget(parent),
	ui(new Ui::TaskforceSection)
{
	ui->setupUi(this);
}

TaskforceSection::~TaskforceSection()
{
	delete ui;
}

void TaskforceSection::UpdateUi()
{
	for(taskforceIT = taskforces.begin(); taskforceIT != taskforces.end(); ++taskforceIT) {
		ui->TaskforceList->addItem(taskforceIT->second->getName().c_str());
	}
}
