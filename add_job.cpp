#include <QDateTime>

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


void AddJob::on_chkbox_have_ddl_stateChanged(int arg1) {
	if (arg1) {
		ui->datetime_ddl->setVisible(true);
	} else {
		ui->datetime_ddl->setVisible(false);
	}
}


void AddJob::on_chkbox_have_reminder_stateChanged(int arg1) {
	if (arg1) {
		ui->datetime_reminder->setVisible(true);
	} else {
		ui->datetime_reminder->setVisible(false);
	}
}

void AddJob::on_datetime_ddl_dateTimeChanged(const QDateTime &datetime) {
	ui->datetime_reminder->setDateTime(datetime);
}

void AddJob::on_btn_create_clicked() {
	if(ui->input_task_name->text().isEmpty()) {
//        err->setModal(true);
//        connect(this,&AddTaskList::change_error_text,err,&Errors::change_text);
//        emit change_error_text(1);
//        err->exec();
	} else {
		Task new_task;
		new_task.type = TaskType::JOB;
		new_task.name = ui->input_task_name->text();
		if (ui->chkbox_have_ddl->isChecked()) {
			new_task.end_time = ui->datetime_ddl->dateTime();
		}
		if (ui->chkbox_have_reminder->isChecked()) {
			Reminder reminder;
			reminder.type = ReminderType::BY_ACCURATE_TIME;
			new_task.reminders.push_back(reminder);
		}
		MainWindow* parent = dynamic_cast<MainWindow*>(this->parentWidget());
		Q_ASSERT(parent != nullptr);
		Q_ASSERT(parent->selected_tasklist_layout_item != nullptr);
		Q_ASSERT(!parent->selected_tasklist_layout_item->is_virtual);
		parent->selected_tasklist_layout_item->tasklist->add_task(new_task);
		this->QDialog::close();
	}
}
