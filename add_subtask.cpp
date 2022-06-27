#include <QDialog>
#include <QMessageBox>

#include "./src/classes/reminder.h"
#include "./src/classes/subtask.h"
#include "./src/classes/task.h"
#include "./src/classes/tasklist.h"
#include "./src/data/data.h"
#include "add_subtask.h"
#include "ui_add_subtask.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

add_subtask::add_subtask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_subtask)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: rgb(255, 255, 255);");
    this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
}

add_subtask::~add_subtask()
{
    delete ui;
}

void add_subtask::on_btn_create_clicked()
{
    if(ui->input_subtask_name->text().isEmpty())
    {
        QMessageBox message_box;
        message_box.critical(nullptr, "Error", "子任务名不能为空！");
        return;
    }
    if(ui->input_subtask_name->text().length()>12) {
        QMessageBox message_box;
        message_box.critical(nullptr, "DDL Firewall", "子任务名过长！请输入不超过12个字！");
        return;
    }

    QString new_subtask_name = ui->input_subtask_name->text();
    Subtask new_subtask;
    new_subtask.name = new_subtask_name;
    new_subtask.is_finished=false;
    MainWindow* mainwindow = dynamic_cast<MainWindow*>(this->parentWidget());
    Q_ASSERT(mainwindow != nullptr);
    Q_ASSERT(mainwindow->selected_task_layout_item != nullptr);
    mainwindow->selected_task_layout_item->task->add_subtask(new_subtask);
    this->QDialog::close();
}

