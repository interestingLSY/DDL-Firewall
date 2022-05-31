#include "list_type.h"
#include "ui_list_type.h"

list_type::list_type(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::list_type)
{
    ui->setupUi(this);
}

list_type::~list_type()
{
    delete ui;
}
