#include <QDialog>
#include <QMessageBox>
#include <QDateTime>

#include "../backend/classes/reminder.h"
#include "../backend/classes/subtask.h"
#include "../backend/classes/task.h"
#include "../backend/classes/tasklist.h"
#include "../backend/data/data.h"

#include "add_reminder.h"
#include "ui_add_reminder.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

add_reminder::add_reminder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_reminder)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: rgb(255, 255, 255);");
    this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);

    ui->reminder_datetime->setDateTime(QDateTime::currentDateTime());
}

add_reminder::~add_reminder()
{
    delete ui;
}

void add_reminder::on_btn_create_clicked()
{
    if(ui->reminder_datetime->dateTime()<QDateTime::currentDateTime())
    {
        QMessageBox message_box;
        message_box.critical(nullptr, "DDL Firewall", "该提醒时间已经过期！");
        return;
    }
    QDateTime new_reminder_time = ui->reminder_datetime->dateTime();
    Reminder new_reminder;
    new_reminder.type=ReminderType::BY_ACCURATE_TIME;
    new_reminder.accurate_time = new_reminder_time;
    new_reminder.is_reminded = false;
    MainWindow* mainwindow = dynamic_cast<MainWindow*>(this->parentWidget());
    Q_ASSERT(mainwindow != nullptr);
    Q_ASSERT(mainwindow->selected_task_layout_item != nullptr);
    mainwindow->selected_task_layout_item->task->add_reminder(new_reminder);
    this->QDialog::close();
}

