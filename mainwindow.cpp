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
    ui->pushButton->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑';color: rgb(255,255,255);background-color: rgb(120,196,255);"
                                    "border: none;border-radius:15px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->pushButton_2->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑';color: rgb(255,255,255);background-color: rgb(120,196,255);"
                                    "border: none;border-radius:15px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->pushButton_3->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑';color: rgb(255,255,255);background-color: rgb(120,196,255);"
                                    "border: none;border-radius:15px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->pushButton_4->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑';color: rgb(255,255,255);background-color: rgb(120,196,255);"
                                    "border: none;border-radius:15px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->mid_switch->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑';color: rgb(255,255,255);background-color: rgb(120,196,255);"
                                    "border: none;border-radius:15px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->mid_newtask->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑';color: rgb(255,255,255);background-color: rgb(120,196,255);"
                                    "border: none;border-radius:15px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->mid_refresh->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑';color: rgb(255,255,255);background-color: rgb(120,196,255);"
                                        "border: none;border-radius:15px;}"
                                        "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                        "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->label->setStyleSheet("font: 25 19pt '宋体';" //字体
                                "color: rgb(31,31,31);"		//字体颜色
                                "background-color: rgb(255, 255, 255);"); //背景颜色
    ui->label_2->setStyleSheet("font: 25 11pt '宋体';" //字体
                                        "color: rgb(31,31,31);"		//字体颜色
                                        "background-color: rgb(255, 255, 255);"); //背景颜色
    ui->ddlcounter->setStyleSheet("font: 25 11pt '宋体';" //字体
                                        "color: rgb(31,31,31);"		//字体颜色
                                        "background-color: rgb(255, 255, 255);"); //背景颜色
    ui->label_4->setStyleSheet("font: 25 11pt '宋体';" //字体
                                        "color: rgb(31,31,31);"		//字体颜色
                                        "background-color: rgb(255, 255, 255);"); //背景颜色
    ui->label_6->setStyleSheet("font: 25 11pt '宋体';" //字体
                                        "color: rgb(31,31,31);"		//字体颜色
                                        "background-color: rgb(255, 255, 255);"); //背景颜色
    ui->label_7->setStyleSheet("font: 25 11pt '宋体';" //字体
                                        "color: rgb(31,31,31);"		//字体颜色
                                        "background-color: rgb(255, 255, 255);"); //背景颜色
    ui->ddlcounter->setText("今天还有"+QString::number(1)+"个ddl,加油！");
    ui->ddlcounter->setAlignment(Qt::AlignHCenter);

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


void MainWindow::on_mid_newtask_clicked()
{
    AddTask *querytask = new AddTask(this);
    querytask->setModal(true);
    querytask->exec();
}

