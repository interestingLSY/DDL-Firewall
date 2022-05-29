#include "calendar_type.h"
#include "ui_calendar_type.h"

calendar_type::calendar_type(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::calendar_type)
{
    ui->setupUi(this);
}

calendar_type::~calendar_type()
{
    delete ui;
}
