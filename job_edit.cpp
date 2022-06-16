#include "job_edit.h"
#include "ui_job_edit.h"
#include "mainwindow.h"

#include <QDateTime>
#include <QMessageBox>

job_edit::job_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::job_edit)
{
    ui->setupUi(this);
}

job_edit::~job_edit()
{
    delete ui;
}

void job_edit::on_chkbox_have_ddl_stateChanged(int if_is_checked)
{
    ui->datetime_ddl->setVisible(if_is_checked);
}

void job_edit::on_chkbox_have_reminder_stateChanged(int if_is_checked)
{
    ui->datetime_reminder->setVisible(if_is_checked);
}


void job_edit::on_datetime_ddl_dateTimeChanged(const QDateTime &dateTime)
{
   ui->datetime_reminder->setDateTime(dateTime);
}


void job_edit::putTaskAddress(Task *temp)
{
    this->task=temp;
}

void job_edit::on_btn_create_clicked()
{
    if(ui->input_task_name->text().isEmpty()) {
        QMessageBox message_box;
        message_box.critical(nullptr, "Error", "事务名不能为空");
        return;
    }
    this->task->type = TaskType::JOB;
    this->task->name = ui->input_task_name->text();
    this->task->comment = ui->input_comment->toPlainText();
    if (ui->chkbox_have_ddl->isChecked()) {
        this->task->end_time = ui->datetime_ddl->dateTime();
    }
    if (ui->chkbox_have_reminder->isChecked()) {
        this->task->reminders.clear();
        Reminder reminder;
        reminder.type = ReminderType::BY_ACCURATE_TIME;
        this->task->reminders.push_back(reminder);
    }
    this->QDialog::close();
}

