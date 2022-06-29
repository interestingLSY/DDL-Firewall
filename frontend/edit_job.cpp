#include "edit_job.h"
#include "ui_edit_job.h"
#include "mainwindow.h"

#include <QDateTime>
#include <QMessageBox>

EditJob::EditJob(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditJob)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: rgb(255, 255, 255);");
    this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
}

EditJob::~EditJob()
{
    delete ui;
}

void EditJob::on_chkbox_have_ddl_stateChanged(int if_is_checked)
{
    ui->datetime_ddl->setVisible(if_is_checked);
}

void EditJob::on_chkbox_have_reminder_stateChanged(int if_is_checked)
{
    ui->datetime_reminder->setVisible(if_is_checked);
}


void EditJob::on_datetime_ddl_dateTimeChanged(const QDateTime &dateTime)
{
   ui->datetime_reminder->setDateTime(dateTime);
}


void EditJob::putTaskAddress(Task *temp)
{
    this->task=temp;
}

void EditJob::on_btn_create_clicked()
{
    if(ui->input_task_name->text().isEmpty()) {
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
        reminder.is_reminded=false;
        reminder.accurate_time = ui->datetime_reminder->dateTime();
        this->task->reminders.push_back(reminder);
    }
    this->QDialog::close();
}

