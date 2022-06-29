#include "errors.h"
#include "ui_errors.h"
#include "../backend/classes/reminder.h"
#include "../backend/classes/subtask.h"
#include "../backend/classes/task.h"
#include "../backend/classes/tasklist.h"
#include "add_tasklist.h"


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
