#include "edit_subtask.h"
#include "ui_edit_subtask.h"

#include <QDateTime>
#include <QMessageBox>

edit_subtask::edit_subtask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_subtask)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: rgb(255, 255, 255);");
    this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);

}

edit_subtask::~edit_subtask()
{
    delete ui;
}

void edit_subtask::putSubtaskAddress(Subtask* subtask)
{
    this->subtask=subtask;
}


void edit_subtask::on_btn_confirm_clicked()
{
    if(ui->input_subtask_name->text().isEmpty()) {
        QMessageBox message_box;
        message_box.critical(nullptr, "Error", "子任务名不能为空");
        return;
    }
    this->subtask->name=ui->input_subtask_name->text();

    this->QDialog::close();
}

