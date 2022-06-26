#include "remind_acurator.h"
#include "ui_remind_acurator.h"

#include <QScreen>

remind_acurator::remind_acurator(Task* task, Reminder* reminder, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::remind_acurator)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: rgb(255, 255, 255);");
    this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
//    TODO 放在右下角
//    QScreen * screen = QGuiApplication::primaryScreen();
//    const QRect desk_rect = screen->availableGeometry();

    ui->content->setText("提醒：不要忘记完成任务 "+task->name+" 呀！");
}

remind_acurator::~remind_acurator()
{
    delete ui;
}