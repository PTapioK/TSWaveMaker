#include "infodialog.h"
#include "ui_infodialog.h"

InfoDialog::InfoDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::InfoDialog)
{
	ui->setupUi(this);
	ui->gitBuild->setText(GIT_VERSION);
}

InfoDialog::~InfoDialog()
{
	delete ui;
}

void InfoDialog::closeEvent(QCloseEvent *event) {
	event->accept();
	this->deleteLater();
}
