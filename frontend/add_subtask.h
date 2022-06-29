#ifndef ADD_SUBTASK_H
#define ADD_SUBTASK_H

#include <QDialog>

namespace Ui {
class add_subtask;
}

class add_subtask : public QDialog
{
    Q_OBJECT

public:
    explicit add_subtask(QWidget *parent = nullptr);
    ~add_subtask();

private slots:
    void on_btn_create_clicked();

private:
    Ui::add_subtask *ui;
};

#endif // ADD_SUBTASK_H
