#include "main.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	currentFileData.m_Flags |= AUTOCREATE_KEYS;
	currentFileData.m_Flags |= AUTOCREATE_SECTIONS;
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
