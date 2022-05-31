#include "list_type2.h"
#include "ui_list_type2.h"

list_type2::list_type2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::list_type2)
{
    ui->setupUi(this);
}

list_type2::~list_type2()
{
    delete ui;
}
