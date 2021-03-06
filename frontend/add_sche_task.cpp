#include <QDateTime>
#include <QMessageBox>

#include "../backend/classes/tasklist.h"
#include "../backend/data/data.h"

#include "add_sche_task.h"
#include "ui_add_sche_task.h"
#include "mainwindow.h"

AddScheTask::AddScheTask(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddScheTask)
{
	ui->setupUi(this);
	this->setStyleSheet("background-color: rgb(255, 255, 255);");
	this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);

	ui->datetime_start->setDateTime(QDateTime::currentDateTime());
	ui->datetime_end->setDateTime(QDateTime::currentDateTime());
	ui->datetime_reminder->setDateTime(QDateTime::currentDateTime());

	ui->datetime_reminder->setVisible(false);
}

AddScheTask::~AddScheTask()
{
	delete ui;
}


void AddScheTask::on_chkbox_have_reminder_stateChanged(int is_checked) {
	ui->datetime_reminder->setVisible(is_checked);
}

void AddScheTask::on_datetime_start_dateTimeChanged(const QDateTime &datetime) {
	ui->datetime_end->setDateTime(datetime);
	ui->datetime_reminder->setDateTime(datetime);
}

void AddScheTask::on_btn_create_clicked() {
	if (ui->input_task_name->text().isEmpty()) {
		QMessageBox message_box;
		message_box.critical(nullptr, "Error", "事务名不能为空");
		return;
	}
    if(ui->input_task_name->text().length()>20) {
        QMessageBox message_box;
        message_box.critical(nullptr, "DDL Firewall", "事务名过长！请输入不超过20个字！");
        return;
    }
    if(ui->input_comment->toPlainText().length()>100) {
        QMessageBox message_box;
        message_box.critical(nullptr, "DDL Firewall", "事务描述过长！请输入不超过100个字！");
        return;
    }
	if (ui->datetime_start->dateTime() > ui->datetime_end->dateTime()) {
		QMessageBox message_box;
		message_box.critical(nullptr, "Error", "事务的开始时间不能晚于结束时间");
		return;
	}
	Task new_task;
	new_task.type = TaskType::SCHEDULED_EVENT;
	new_task.name = ui->input_task_name->text();
    new_task.comment = ui->input_comment->toPlainText();
	new_task.start_time = ui->datetime_start->dateTime();
	new_task.end_time = ui->datetime_end->dateTime();
	if (ui->chkbox_have_reminder->isChecked()) {
		Reminder reminder;
		reminder.type = ReminderType::BY_ACCURATE_TIME;
		reminder.accurate_time = ui->datetime_reminder->dateTime();
        reminder.is_reminded=false;
		new_task.reminders.push_back(reminder);
	}
	MainWindow* parent = dynamic_cast<MainWindow*>(this->parentWidget());
	Q_ASSERT(parent != nullptr);
	Q_ASSERT(parent->selected_tasklist_layout_item != nullptr);
	Q_ASSERT(!parent->selected_tasklist_layout_item->is_virtual);
	parent->selected_tasklist_layout_item->tasklist->add_task(new_task);
	this->QDialog::close();
}

