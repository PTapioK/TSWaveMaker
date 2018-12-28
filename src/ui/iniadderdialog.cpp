#include "iniadderdialog.h"
#include "ui_iniadderdialog.h"
#include "../utils/CDataFile/CDataFile.h"
#include "../utils/containers.h"
#include "../utils/filehandler.h"

#include <sstream>
#include <iostream>

INIAdderDialog::INIAdderDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::INIAdderDialog)
{
	ui->setupUi(this);
}

INIAdderDialog::~INIAdderDialog()
{
	delete ui;
}

void INIAdderDialog::on_OKButton_clicked()
{
	CDataFile textData;
	textData.m_Flags |= AUTOCREATE_KEYS;
	textData.m_Flags |= AUTOCREATE_SECTIONS;
	QString qStr = ui->DropContentBox->toPlainText();
	std::stringstream ss;
	ss << qStr.toStdString();
	textData.AddFromText(ss);
	const SectionList* mapSectList = file.getDataHandle()->GetSectionList();
	const SectionList* addSectList = textData.GetSectionList();
	std::cout << textData.SectionCount() << std::endl;
	for (auto IT : *addSectList)
	{
		// There is one empty section for some reason
		if (!IT->szName.empty())
			std::cout << IT->szName << std::endl;
	}
}
