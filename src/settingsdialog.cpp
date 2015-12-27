#include "utils.h"
#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);
	ui->rulesFileEdit->setText(tsRulesPath.substr(0, tsRulesPath.find_last_of("/")).c_str());
	ui->firestrmEdit->setText(fsRulesPath.substr(0, fsRulesPath.find_last_of("/")).c_str());

	ui->cloneOfBox->setChecked(cloneOfNaming);
	ui->ascNumBox->setChecked(ascNumNaming);
	ui->alphaOrdBox->setChecked(alphabetNaming);
}

SettingsDialog::~SettingsDialog()
{
	delete ui;
}

void SettingsDialog::on_rulesFind_clicked()
{
	std::string ts_rules_path = ui->rulesFileEdit->text().toStdString();
	ts_rules_path = rulesPathForTS(ts_rules_path);
	tsRulesPath = ts_rules_path + "/rules.ini";
	ui->rulesFileEdit->setText(ts_rules_path.c_str());
}

void SettingsDialog::on_firestrmFind_clicked()
{
	std::string fs_rules_path = ui->firestrmEdit->text().toStdString();
	fs_rules_path = rulesPathForFS(fs_rules_path);
	fsRulesPath = fs_rules_path + "/firestrm.ini";
	ui->firestrmEdit->setText(fs_rules_path.c_str());
}

void SettingsDialog::on_saveButton_clicked()
{
	settingsFileData.SetValue("rulesPath", ui->rulesFileEdit->text().toStdString(), "", "rules");
	settingsFileData.SetValue("firestrmPath", ui->firestrmEdit->text().toStdString(), "", "rules");

	settingsFileData.SetBool("cloneOfNaming", ui->cloneOfBox->isChecked());
	settingsFileData.SetBool("increaseNumberNaming", ui->ascNumBox->isChecked());
	settingsFileData.SetBool("alphabetsInOrderNaming", ui->alphaOrdBox->isChecked());

	settingsFileData.Save();
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
