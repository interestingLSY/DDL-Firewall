#ifndef JOB_EDIT_H
#define JOB_EDIT_H

#include <QDialog>
#include "./src/classes/task.h"
namespace Ui {
class job_edit;
}

class job_edit : public QDialog
{
    Q_OBJECT

public:
    explicit job_edit(QWidget *parent = nullptr);
    ~job_edit();

public:
    Ui::job_edit *ui;
    Task *task;
    void putTaskAddress(Task* temp);
private slots:
    void on_chkbox_have_ddl_stateChanged(int arg1);
    void on_chkbox_have_reminder_stateChanged(int arg1);
    void on_datetime_ddl_dateTimeChanged(const QDateTime &dateTime);
    void on_btn_create_clicked();
};

#endif // JOB_EDIT_H
