#ifndef INIADDERDIALOG_H
#define INIADDERDIALOG_H

#include <QDialog>

namespace Ui {
class INIAdderDialog;
}

class INIAdderDialog : public QDialog
{
	Q_OBJECT

public:
	explicit INIAdderDialog(QWidget *parent = nullptr);
	~INIAdderDialog();

private slots:
	void on_OKButton_clicked();

private:
	Ui::INIAdderDialog *ui;
};

#endif // INIADDERDIALOG_H
