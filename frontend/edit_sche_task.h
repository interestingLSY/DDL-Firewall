#ifndef EDIT_SCHE_TASK_H
#define EDIT_SCHE_TASK_H

#include <QDialog>
#include <QDateTime>

#include "../backend/classes/task.h"
namespace Ui {
class EditScheTask;
}

class EditScheTask : public QDialog
{
    Q_OBJECT

public:
    explicit EditScheTask(QWidget *parent = nullptr);
    ~EditScheTask();

public:
    Ui::EditScheTask *ui;
    Task *task;
    void putTaskAddress(Task* temp);
private slots:
    void on_btn_create_clicked();
    void on_datetime_start_dateTimeChanged(const QDateTime &datetime);
    void on_chkbox_have_reminder_stateChanged(int arg1);
};

#endif // EDIT_SCHE_TASK_H
