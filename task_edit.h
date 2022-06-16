#ifndef TASK_EDIT_H
#define TASK_EDIT_H

#include <QDialog>
#include <QDateTime>

#include "./src/classes/task.h"
namespace Ui {
class task_edit;
}

class task_edit : public QDialog
{
    Q_OBJECT

public:
    explicit task_edit(QWidget *parent = nullptr);
    ~task_edit();

public:
    Ui::task_edit *ui;
    Task *task;
    void putTaskAddress(Task* temp);
private slots:
    void on_btn_create_clicked();
    void on_datetime_start_dateChanged(const QDateTime &datetime);
    void on_chkbox_have_reminder_stateChanged(int arg1);
};

#endif // TASK_EDIT_H
