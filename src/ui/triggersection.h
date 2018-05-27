#ifndef TRIGGERSECTION_H
#define TRIGGERSECTION_H

#include <QtWidgets/QDockWidget>

#include "../main.h"

class TriggerSection : public QDockWidget
{
	Q_OBJECT
	
	public:
		explicit TriggerSection(QWidget *parent = 0);
		~TriggerSection();
	public slots:
		void updateUi();
	private slots:
		void on_TriggerList_itemSelectionChanged();

		void on_NewTrigger_clicked();

		void on_EditTriggerName_clicked();

		void on_isDisabledCheck_clicked();

		void on_DeleteTrigger_clicked();

		void on_CloneTrigger_clicked();

		void on_WaveTimer_editingFinished();

		void on_NewAction_clicked();

		void on_DeleteAction_clicked();

		void on_CloneAction_clicked();

		void on_ActionList_itemSelectionChanged();

		void mousePressEvent(QMouseEvent *event);

		void on_TagOr_clicked();

		void on_TagAnd_clicked();

		void on_TagRepeatingOr_clicked();

		void on_EventList_itemSelectionChanged();

		void on_NewEvent_clicked();

		void on_DeleteEvent_clicked();

		void on_CloneEvent_clicked();

		void on_EventTypeBox_activated();

		void on_EventParamBox_activated();

		void on_TEParamAOButton_clicked();

		void on_ActionTypeBox_activated();

		void on_ActionParamNameBox_activated();

		void on_ActionParamValueBox_activated();

		void on_AParamAOButton_clicked();

		void on_TriggerHouseBox_activated();

		void on_AttachedTriggerBox_activated();

	private:
		Ui::TriggerSection *ui;

		void cleanActionList();
		void cleanEventList();
		void updateEventTypeBox();
		void updateEventParamBox();
		void updateActionTypeBox();
		void updateActionParamNameBox();
		void updateActionParamValueBox();
		void updateTriggerHouseBox();
		void updateAttachedTriggerBox();
		void resetActionLine(Action *action);
		uint16_t addTutorialText(QString text);

		QStringList getTargetStrings(TargetType type);
		TargetType getEventTargetType(int32_t ID);
		QString getTargetTypeString(int32_t ID);
		QString getTriggerNameByPosition(uint32_t pos);
		QString getTeamNameByPosition(uint32_t pos);
		QString getTagNameByPosition(uint32_t pos);
		QString getBuildingNameByKey(uint16_t key);
		QString getUnitNameByKey(uint16_t key, std::map<QString, unitContainer> &unitMap);
		uint16_t getTutorialKeyByText(QString text);
		uint16_t getUnitKeyByName(QString name, std::map<QString, unitContainer> &unitMap);
		TargetType getActionTargetType(int32_t ID, uint8_t paramID);
};

#endif // TRIGGERSECTION_H
