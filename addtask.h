#ifndef ADDTASK_H
#define ADDTASK_H

#include <QDialog>

namespace Ui {
class AddTask;
}

class AddTask : public QDialog
{
    Q_OBJECT

public:
    explicit AddTask(QWidget *parent = nullptr);
    ~AddTask();

private slots:
    void on_checkBoxSubtask_stateChanged(int arg1);

    void on_checkBoxDate_stateChanged(int arg1);

    void on_checkBoxTime_stateChanged(int arg1);

    void on_pushButton_clicked();

private:
    Ui::AddTask *ui;
};

#endif // ADDTASK_H