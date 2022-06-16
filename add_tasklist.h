#ifndef ADDTASKLIST_H
#define ADDTASKLIST_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class AddTaskList;
}
QT_END_NAMESPACE

class AddTaskList : public QDialog
{
    Q_OBJECT

public:
    explicit AddTaskList(QWidget *parent = nullptr);
    ~AddTaskList();

private slots:
    void on_btn_create_clicked();
signals:
    void change_error_text(int);
public:
    Ui::AddTaskList *ui;
};

#endif // ADDTASKLIST_H
