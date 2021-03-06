#include "alliesdialog.h"
#include "ui_alliesdialog.h"

AlliesDialog::AlliesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlliesDialog)
{
    ui->setupUi(this);

	if (!allies.getDescription().isEmpty()) {
		this->setWindowTitle("Allies - " + allies.getDescription());
	}

	// Populate lists
	for (uint8_t i = 0; i < MAXPLAYERS; ++i) {
		QListWidgetItem * newSpawnItem = new QListWidgetItem(QString("Spawn ") + QString::number(i), ui->nonTeamList);
		newSpawnItem->setData(Qt::UserRole, i);
		ui->nonTeamList->addItem(newSpawnItem);
	}

	std::set<int32_t> teamA = allies.getPlayersByTeam("A");
	for (auto IT = teamA.begin(); IT != teamA.end(); ++IT) {
		QListWidgetItem * newSpawnItem = new QListWidgetItem(QString("Spawn ") + QString::number(*IT), ui->teamAList);
		newSpawnItem->setData(Qt::UserRole, *IT);
		ui->teamAList->addItem(newSpawnItem);
	}

	std::set<int32_t> teamB = allies.getPlayersByTeam("B");
	for (auto IT = teamB.begin(); IT != teamB.end(); ++IT) {
		QListWidgetItem * newSpawnItem = new QListWidgetItem(QString("Spawn ") + QString::number(*IT), ui->teamBList);
		newSpawnItem->setData(Qt::UserRole, *IT);
		ui->teamAList->addItem(newSpawnItem);
	}

	std::set<int32_t> teamC = allies.getPlayersByTeam("C");
	for (auto IT = teamC.begin(); IT != teamC.end(); ++IT) {
		QListWidgetItem * newSpawnItem = new QListWidgetItem(QString("Spawn ") + QString::number(*IT), ui->teamCList);
		newSpawnItem->setData(Qt::UserRole, *IT);
		ui->teamAList->addItem(newSpawnItem);
	}

	std::set<int32_t> teamD = allies.getPlayersByTeam("D");
	for (auto IT = teamD.begin(); IT != teamD.end(); ++IT) {
		QListWidgetItem * newSpawnItem = new QListWidgetItem(QString("Spawn ") + QString::number(*IT), ui->teamDList);
		newSpawnItem->setData(Qt::UserRole, *IT);
		ui->teamAList->addItem(newSpawnItem);
	}

	std::set<int32_t> teamE = allies.getPlayersByTeam("E");
	for (auto IT = teamE.begin(); IT != teamE.end(); ++IT) {
		QListWidgetItem * newSpawnItem = new QListWidgetItem(QString("Spawn ") + QString::number(*IT), ui->teamEList);
		newSpawnItem->setData(Qt::UserRole, *IT);
		ui->teamAList->addItem(newSpawnItem);
	}

	std::set<int32_t> teamF = allies.getPlayersByTeam("F");
	for (auto IT = teamF.begin(); IT != teamF.end(); ++IT) {
		QListWidgetItem * newSpawnItem = new QListWidgetItem(QString("Spawn ") + QString::number(*IT), ui->teamFList);
		newSpawnItem->setData(Qt::UserRole, *IT);
		ui->teamAList->addItem(newSpawnItem);
	}

	std::set<int32_t> teamG = allies.getPlayersByTeam("G");
	for (auto IT = teamG.begin(); IT != teamG.end(); ++IT) {
		QListWidgetItem * newSpawnItem = new QListWidgetItem(QString("Spawn ") + QString::number(*IT), ui->teamGList);
		newSpawnItem->setData(Qt::UserRole, *IT);
		ui->teamAList->addItem(newSpawnItem);
	}

	std::set<int32_t> teamH = allies.getPlayersByTeam("H");
	for (auto IT = teamH.begin(); IT != teamH.end(); ++IT) {
		QListWidgetItem * newSpawnItem = new QListWidgetItem(QString("Spawn ") + QString::number(*IT), ui->teamHList);
		newSpawnItem->setData(Qt::UserRole, *IT);
		ui->teamAList->addItem(newSpawnItem);
	}

	QShortcut* teamADelete = new QShortcut(QKeySequence(Qt::Key_Delete), ui->teamAList);
	connect(teamADelete, &QShortcut::activatedAmbiguously, this, [&](){deleteFrom(ui->teamAList);});

	QShortcut* teamBDelete = new QShortcut(QKeySequence(Qt::Key_Delete), ui->teamBList);
	connect(teamBDelete, &QShortcut::activatedAmbiguously, this, [&](){deleteFrom(ui->teamBList);});

	QShortcut* teamCDelete = new QShortcut(QKeySequence(Qt::Key_Delete), ui->teamCList);
	connect(teamCDelete, &QShortcut::activatedAmbiguously, this, [&](){deleteFrom(ui->teamCList);});

	QShortcut* teamDDelete = new QShortcut(QKeySequence(Qt::Key_Delete), ui->teamDList);
	connect(teamDDelete, &QShortcut::activatedAmbiguously, this, [&](){deleteFrom(ui->teamDList);});

	QShortcut* teamEDelete = new QShortcut(QKeySequence(Qt::Key_Delete), ui->teamEList);
	connect(teamEDelete, &QShortcut::activatedAmbiguously, this, [&](){deleteFrom(ui->teamEList);});

	QShortcut* teamFDelete = new QShortcut(QKeySequence(Qt::Key_Delete), ui->teamFList);
	connect(teamFDelete, &QShortcut::activatedAmbiguously, this, [&](){deleteFrom(ui->teamFList);});

	QShortcut* teamGDelete = new QShortcut(QKeySequence(Qt::Key_Delete), ui->teamGList);
	connect(teamGDelete, &QShortcut::activatedAmbiguously, this, [&](){deleteFrom(ui->teamGList);});

	QShortcut* teamHDelete = new QShortcut(QKeySequence(Qt::Key_Delete), ui->teamHList);
	connect(teamHDelete, &QShortcut::activatedAmbiguously, this, [&](){deleteFrom(ui->teamHList);});

	connect(ui->teamAList, &QListWidget::customContextMenuRequested, this, [&](const QPoint &pos){showContextMenu(pos, ui->teamAList);});
	connect(ui->teamBList, &QListWidget::customContextMenuRequested, this, [&](const QPoint &pos){showContextMenu(pos, ui->teamBList);});
	connect(ui->teamCList, &QListWidget::customContextMenuRequested, this, [&](const QPoint &pos){showContextMenu(pos, ui->teamCList);});
	connect(ui->teamDList, &QListWidget::customContextMenuRequested, this, [&](const QPoint &pos){showContextMenu(pos, ui->teamDList);});
	connect(ui->teamEList, &QListWidget::customContextMenuRequested, this, [&](const QPoint &pos){showContextMenu(pos, ui->teamEList);});
	connect(ui->teamFList, &QListWidget::customContextMenuRequested, this, [&](const QPoint &pos){showContextMenu(pos, ui->teamFList);});
	connect(ui->teamGList, &QListWidget::customContextMenuRequested, this, [&](const QPoint &pos){showContextMenu(pos, ui->teamGList);});
	connect(ui->teamHList, &QListWidget::customContextMenuRequested, this, [&](const QPoint &pos){showContextMenu(pos, ui->teamHList);});
}

