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
	for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		ui->TaskforceList->addItem(IT->second->getName().c_str());
	}
}
