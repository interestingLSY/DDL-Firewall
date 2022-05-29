#include "addtask.h"
#include "ui_addtask.h"

AddTask::AddTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTask)
{
    ui->setupUi(this);
    for(int i=2022;i<=2099;i++)
        ui->comboBoxYear->addItem(QString::number(i));
    ui->comboBoxYear->setCurrentIndex(0);
    for(int i=1;i<=12;i++)
        ui->comboBoxMonth->addItem(QString::number(i));
    ui->comboBoxMonth->setCurrentIndex(0);
    for(int i=1;i<=31;i++)
        ui->comboBoxDay->addItem(QString::number(i));
    ui->comboBoxDay->setCurrentIndex(0);
    for(int i=0;i<=23;i++)
        ui->comboBoxHour->addItem(QString::number(i));
    ui->comboBoxHour->setCurrentIndex(7);
    for(int i=0;i<=59;i++)
        ui->comboBoxMinute->addItem(QString::number(i));
    ui->comboBoxMinute->setCurrentIndex(0);
    ui->comboBoxYear->setVisible(false);
    ui->comboBoxMonth->setVisible(false);
    ui->comboBoxHour->setVisible(false);
    ui->comboBoxDay->setVisible(false);
    ui->comboBoxMinute->setVisible(false);
    ui->year->setVisible(false);
    ui->month->setVisible(false);
    ui->day->setVisible(false);
    ui->minute->setVisible(false);
    ui->hour->setVisible(false);
    ui->remind->setText("");
    ui->lineEdit->setStyleSheet("font: 25 13pt '微软雅黑';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:20px;"       //内边距-字体缩进
                                    "background-color: rgb(255, 255, 255);" //背景颜色
                                    "border:2px solid rgb(120,196,255);border-radius:15px;");//边框粗细-颜色-圆角设置
    ui->plainTextEdit->setStyleSheet("font: 25 11pt '宋体';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:20px;"       //内边距-字体缩进
                                    "background-color: rgb(255, 255, 255);" //背景颜色
                                    "border:2px solid rgb(120,196,255);border-radius:15px;");//边框粗细-颜色-圆角设置
    ui->checkBoxSubtask->setStyleSheet("font: 25 11pt '宋体';" //字体
                                       "color: rgb(31,31,31);"		//字体颜色
                                       "background-color: rgb(255, 255, 255);"); //背景颜色
    ui->checkBoxDate->setStyleSheet("font: 25 11pt '宋体';" //字体
                                       "color: rgb(31,31,31);"		//字体颜色
                                       "background-color: rgb(255, 255, 255);"); //背景颜色
    ui->checkBoxTime->setStyleSheet("font: 25 11pt '宋体';" //字体
                                       "color: rgb(31,31,31);"		//字体颜色
                                       "background-color: rgb(255, 255, 255);"); //背景颜色
    ui->year->setStyleSheet("font: 25 11pt '宋体';" //字体
                                       "color: rgb(31,31,31);"		//字体颜色
                                       "background-color: rgb(255, 255, 255);"); //背景颜色
    ui->month->setStyleSheet("font: 25 11pt '宋体';" //字体
                                       "color: rgb(31,31,31);"		//字体颜色
                                       "background-color: rgb(255, 255, 255);"); //背景颜色
    ui->day->setStyleSheet("font: 25 11pt '宋体';" //字体
                                       "color: rgb(31,31,31);"		//字体颜色
                                       "background-color: rgb(255, 255, 255);"); //背景颜色
    ui->hour->setStyleSheet("font: 25 11pt '宋体';" //字体
                                       "color: rgb(31,31,31);"		//字体颜色
                                       "background-color: rgb(255, 255, 255);"); //背景颜色
    ui->minute->setStyleSheet("font: 25 11pt '宋体';" //字体
                                       "color: rgb(31,31,31);"		//字体颜色
                                       "background-color: rgb(255, 255, 255);"); //背景颜色
    ui->label_taskname->setAlignment(Qt::AlignHCenter);
    ui->label_taskdetail->setAlignment(Qt::AlignHCenter);
    this->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->label_taskname->setStyleSheet("font: 20 18pt '宋体';" //字体
                             "color: rgb(31,31,31);"		//字体颜色
                             "background-color: rgb(255, 255, 255);"); //背景颜色
    ui->label_taskdetail->setStyleSheet("font: 20 18pt '宋体';" //字体
                             "color: rgb(31,31,31);"		//字体颜色
                             "background-color: rgb(255, 255, 255);"); //背景颜色
    this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    ui->pushButton->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑';color: rgb(255,255,255);background-color: rgb(120,196,255);"
                                    "border: none;border-radius:15px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->pushButton_2->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑';color: rgb(255,255,255);background-color: rgb(120,196,255);"
                                    "border: none;border-radius:15px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
}

AddTask::~AddTask()
{
    delete ui;
}


void AddTask::on_checkBoxDate_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->comboBoxYear->setVisible(true);
        ui->comboBoxMonth->setVisible(true);
        ui->comboBoxDay->setVisible(true);
        ui->year->setVisible(true);
        ui->month->setVisible(true);
        ui->day->setVisible(true);
    }
    else
    {
        ui->comboBoxYear->setVisible(false);
        ui->comboBoxMonth->setVisible(false);
        ui->comboBoxDay->setVisible(false);
        ui->year->setVisible(false);
        ui->month->setVisible(false);
        ui->day->setVisible(false);
    }
}


void AddTask::on_checkBoxTime_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->comboBoxHour->setVisible(true);
        ui->comboBoxMinute->setVisible(true);
        ui->hour->setVisible(true);
        ui->minute->setVisible(true);
    }
    else
    {
        ui->comboBoxHour->setVisible(false);
        ui->comboBoxMinute->setVisible(false);
        ui->hour->setVisible(false);
        ui->minute->setVisible(false);

    }
}


void AddTask::on_checkBoxSubtask_stateChanged(int arg1)
{
    // do something
}


void AddTask::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        ui->remind->setText("任务名不能为空！");
        ui->remind->setStyleSheet("font: 12 9pt '宋体';" //字体
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
        QString temp_taskname=ui->lineEdit->text();
                                                                                                // 此处获取信息
        this->QDialog::close();
    }
}

