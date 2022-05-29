#ifndef ADDTASKLIST_H
#define ADDTASKLIST_H

#include <QDialog>

namespace Ui {
class AddTaskList;
}

class AddTaskList : public QDialog
{
    Q_OBJECT

public:
    explicit AddTaskList(QWidget *parent = nullptr);
    ~AddTaskList();

private slots:
    void on_pushButton_2_clicked();
signals:
    void change_error_text(int);
public:
    Ui::AddTaskList *ui;
};

#endif // ADDTASKLIST_H
