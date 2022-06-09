#include "errors.h"
#include "ui_errors.h"
#include "./src/classes/reminder.h"
#include "./src/classes/subtask.h"
#include "./src/classes/task.h"
#include "./src/classes/tasklist.h"
#include "addtasklist.h"


Errors::Errors(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Errors)
{
    this->setModal(true);
    ui->setupUi(this);
}

Errors::~Errors()
{
    delete ui;
}

void Errors::change_text()
{
     ui->remind_text->setText("任务清单名不能为空！");
}
