#include <QDateTime>
#include <QMessageBox>

#include "./src/classes/tasklist.h"
#include "./src/data/data.h"

#include "add_job.h"
#include "ui_add_job.h"
#include "mainwindow.h"

AddJob::AddJob(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddJob)
{
	ui->setupUi(this);
	this->setStyleSheet("background-color: rgb(255, 255, 255);");
	this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);

	ui->datetime_ddl->setDateTime(QDateTime::currentDateTime());
	ui->datetime_reminder->setDateTime(QDateTime::currentDateTime());

	ui->datetime_ddl->setVisible(false);
	ui->datetime_reminder->setVisible(false);
}

AddJob::~AddJob()
{
	delete ui;
}


void AddJob::on_chkbox_have_ddl_stateChanged(int is_checkced) {
	ui->datetime_ddl->setVisible(is_checkced);
}


void AddJob::on_chkbox_have_reminder_stateChanged(int is_checked) {
	ui->datetime_reminder->setVisible(is_checked);
}

void AddJob::on_datetime_ddl_dateTimeChanged(const QDateTime &datetime) {
	ui->datetime_reminder->setDateTime(datetime);
}

void AddJob::on_btn_create_clicked() {
	if(ui->input_task_name->text().isEmpty()) {
		QMessageBox message_box;
		message_box.critical(nullptr, "Error", "事务名不能为空");
		return;
	}
	Task new_task;
	new_task.type = TaskType::JOB;
	new_task.name = ui->input_task_name->text();
    new_task.comment = ui->input_comment->toPlainText();
	if (ui->chkbox_have_ddl->isChecked()) {
		new_task.end_time = ui->datetime_ddl->dateTime();
	}
	if (ui->chkbox_have_reminder->isChecked()) {
		Reminder reminder;
		reminder.type = ReminderType::BY_ACCURATE_TIME;
		reminder.accurate_time = ui->datetime_reminder->dateTime();
		new_task.reminders.push_back(reminder);
	}
	MainWindow* parent = dynamic_cast<MainWindow*>(this->parentWidget());
	Q_ASSERT(parent != nullptr);
	Q_ASSERT(parent->selected_tasklist_layout_item != nullptr);
	Q_ASSERT(!parent->selected_tasklist_layout_item->is_virtual);
	parent->selected_tasklist_layout_item->tasklist->add_task(new_task);
	this->QDialog::close();
}
