#include "../utils/containers.h"
#include "variablesection.h"
#include "ui_variablesection.h"

VariableSection::VariableSection(QWidget *parent) :
	QDockWidget(parent),
	ui(new Ui::VariableSection)
{
	ui->setupUi(this);
}

VariableSection::~VariableSection()
{
	delete ui;
}

void VariableSection::updateUi()
{
	ui->LocalVariableList->clearSelection();
	ui->LocalVariableList->clear();
	for(auto IT = localvariables.begin(); IT != localvariables.end(); ++IT) {
		QListWidgetItem* newVarItem = new QListWidgetItem(IT->second.name + ", " + QString::number(IT->second.set), ui->LocalVariableList);
		newVarItem->setData(Qt::ItemDataRole::UserRole, IT->second.name);
		ui->LocalVariableList->addItem(newVarItem);
	}
}

void VariableSection::on_NewLocal_clicked()
{
	QString name = ui->LocalNameEdit->text();
	if(findLocalVariableByName(name) == NULL) {
		uint16_t nID = uint16_t(localvariables.size());
		variableContainer nVar;
		nVar.name = name;
		nVar.set = false;
		localvariables[nID] = nVar;

		QListWidgetItem* newVarItem = new QListWidgetItem(name + ", " + QString::number(false), ui->LocalVariableList);
		newVarItem->setData(Qt::ItemDataRole::UserRole, name);
		ui->LocalVariableList->addItem(newVarItem);
	}
}

void VariableSection::on_LocalVariableList_itemSelectionChanged()
{
	if(ui->LocalVariableList->selectedItems().size() != 0) {
		const QString name = ui->LocalVariableList->selectedItems().last()->data(Qt::ItemDataRole::UserRole).toString();
		variableContainer* curVariable = findLocalVariableByName(name, true);

		ui->LocalNameEdit->setText(curVariable->name);
		ui->isValueSetCheck->setChecked(curVariable->set);
	}
}

void VariableSection::on_DeleteLocal_clicked()
{
	if(ui->LocalVariableList->selectedItems().size() != 0) {
		for(int a = 0; a != ui->LocalVariableList->selectedItems().size(); ++a) {
			const QString name = ui->LocalVariableList->selectedItems().at(a)->data(Qt::ItemDataRole::UserRole).toString();
			uint16_t curVariableKey = getLocalVariableKeyByName(name);
			localvariables.erase(curVariableKey);
		}
		updateUi();
	}
}

void VariableSection::on_EditLocalName_clicked()
{
	if(ui->LocalVariableList->selectedItems().size() != 0) {
		QString name = ui->LocalNameEdit->text();
		if(findLocalVariableByName(name) == NULL) {
			QListWidgetItem* curItem = ui->LocalVariableList->selectedItems().last();
			const QString curName = curItem->data(Qt::ItemDataRole::UserRole).toString();
			const QString newName = ui->LocalNameEdit->text();
			variableContainer* curVariable = findLocalVariableByName(curName, true);

			curVariable->name = newName;
			curItem->setText(newName + ", " + QString::number(curVariable->set));
			curItem->setData(Qt::ItemDataRole::UserRole, newName);
		}
	}
}

void VariableSection::on_CloneLocal_clicked()
{
	if(ui->LocalVariableList->selectedItems().size() != 0) {
		for(int a = 0; a != ui->LocalVariableList->selectedItems().size(); ++a) {
			QListWidgetItem* curItem = ui->LocalVariableList->selectedItems().at(a);
			const QString curName = curItem->data(Qt::ItemDataRole::UserRole).toString();
			variableContainer* curVariable = findLocalVariableByName(curName, true);
			QString newName = getNameWithNextMark(curVariable->name, a, 0);

			int i = 0;
			while(findLocalVariableByName(newName) != NULL) {
				++i;
				newName = getNameWithNextMark(curName, i);
			}
			uint16_t nID = uint16_t(localvariables.size());
			variableContainer nVar;
			nVar.name = newName;
			nVar.set = curVariable->set;
			localvariables[nID] = nVar;

			QListWidgetItem* newVarItem = new QListWidgetItem(newName + ", " + QString::number(curVariable->set), ui->LocalVariableList);
			newVarItem->setData(Qt::ItemDataRole::UserRole, newName);
			ui->LocalVariableList->addItem(newVarItem);
		}
	}
}

void VariableSection::on_InsertBeforeLocal_clicked()
{
	QString name = ui->LocalNameEdit->text();
	if(findLocalVariableByName(name) == NULL && !localvariables.empty()) {
		uint16_t nID = uint16_t(ui->LocalVariableList->currentRow());
		for (int32_t i = int32_t(localvariables.size()) - 1; i >= nID; --i) {
			localvariables[uint16_t(i + 1)] = localvariables[uint16_t(i)];
		}
		variableContainer nVar;
		nVar.name = name;
		nVar.set = false;
		localvariables[nID] = nVar;

		QListWidgetItem* newVarItem = new QListWidgetItem(name + ", " + QString::number(false), ui->LocalVariableList);
		newVarItem->setData(Qt::ItemDataRole::UserRole, name);

		updateUi();
	}
}

void VariableSection::on_isValueSetCheck_clicked()
{
	for(int a = 0; a != ui->LocalVariableList->selectedItems().size(); ++a) {
		QListWidgetItem* curItem = ui->LocalVariableList->selectedItems().at(a);
		const QString curName = curItem->data(Qt::ItemDataRole::UserRole).toString();
		variableContainer* curVariable = findLocalVariableByName(curName, true);
		curVariable->set = ui->isValueSetCheck->isChecked();
		curItem->setText(curName + ", " + QString::number(curVariable->set));
	}
}
