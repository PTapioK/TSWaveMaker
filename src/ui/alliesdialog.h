#ifndef ALLIESDIALOG_H
#define ALLIESDIALOG_H

#include "../main.h"

namespace Ui {
class AlliesDialog;
}

class AlliesDialog : public QDialog
{
	Q_OBJECT

public:
	explicit AlliesDialog(QWidget *parent = 0);
	~AlliesDialog();

protected:
	void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
	void on_AButton_clicked();
	void on_EButton_clicked();
	void on_BButton_clicked();
	void on_FButton_clicked();
	void on_CButton_clicked();
	void on_GButton_clicked();
	void on_DButton_clicked();
	void on_HButton_clicked();

	void deleteFrom(QListWidget *listWidget);

	void on_teamAList_itemChanged(QListWidgetItem *item);
	void on_teamEList_itemChanged(QListWidgetItem *item);
	void on_teamBList_itemChanged(QListWidgetItem *item);
	void on_teamFList_itemChanged(QListWidgetItem *item);
	void on_teamCList_itemChanged(QListWidgetItem *item);
	void on_teamGList_itemChanged(QListWidgetItem *item);
	void on_teamDList_itemChanged(QListWidgetItem *item);
	void on_teamHList_itemChanged(QListWidgetItem *item);

	void on_saveButton_clicked();
	void on_cancelButton_clicked();

	void showContextMenu(const QPoint &pos, QListWidget *listWidget);
	void on_clearButton_clicked();

private:
	Ui::AlliesDialog *ui;
};

#endif // ALLIESDIALOG_H
