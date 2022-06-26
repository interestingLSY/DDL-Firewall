#include "mainwindow.h"
#include "reminder_detector.h"
#include "remind_acurator.h"

#include <QMutex>
#include <QDebug>
#include <QDateTime>
#include <QObject>


void reminder_detector::run()
{

    // 目前full of bugs，车祸现场
    /*
    QMutex mutex;
    while(true)
    {
            qDebug()<<if_need_remind<<endl;
            qDebug()<<next_reminder->accurate_time<<endl;

        if(if_need_remind && QDateTime::currentDateTime()>=next_reminder->accurate_time)
        {
            //弹窗提醒
            //把Task名传递给mainwindow
            this->Address_mainwindow->set_next_task(this->next_task_to_remind);
            connect(this,&reminder_detector::remind_now,Address_mainwindow,&MainWindow::create_remind_acurator);
            emit remind_now();
            next_reminder->if_reminded=true;
            int cnt_all=0;
            if_need_remind=false;
            for (Tasklist &tasklist : data_manager.tasklists)
                for (Task &task : tasklist.tasks)
                    for(Reminder &reminder : task.reminders)
                    {
                        if(task.is_finished==false && reminder.if_reminded == false)
                        {
                            if(cnt_all==0||next_reminder->accurate_time>task.end_time)
                            {
                                if_need_remind = true ;
                                cnt_all++;
                                next_reminder = &reminder ;
                                next_task_to_remind = &task ;
                            }
                        }
                    }
        }
        QThread::sleep(1);
    }
    */
}


void reminder_detector::set_task(Task* task)
{
    this->next_task_to_remind=task;
}

void reminder_detector::set_reminder(Reminder* reminder)
{
    this->next_reminder=reminder;
}
void reminder_detector::set_flag(bool flag)
{
    this->if_need_remind=flag;
}
