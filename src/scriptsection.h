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

		void updateUi();
	private slots:
		void on_ScriptList_itemSelectionChanged();

		void on_ScriptActionList_itemSelectionChanged();

		void on_SATypeBox_activated();

		void on_SATargetBox_activated();

		void updateSATargeBox();

		void on_CLastButton_clicked();

		void on_newS_clicked();

		void on_delS_clicked();

		void on_editSN_clicked();

		void on_cloneS_clicked();

		void on_newSA_clicked();

		void on_delSA_clicked();

		void on_SATargetBox_editTextChanged(const QString &arg1);

		void on_lowThreat_clicked();

		void on_bigThreat_clicked();

		void on_nearTarget_clicked();

		void on_farTarget_clicked();

		void on_defaultTarget_clicked();

		void on_newSA_Bef_clicked();

		void mousePressEvent(QMouseEvent *event);
	private:
		void updateSATypeBox();
		QStringList getScriptActionTargetStrings(SATargetType type);
		QString getScriptNameByPosition(uint16_t pos);
		QString getTaskforceNameByPosition(uint16_t pos);

		Ui::ScriptSection *ui;
};

#endif // SCRIPTSECTION_H
