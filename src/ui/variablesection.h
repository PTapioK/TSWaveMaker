#ifndef VARIABLESECTION_H
#define VARIABLESECTION_H

#include <QDockWidget>

namespace Ui {
class VariableSection;
}

class VariableSection : public QDockWidget
{
	Q_OBJECT

public:
	explicit VariableSection(QWidget *parent = 0);
	~VariableSection();

	void updateUi();

private slots:
	void on_NewLocal_clicked();

	void on_LocalVariableList_itemSelectionChanged();

	void on_DeleteLocal_clicked();

	void on_EditLocalName_clicked();

	void on_CloneLocal_clicked();

	void on_InsertBeforeLocal_clicked();

	void on_isValueSetCheck_clicked();

private:
	Ui::VariableSection *ui;
};

#endif // VARIABLESECTION_H
