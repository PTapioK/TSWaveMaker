#include "../utils/utils.h"
#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "../utils/settings.h"

using namespace Settings;

SettingsDialog::SettingsDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);
	ui->rulesFileEdit->setText(tsRulesPath.left(tsRulesPath.lastIndexOf("/")));
	ui->firestrmEdit->setText(fsRulesPath.left(fsRulesPath.lastIndexOf("/")));

	ui->cloneOfBox->setChecked(cloneOfNaming);
	ui->ascNumBox->setChecked(ascNumNaming);
	ui->alphaOrdBox->setChecked(alphabetNaming);

	ui->disWarnings->setChecked(disableWarnings);
}

SettingsDialog::~SettingsDialog()
{
	delete ui;
}

void SettingsDialog::on_rulesFind_clicked()
{
	QString ts_rules_path = ui->rulesFileEdit->text();
	ts_rules_path = getRulesPathFor("rules.ini", ts_rules_path);
	if (!ts_rules_path.isEmpty()) {
		tsRulesPath = ts_rules_path + "/rules.ini";
		ui->rulesFileEdit->setText(ts_rules_path);
	}
}

void SettingsDialog::on_firestrmFind_clicked()
{
	QString fs_rules_path = ui->firestrmEdit->text();
	fs_rules_path = getRulesPathFor("firestrm.ini", fs_rules_path);
	if (!fs_rules_path.isEmpty()) {
		fsRulesPath = fs_rules_path + "/firestrm.ini";
		ui->firestrmEdit->setText(fs_rules_path);
	}
}

void SettingsDialog::on_saveButton_clicked()
{
	settings.setValue("rules/rulesPath", ui->rulesFileEdit->text());
	settings.setValue("rules/firestrmPath", ui->firestrmEdit->text());

	settings.setValue("cloneOfNaming", ui->cloneOfBox->isChecked());
	settings.setValue("increaseNumberNaming", ui->ascNumBox->isChecked());
	settings.setValue("alphabetsInOrderNaming", ui->alphaOrdBox->isChecked());

	settings.setValue("disableWarnings", ui->disWarnings->isChecked());

	settings.sync();
}

void SettingsDialog::closeEvent(QCloseEvent *event)
{
	event->accept();
	this->deleteLater();
}

void SettingsDialog::on_cloneOfBox_clicked()
{
	cloneOfNaming = ui->cloneOfBox->isChecked();
}

void SettingsDialog::on_ascNumBox_clicked()
{
	ascNumNaming = ui->ascNumBox->isChecked();
}

void SettingsDialog::on_alphaOrdBox_clicked()
{
	alphabetNaming = ui->alphaOrdBox->isChecked();
}

void SettingsDialog::on_disWarnings_clicked()
{
	disableWarnings = ui->disWarnings->isChecked();
}
