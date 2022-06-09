#ifndef ADDTASK_H
#define ADDTASK_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class AddTask;
}
QT_END_NAMESPACE

class AddTask : public QDialog
{
    Q_OBJECT

public:
    explicit AddTask(QWidget *parent = nullptr);
    ~AddTask();

private slots:
    void on_chkbox_have_ddl_stateChanged(int arg1);

    void on_chkbox_have_reminder_stateChanged(int arg1);

    void on_btn_create_clicked();

private:
    Ui::AddTask *ui;
};

#endif // ADDTASK_H
