#include "edit_reminder.h"
#include "ui_edit_reminder.h"

#include <QDateTime>
#include <QMessageBox>

edit_reminder::edit_reminder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_reminder)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: rgb(255, 255, 255);");
    this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
}

edit_reminder::~edit_reminder()
{
    delete ui;
}

void edit_reminder::putReminderAddress(Reminder* reminder)
{
    this->reminder=reminder;
}

void edit_reminder::on_btn_confirm_clicked()
{
    if(ui->reminder_datetime->dateTime()<QDateTime::currentDateTime())
    {
        // TO DO 编写error类优化界面
        QMessageBox message_box;
        message_box.critical(nullptr, "Error", "提醒时间已经过期！");
        return;
    }
    this->reminder->accurate_time = ui->reminder_datetime->dateTime();
    this->reminder->is_reminded = false;

    this->QDialog::close();
}

