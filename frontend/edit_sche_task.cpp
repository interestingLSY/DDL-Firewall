#include "edit_sche_task.h"
#include "ui_edit_sche_task.h"
#include "../backend/classes/task.h"
#include "mainwindow.h"

#include <QDateTime>
#include <QMessageBox>

EditScheTask::EditScheTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditScheTask)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: rgb(255, 255, 255);");
    this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
}

EditScheTask::~EditScheTask()
{
    delete ui;
}

void EditScheTask::putTaskAddress(Task *temp)
{
    this->task=temp;
}

void EditScheTask::on_btn_create_clicked()
{
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
    this->task->type = TaskType::SCHEDULED_EVENT;
    this->task->name = ui->input_task_name->text();
    this->task->comment = ui->input_comment->toPlainText();
    this->task->start_time = ui->datetime_start->dateTime();
    this->task->end_time = ui->datetime_end->dateTime();
    if (ui->chkbox_have_reminder->isChecked()) {
        this->task->reminders.clear();
        // 编辑将删除原有所有reminder
        Reminder reminder;
        reminder.type = ReminderType::BY_ACCURATE_TIME;
        reminder.accurate_time = ui->datetime_reminder->dateTime();
        this->task->reminders.push_back(reminder);
    }
    this->QDialog::close();
}


void EditScheTask::on_datetime_start_dateTimeChanged(const QDateTime &datetime)
{
    ui->datetime_end->setDateTime(datetime);
    ui->datetime_reminder->setDateTime(datetime);
}



void EditScheTask::on_chkbox_have_reminder_stateChanged(int is_checked)
{
    ui->datetime_reminder->setVisible(is_checked);
}