AlliesDialog::~AlliesDialog()
{
	delete ui;
}

void AlliesDialog::closeEvent(QCloseEvent *event)
{
	event->accept();
	this->deleteLater();
}

void AlliesDialog::on_AButton_clicked()
{
	ui->stackedWidget->setCurrentIndex(1);
}

void AlliesDialog::on_EButton_clicked()
{
	ui->stackedWidget->setCurrentIndex(0);
}

void AlliesDialog::on_BButton_clicked()
{
	ui->stackedWidget_2->setCurrentIndex(1);
}

void AlliesDialog::on_FButton_clicked()
{
	ui->stackedWidget_2->setCurrentIndex(0);
}

void AlliesDialog::on_CButton_clicked()
{
	ui->stackedWidget_3->setCurrentIndex(1);
}

void AlliesDialog::on_GButton_clicked()
{
	ui->stackedWidget_3->setCurrentIndex(0);
}

void AlliesDialog::on_DButton_clicked()
{
	ui->stackedWidget_4->setCurrentIndex(1);
}

void AlliesDialog::on_HButton_clicked()
{
	ui->stackedWidget_4->setCurrentIndex(0);
}

void AlliesDialog::deleteFrom(QListWidget *listWidget)
{
	if (listWidget->hasFocus()) delete listWidget->currentItem();
}

void AlliesDialog::on_teamAList_itemChanged(QListWidgetItem *item)
{
	for (int i = 0; i < ui->teamAList->count(); ++i) {
		if (ui->teamAList->item(i)->data(Qt::UserRole) == item->data(Qt::UserRole) && item != ui->teamAList->item(i)) {
			delete item;
			return;
		}
	}
}

void AlliesDialog::on_teamEList_itemChanged(QListWidgetItem *item)
{
	for (int i = 0; i < ui->teamEList->count(); ++i) {
		if (ui->teamEList->item(i)->data(Qt::UserRole) == item->data(Qt::UserRole) && item != ui->teamEList->item(i)) {
			delete item;
			return;
		}
	}
}

