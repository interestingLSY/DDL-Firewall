#include "job_edit.h"
#include "ui_job_edit.h"

job_edit::job_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::job_edit)
{
    ui->setupUi(this);
}

job_edit::~job_edit()
{
    delete ui;
}
