#ifndef EDIT_SUBTASK_H
#define EDIT_SUBTASK_H

#include "../backend/classes/subtask.h"
#include "mainwindow.h"

#include <QDialog>

namespace Ui {
class edit_subtask;
}

class edit_subtask : public QDialog
{
    Q_OBJECT

public:
    explicit edit_subtask(QWidget *parent = nullptr);
    ~edit_subtask();
    Subtask *subtask;
    void putSubtaskAddress(Subtask* temp);

private slots:
    void on_btn_confirm_clicked();

public:
    Ui::edit_subtask *ui;
};

#endif // EDIT_SUBTASK_H