void AlliesDialog::on_teamBList_itemChanged(QListWidgetItem *item)
{
	for (int i = 0; i < ui->teamBList->count(); ++i) {
		if (ui->teamBList->item(i)->data(Qt::UserRole) == item->data(Qt::UserRole) && item != ui->teamBList->item(i)) {
			delete item;
			return;
		}
	}
}

void AlliesDialog::on_teamFList_itemChanged(QListWidgetItem *item)
{
	for (int i = 0; i < ui->teamFList->count(); ++i) {
		if (ui->teamFList->item(i)->data(Qt::UserRole) == item->data(Qt::UserRole) && item != ui->teamFList->item(i)) {
			delete item;
			return;
		}
	}
}

void AlliesDialog::on_teamCList_itemChanged(QListWidgetItem *item)
{
	for (int i = 0; i < ui->teamCList->count(); ++i) {
		if (ui->teamCList->item(i)->data(Qt::UserRole) == item->data(Qt::UserRole) && item != ui->teamCList->item(i)) {
			delete item;
			return;
		}
	}
}

void AlliesDialog::on_teamGList_itemChanged(QListWidgetItem *item)
{
	for (int i = 0; i < ui->teamGList->count(); ++i) {
		if (ui->teamGList->item(i)->data(Qt::UserRole) == item->data(Qt::UserRole) && item != ui->teamGList->item(i)) {
			delete item;
			return;
		}
	}
}

void AlliesDialog::on_teamDList_itemChanged(QListWidgetItem *item)
{
	for (int i = 0; i < ui->teamDList->count(); ++i) {
		if (ui->teamDList->item(i)->data(Qt::UserRole) == item->data(Qt::UserRole) && item != ui->teamDList->item(i)) {
			delete item;
			return;
		}
	}
}

void AlliesDialog::on_teamHList_itemChanged(QListWidgetItem *item)
{
	for (int i = 0; i < ui->teamHList->count(); ++i) {
		if (ui->teamHList->item(i)->data(Qt::UserRole) == item->data(Qt::UserRole) && item != ui->teamHList->item(i)) {
			delete item;
			return;
		}
	}
}

void AlliesDialog::on_saveButton_clicked()
{
	allies.clearTeams();

	for (int i = 0; i < ui->teamAList->count(); ++i) {
		allies.addPlayerToTeam(ui->teamAList->item(i)->data(Qt::UserRole).toInt(), "A");
	}
	for (int i = 0; i < ui->teamBList->count(); ++i) {
		allies.addPlayerToTeam(ui->teamBList->item(i)->data(Qt::UserRole).toInt(), "B");
	}
	for (int i = 0; i < ui->teamCList->count(); ++i) {
		allies.addPlayerToTeam(ui->teamCList->item(i)->data(Qt::UserRole).toInt(), "C");
	}
	for (int i = 0; i < ui->teamDList->count(); ++i) {
		allies.addPlayerToTeam(ui->teamDList->item(i)->data(Qt::UserRole).toInt(), "D");
	}
	for (int i = 0; i < ui->teamEList->count(); ++i) {
		allies.addPlayerToTeam(ui->teamEList->item(i)->data(Qt::UserRole).toInt(), "E");
	}
	for (int i = 0; i < ui->teamFList->count(); ++i) {
		allies.addPlayerToTeam(ui->teamFList->item(i)->data(Qt::UserRole).toInt(), "F");
	}
	for (int i = 0; i < ui->teamGList->count(); ++i) {
		allies.addPlayerToTeam(ui->teamGList->item(i)->data(Qt::UserRole).toInt(), "G");
	}
	for (int i = 0; i < ui->teamHList->count(); ++i) {
		allies.addPlayerToTeam(ui->teamHList->item(i)->data(Qt::UserRole).toInt(), "H");
	}

	this->close();
}

void AlliesDialog::on_cancelButton_clicked()
{
	this->close();
}

void AlliesDialog::showContextMenu(const QPoint &pos, QListWidget *listWidget)
{
	QPoint globalPos = listWidget->mapToGlobal(pos);

	QMenu deleteMenu;
	deleteMenu.addAction("Delete", this, [&](){deleteFrom((listWidget));});

	deleteMenu.exec(globalPos);
}

void AlliesDialog::on_clearButton_clicked()
{
	ui->teamAList->clear();
	ui->teamBList->clear();
	ui->teamCList->clear();
	ui->teamDList->clear();
	ui->teamEList->clear();
	ui->teamFList->clear();
	ui->teamGList->clear();
	ui->teamHList->clear();
}
