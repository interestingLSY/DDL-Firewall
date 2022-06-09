#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "./src/classes/reminder.h"
#include "./src/classes/subtask.h"
#include "./src/classes/task.h"
#include "./src/classes/tasklist.h"
#include <QDialog>
#include <QWidget>
#include "addtasklist.h"
#include "errors.h"
#include "list_type.h"
#include "calendar_type.h"
#include "addtask.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    this->setStyleSheet("background-color: rgb(255, 255, 255);");
    
#define BUTTON_STYLE "QPushButton{font: 25 14pt '微软雅黑';color: rgb(255,255,255);background-color: rgb(120,196,255);" \
                    "border: none;border-radius:15px;}" \
                    "QPushButton:hover{background-color: rgb(22,218,208);}" \
                    "QPushButton:pressed{background-color: rgb(17,171,164);}"
    this->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->btn_left_create_tasklist->setStyleSheet(BUTTON_STYLE);
    ui->btn_right_done->setStyleSheet(BUTTON_STYLE);
    ui->btn_right_edit_task->setStyleSheet(BUTTON_STYLE);
    ui->btn_right_del_task->setStyleSheet(BUTTON_STYLE);
    ui->btn_mid_switch->setStyleSheet(BUTTON_STYLE);
    ui->btn_mid_create_task->setStyleSheet(BUTTON_STYLE);
    ui->btn_mid_refresh->setStyleSheet(BUTTON_STYLE);
#undef BUTTON_STYLE

    ui->lab_ddlcounter->setText("今天还有"+QString::number(1)+"个ddl,加油！");
    ui->lab_ddlcounter->setAlignment(Qt::AlignHCenter);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_left_create_tasklist_clicked()
{
    AddTaskList *querylists = new AddTaskList(this);

    querylists->setModal(true);
    querylists->exec();
}

int type=0,backtype=0; //视图类型

void MainWindow::on_btn_mid_switch_clicked() // 切换视图
{
    if(type==0||type==2)
    {
        backtype=type;
        type=1;
        ui->stackedWidget->setCurrentIndex(1);
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(backtype);
        type=backtype;
    }


}


void MainWindow::on_btn_mid_create_task_clicked()
{
    AddTask *querytask = new AddTask(this);
    querytask->setModal(true);
    querytask->exec();
}

