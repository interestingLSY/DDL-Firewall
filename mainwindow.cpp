#include "mainwindow.h"
#include "ui_mainwindow.h"
#include ".\src\classes\reminder.h"
#include ".\src\classes\subtask.h"
#include ".\src\classes\task.h"
#include ".\src\classes\tasklist.h"
#include <QDialog>
#include <QWidget>
#include "addtasklist.h"
#include "errors.h"
#include "list_type.h"
#include "calendar_type.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    this->setStyleSheet("background-color: rgb(255, 255, 255);");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    AddTaskList *querylists = new AddTaskList(this);

    querylists->setModal(true);
    querylists->exec();
}

int type=0,backtype=0; //视图类型

void MainWindow::on_mid_switch_clicked() // 切换视图
{
    if(type==0||type==1)
    {
        backtype=type;
        type=2;
        ui->stackedWidget->setCurrentIndex(2);
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(backtype);
        type=backtype;
    }


}

