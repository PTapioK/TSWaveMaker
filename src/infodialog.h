#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QtWidgets/QDialog>

#include "main.h"

namespace Ui {
class InfoDialog;
}

class InfoDialog : public QDialog
{
	Q_OBJECT
	protected:
		void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
	public:
		explicit InfoDialog(QWidget *parent = 0);
		~InfoDialog();
	private:
		Ui::InfoDialog *ui;
};

#endif // INFODIALOG_H
