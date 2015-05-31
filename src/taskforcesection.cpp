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
	ui->TaskforceList->clearSelection();
	ui->TaskforceList->clear();
	for(taskforceIT IT = taskforces.begin(); IT != taskforces.end(); ++IT) {
		QListWidgetItem * newItem = new QListWidgetItem(ui->TaskforceList);
		newItem->setText(IT->second->getName().c_str());
		newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);
		ui->TaskforceList->addItem(newItem);
	}
}
