#ifndef SCRIPTSECTION_H
#define SCRIPTSECTION_H

#include <QtWidgets/QDockWidget>

#include "main.h"

namespace Ui {
class ScriptSection;
}

class ScriptSection : public QDockWidget
{
	Q_OBJECT
	
public:
	explicit ScriptSection(QWidget *parent = 0);
	~ScriptSection();
	
	void UpdateUi();
private slots:
	void on_ScriptList_itemSelectionChanged();

	void on_ScriptActionList_itemSelectionChanged();

	void on_SATypeBox_activated();

	void on_SATargetBox_activated();

	void on_CLastButton_clicked();

	void on_newS_clicked();

	void on_delS_clicked();

	void on_editSN_clicked();

	void on_cloneS_clicked();

	void on_newSA_clicked();

	void on_delSA_clicked();

private:
	Ui::ScriptSection *ui;
};

#endif // SCRIPTSECTION_H
