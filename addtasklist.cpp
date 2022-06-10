#include <QDialog>
#include <QMessageBox>

#include "./src/classes/reminder.h"
#include "./src/classes/subtask.h"
#include "./src/classes/task.h"
#include "./src/classes/tasklist.h"
#include "./src/data/data.h"

#include "addtasklist.h"
#include "ui_addtasklist.h"
#include "errors.h"

AddTaskList::AddTaskList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTaskList)
{
    ui->setupUi(this);
    this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    this->setStyleSheet("background-color: rgb(255, 255, 255);");
}

AddTaskList::~AddTaskList()
{
    delete ui;
}

void AddTaskList::on_btn_create_clicked()
{
    if(ui->input_tasklist_name->text().isEmpty()) {
        QMessageBox message_box;
		message_box.critical(nullptr, "Error", "事务列表名不能为空");
		return;
    }
    QString new_tasklist_name = ui->input_tasklist_name->text();
    Tasklist new_tasklist;
    new_tasklist.name = new_tasklist_name;
    data_manager.add_tasklist(new_tasklist);
    this->QDialog::close();
}

