#ifndef REMINDER_DETECTOR_H
#define REMINDER_DETECTOR_H

#include <QThread>

#include "./src/classes/reminder.h"
#include "./src/classes/subtask.h"
#include "./src/classes/task.h"
#include "./src/classes/tasklist.h"
#include "./src/data/data.h"
#include "mainwindow.h"
class reminder_detector : public QThread
{
    Q_OBJECT
public:
    Task *next_task_to_remind;
    Reminder *next_reminder;
    bool if_need_remind;
    MainWindow *Address_mainwindow;
    void set_task(Task* task);
    void set_reminder(Reminder* reminder);
    void set_flag(bool flag);

protected:
    virtual void run();
signals:
    void remind_now();
};

#endif // REMINDER_DETECTOR_H
