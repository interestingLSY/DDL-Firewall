#include "addtask.h"
#include "ui_addtask.h"

AddTask::AddTask(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddTask)
{
	ui->setupUi(this);
	this->setStyleSheet("background-color: rgb(255, 255, 255);");
	this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);

	ui->datetime_ddl->setVisible(false);
	ui->datetime_reminder->setVisible(false);
}

AddTask::~AddTask()
{
	delete ui;
}


void AddTask::on_chkbox_have_ddl_stateChanged(int arg1) {
	if (arg1) {
		ui->datetime_ddl->setVisible(true);
	} else {
		ui->datetime_ddl->setVisible(false);
	}
}


void AddTask::on_chkbox_have_reminder_stateChanged(int arg1)
{
	if (arg1) {
		ui->datetime_reminder->setVisible(true);
	} else {
		ui->datetime_reminder->setVisible(false);
	}
}


void AddTask::on_btn_create_clicked()
{
	if(ui->input_task_name->text().isEmpty())
	{
//        err->setModal(true);
//        connect(this,&AddTaskList::change_error_text,err,&Errors::change_text);
//        emit change_error_text(1);
//        err->exec();
	}
	else
	{
		QString temp_taskname = ui->input_task_name->text();
		this->QDialog::close();
	}
}

