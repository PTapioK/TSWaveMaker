#ifndef SCRIPTSECTION_H
#define SCRIPTSECTION_H

#include <QDockWidget>

namespace Ui {
class ScriptSection;
}

class ScriptSection : public QDockWidget
{
	Q_OBJECT
	
public:
	explicit ScriptSection(QWidget *parent = 0);
	~ScriptSection();
	
private:
	Ui::ScriptSection *ui;
};

#endif // SCRIPTSECTION_H
