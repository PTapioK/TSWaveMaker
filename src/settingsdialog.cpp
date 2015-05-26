#include "utils.h"
#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);
	ui->rulesFileEdit->setText(ts_rules.substr(0, ts_rules.find_last_of("/")).c_str());
	ui->firestrmEdit->setText(fs_rules.substr(0, fs_rules.find_last_of("/")).c_str());
}

SettingsDialog::~SettingsDialog()
{
	delete ui;
}

void SettingsDialog::on_rulesFind_clicked()
{
	string ts_rules_path = ui->rulesFileEdit->text().toStdString();
	ts_rules_path = TSRulesPath(ts_rules_path);
	ts_rules = ts_rules_path + "/rules.ini";
	ui->rulesFileEdit->setText(ts_rules_path.c_str());
}

void SettingsDialog::on_firestrmFind_clicked()
{
	string fs_rules_path = ui->firestrmEdit->text().toStdString();
	fs_rules_path = FSRulesPath(fs_rules_path);
	fs_rules = fs_rules_path + "/firestrm.ini";
	ui->firestrmEdit->setText(fs_rules_path.c_str());
}

void SettingsDialog::on_saveButton_clicked()
{
	settings_data.SetValue("rules_path", ui->rulesFileEdit->text().toStdString());
	settings_data.SetValue("firestrm_path", ui->firestrmEdit->text().toStdString());
	settings_data.Save();
}

void SettingsDialog::closeEvent(QCloseEvent *event)
{
	this->deleteLater();
}
