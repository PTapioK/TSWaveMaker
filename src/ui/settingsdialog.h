#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

#include "../main.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
		Q_OBJECT

	protected:
		void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
	public:
		explicit SettingsDialog(QWidget *parent = 0);
		~SettingsDialog();
	private slots:
		void on_rulesFind_clicked();

		void on_firestrmFind_clicked();

		void on_saveButton_clicked();

		void on_cloneOfBox_clicked();

		void on_ascNumBox_clicked();

		void on_alphaOrdBox_clicked();

		void on_disWarnings_clicked();

private:
		Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
