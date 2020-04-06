#include "settings.h"

namespace Settings {

const QString settingsFilePath = "settings.ini";
const QString scriptStringsPath = "scriptstrings.ini";
const QString triggerStringsPath = "triggerstrings.ini";

QString tsRulesPath;
QString fsRulesPath;
QString lastUsedPath;

QSettings settings(settingsFilePath, QSettings::IniFormat);
QSettings scriptStrings(scriptStringsPath, QSettings::IniFormat);
QSettings triggerStrings(triggerStringsPath, QSettings::IniFormat);

bool cloneOfNaming, ascNumNaming, alphabetNaming;
bool disableWarnings;

void loadSettings()
{
	QString ts_rules_path = settings.value("rules/rulesPath").toString();
	QString fs_rules_path = settings.value("rules/firestrmPath").toString();

	cloneOfNaming = settings.value("cloneOfNaming", "false").toBool();
	ascNumNaming  = settings.value("increaseNumberNaming", "false").toBool();
	alphabetNaming = settings.value("alphabetsInOrderNaming", "false").toBool();

	lastUsedPath = settings.value("lastUsedPath", ".").toString();

	disableWarnings = settings.value("disableWarnings", "true").toBool();

    QDir current_path(QCoreApplication::applicationDirPath());
    const QString relative_ini_path = "../../ini/";

    if(QFile::exists(current_path.absoluteFilePath(relative_ini_path + "rules.ini")))
    {
        QFileInfo ts_rules_info(current_path.absoluteFilePath(relative_ini_path + "rules.ini"));
        ts_rules_path = ts_rules_info.absolutePath();
    }
    if(QFile::exists(current_path.absoluteFilePath(relative_ini_path + "firestrm.ini")))
    {
        QFileInfo fs_rules_info(current_path.absoluteFilePath(relative_ini_path + "firestrm.ini"));
        fs_rules_path = fs_rules_info.absolutePath();
    }

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
