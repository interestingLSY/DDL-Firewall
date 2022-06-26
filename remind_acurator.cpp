#include "remind_acurator.h"
#include "ui_remind_acurator.h"

#include <QScreen>

remind_acurator::remind_acurator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::remind_acurator)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: rgb(255, 255, 255);");
    this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
//    打算放在右下角
//    QScreen * screen = QGuiApplication::primaryScreen();
//    const QRect desk_rect = screen->availableGeometry();

    this->setFixedSize(310,210);
    ui->content->setText("提醒：不要忘记完成任务 "+this->next_task->name+" 呀！");
}

remind_acurator::~remind_acurator()
{
    delete ui;
}

void remind_acurator::set_next_task(Task *task)
{
    this->next_task=task;
    //qDebug()<<this->next_task->name<<endl;
}
