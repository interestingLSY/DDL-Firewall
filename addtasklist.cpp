#include "addtasklist.h"
#include "ui_addtasklist.h"
#include "./src/classes/reminder.h"
#include "./src/classes/subtask.h"
#include "./src/classes/task.h"
#include "./src/classes/tasklist.h"
#include "./src/data/data.h"
#include <QDialog>
#include "errors.h"
#include <QApplication>

AddTaskList::AddTaskList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTaskList)
{
    ui->setupUi(this);
    this->setWindowTitle("新建任务列表");
    this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    this->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->remind->setText("");
}

AddTaskList::~AddTaskList()
{
    delete ui;
}

void AddTaskList::on_btn_create_clicked()
{
    if(ui->input_tasklist_name->text().isEmpty())
    {
        ui->remind->setText("任务清单名不能为空！");
//        Errors *err = new Errors(this);
//        err->setModal(true);
//        connect(this,&AddTaskList::change_error_text,err,&Errors::change_text);
//        emit change_error_text(1);
//        err->exec();
    }
    else
    {
        QString new_tasklist_name=ui->input_tasklist_name->text();
//        Tasklist tmp;
//        tmp.name=new_tasklist_name;
//        bool chk=true;
//        for(int i=0;i<data_manager.tasklists.size();i++)
//            if(data_manager.tasklists[i].name==new_tasklist_name)
//            {
//                ui->remind->setText("该任务清单名已存在！");
//                chk=false;
//                break;
//            }
//        if(chk)
//            data_manager.add_tasklist(tmp);
        this->QDialog::close();
        QApplication::processEvents();
    }
}

