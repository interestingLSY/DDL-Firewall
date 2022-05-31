#include "addtasklist.h"
#include "ui_addtasklist.h"
#include ".\src\classes\reminder.h"
#include ".\src\classes\subtask.h"
#include ".\src\classes\task.h"
#include ".\src\classes\tasklist.h"
#include <QDialog>
#include "errors.h"

AddTaskList::AddTaskList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTaskList)
{
   ui->setupUi(this);
   this->setWindowTitle("新建任务列表");
   this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
   ui->lineEdit->setStyleSheet("font: 25 13pt '微软雅黑 Light';" //字体
                                   "color: rgb(31,31,31);"		//字体颜色
                                   "padding-left:20px;"       //内边距-字体缩进
                                   "background-color: rgb(255, 255, 255);" //背景颜色
                                   "border:2px solid rgb(120,196,255);border-radius:15px;");//边框粗细-颜色-圆角设置
   ui->label->setAlignment(Qt::AlignHCenter);
   this->setStyleSheet("background-color: rgb(255, 255, 255);");
   ui->label->setStyleSheet("font: 20 14pt '微软雅黑 Light';" //字体
                            "color: rgb(31,31,31);"		//字体颜色
                            "background-color: rgb(255, 255, 255);"); //背景颜色
   ui->remind->setText("");
   ui->pushButton->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(120,196,255);"
                                   "border: none;border-radius:15px;}"
                                   "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                   "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
   ui->pushButton_2->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(120,196,255);"
                                   "border: none;border-radius:15px;}"
                                   "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                   "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed


}

AddTaskList::~AddTaskList()
{
    delete ui;
}

void AddTaskList::on_pushButton_2_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        ui->remind->setText("任务清单名不能为空！");
        ui->remind->setStyleSheet("font: 12 9pt '微软雅黑 Light';" //字体
                                  "color: rgb(255,0,0);"		//字体颜色
                                  "background-color: rgb(255, 255, 255);"); //背景颜色
        ui->remind->setAlignment(Qt::AlignHCenter);
//        Errors *err = new Errors(this);
//        err->setModal(true);
//        connect(this,&AddTaskList::change_error_text,err,&Errors::change_text);
//        emit change_error_text(1);
//        err->exec();
    }
    else
    {
        QString temp_listname=ui->lineEdit->text();
                                                                                                // 此处获取信息
        this->QDialog::close();
    }
}

