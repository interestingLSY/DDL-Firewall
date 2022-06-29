#ifndef EDIT_JOB_H
#define EDIT_JOB_H

#include <QDialog>
#include "../backend/classes/task.h"
namespace Ui {
class EditJob;
}

class EditJob : public QDialog
{
    Q_OBJECT

public:
    explicit EditJob(QWidget *parent = nullptr);
    ~EditJob();

public:
    Ui::EditJob *ui;
    Task *task;
    void putTaskAddress(Task* temp);
private slots:
    void on_chkbox_have_ddl_stateChanged(int arg1);
    void on_chkbox_have_reminder_stateChanged(int arg1);
    void on_datetime_ddl_dateTimeChanged(const QDateTime &dateTime);
    void on_btn_create_clicked();
};

#endif // EDIT_JOB_H
