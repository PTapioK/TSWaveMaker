#include "teamsection.h"
#include "ui_teamsection.h"

TeamSection::TeamSection(QWidget *parent) :
	QDockWidget(parent),
	ui(new Ui::TeamSection)
{
	ui->setupUi(this);
}

TeamSection::~TeamSection()
{
	delete ui;
}

// New team
void TeamSection::on_New_clicked()
{
	if(ui->TeamList->findItems(ui->NameEdit->text(), Qt::MatchExactly).count() == 0) {
		string name = ui->NameEdit->text().toStdString();
		ui->TeamList->addItem(ui->NameEdit->text());
		teams[name] = new Team(fffID(), name);
	}
}

void TeamSection::on_TeamList_itemSelectionChanged()
{

}
