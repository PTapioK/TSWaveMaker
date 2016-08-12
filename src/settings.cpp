#include "settings.h"

namespace Settings {

const QString settingsFilePath = "settings.ini";
const QString scriptStringsPath = "scriptstrings.ini";

QString tsRulesPath;
QString fsRulesPath;
QString lastUsedPath;

QSettings settings(settingsFilePath, QSettings::IniFormat);
QSettings scriptStrings(scriptStringsPath, QSettings::IniFormat);

bool cloneOfNaming, ascNumNaming, alphabetNaming;

void loadSettings(bool ask)
{
	QString ts_rules_path = settings.value("rules/rulesPath").toString();
	QString fs_rules_path = settings.value("rules/firestrmPath").toString();

	cloneOfNaming = settings.value("cloneOfNaming").toBool();
	ascNumNaming  = settings.value("increaseNumberNaming").toBool();
	alphabetNaming = settings.value("alphabetsInOrderNaming").toBool();

	lastUsedPath = settings.value("lastUsedPath", ".").toString();

	if(ask) {
		if(ts_rules_path.isEmpty()) {
			if(QMessageBox::question(NULL, "Rules.ini path hasn't been set", "Rules.ini path has not been set. Do you want set it now?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
				ts_rules_path = getRulesPathFor("rules.ini", ts_rules_path);
			}
		}
		if(fs_rules_path.isEmpty()) {
			if(QMessageBox::question(NULL, "Firestrm.ini path hasn't been set", "Firestrm.ini path has not been set. Do you want set it now?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
				fs_rules_path = getRulesPathFor("firestrm.ini", fs_rules_path);
			}
		}
	}

	settings.setValue("rules/rulesPath", ts_rules_path);
	settings.setValue("rules/firestrmPath", fs_rules_path);

	tsRulesPath = ts_rules_path + "/rules.ini";
	fsRulesPath = fs_rules_path + "/firestrm.ini";

	settings.sync();
}

QString getRulesPathFor(QString fileName, QString path)
{
	QFileDialog fDG(NULL);
	fDG.setFileMode(QFileDialog::Directory);
	fDG.setOption(QFileDialog::ShowDirsOnly, true);
	return fDG.getExistingDirectory(NULL, "Select directory containing " + fileName, path);
}

}
