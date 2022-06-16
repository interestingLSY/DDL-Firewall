#include <QDialog>
#include <QWidget>
#include <QMessageBox>
#include <QBoxLayout>
#include <QtGlobal>
#include <QDateTime>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addtasklist.h"
#include "errors.h"
#include "list_type.h"
#include "calendar_type.h"
#include "add_job.h"
#include "add_sche_task.h"
#include "ui_task_edit.h"
#include "task_edit.h"
#include "job_edit.h"
#include "ui_job_edit.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setStyleSheet("background-color: rgb(255, 255, 255);");
    
#define BUTTON_STYLE "QPushButton{font: 25 12pt '微软雅黑';color: rgb(255,255,255);background-color: rgb(120,196,255);" \
                    "border: none;border-radius:5px;}" \
                    "QPushButton:hover{background-color: rgb(22,218,208);}" \
                    "QPushButton:pressed{background-color: rgb(17,171,164);}"
    this->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->btn_create_tasklist->setStyleSheet(BUTTON_STYLE);
    ui->btn_edit_task->setStyleSheet(BUTTON_STYLE);
    ui->btn_del_task->setStyleSheet(BUTTON_STYLE);
    ui->btn_add_job->setStyleSheet(BUTTON_STYLE);
    ui->btn_add_sche_task->setStyleSheet(BUTTON_STYLE);
#undef BUTTON_STYLE

    ui->lab_ddlcounter->setText("今天还有 " + QString::number(1) + " 个ddl,加油！");

    this->selected_task_layout_item = nullptr;
    this->selected_tasklist_layout_item = nullptr;

    this->redraw_left();
    this->redraw_middle();
    this->redraw_right();
}

MainWindow::~MainWindow() {
    delete ui;
}

// 创建一个新的事务列表
void MainWindow::on_btn_create_tasklist_clicked() {
    AddTaskList *querylists = new AddTaskList(this);
    querylists->setModal(true);
    querylists->exec();
    this->redraw_left();
}

// 创建一个新的任务
void MainWindow::on_btn_add_job_clicked() {
    AddJob *querytask = new AddJob(this);
    querytask->setModal(true);
    querytask->exec();

    // 这里需要 redraw_left，因为“全部事务”，“未完成事务”中的内容可能会出现变化
    this->redraw_left();
    this->redraw_middle();
}

// 创建一个新的定时事务
void MainWindow::on_btn_add_sche_task_clicked() {
    AddScheTask *querytask = new AddScheTask(this);
    querytask->setModal(true);
    querytask->exec();

    this->redraw_left();
    this->redraw_middle();
}

// 删除当前的事务清单
void MainWindow::on_btn_del_tasklist_clicked() {
    Q_ASSERT(this->selected_tasklist_layout_item);
    Q_ASSERT(!this->selected_tasklist_layout_item->is_virtual);
    Tasklist* selected_tasklist = this->selected_tasklist_layout_item->tasklist;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认", "确定要删除事务清单 "+selected_tasklist->name + "？\n这将会删除这个清单内的所有事务！",
                                QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        data_manager.del_tasklisk(selected_tasklist->uuid);
        this->selected_tasklist_layout_item = nullptr;
        this->selected_task_layout_item = nullptr;
        this->redraw_left();
        this->redraw_middle();
        this->redraw_right();
    }
}

// 删除当前的事务
void MainWindow::on_btn_del_task_clicked() {
    Q_ASSERT(this->selected_tasklist_layout_item);
    Q_ASSERT(this->selected_task_layout_item);
    Task* selected_task = this->selected_task_layout_item->task;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认", "确定要删除事务 "+selected_task->name + "？",
                                QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        data_manager.del_task(selected_task->uuid);
        this->selected_task_layout_item = nullptr;
        // 之所以这里需要 redraw_left，是因为“全部事务”、“未完成事务”等 virtual tasklist 中的内容可能会出现变化
        // TODO 以后需要改进一下
        this->redraw_left();
        this->redraw_middle();
        this->redraw_right();
    }
}

// 编辑当前的事务
void MainWindow::on_btn_edit_task_clicked() {
    Q_ASSERT(this->selected_tasklist_layout_item);
    Q_ASSERT(this->selected_task_layout_item);
    Task* selected_task = this->selected_task_layout_item->task;
    Task new_task = *selected_task;
    if(new_task.type==TaskType::SCHEDULED_EVENT)
    {
        task_edit *editTask = new task_edit (this);
        editTask->putTaskAddress(selected_task);
        editTask->ui->input_task_name->setText(selected_task->name);
        editTask->ui->input_comment->setText(selected_task->comment);
        editTask->ui->datetime_start->setDateTime(selected_task->start_time);
        editTask->ui->datetime_end->setDateTime(selected_task->end_time);
        editTask->ui->datetime_start->setDateTime(selected_task->start_time);
        if (selected_task->reminders.size()!=0)
        {
            editTask->ui->chkbox_have_reminder->setChecked(true);
            editTask->ui->datetime_reminder->setDateTime(selected_task->reminders.front().accurate_time);
        }
        else
        {
            editTask->ui->chkbox_have_reminder->setChecked(false);
            editTask->ui->datetime_reminder->setDateTime(QDateTime::currentDateTime());
        }
        editTask->setModal(true);
        editTask->exec();
        new_task=*(editTask->task);
    }
    else if(new_task.type==TaskType::JOB)
    {
        job_edit *editJob = new job_edit (this);
        editJob->putTaskAddress(selected_task);
        editJob->ui->input_task_name->setText(selected_task->name);
        editJob->ui->input_comment->setText(selected_task->comment);
        if(selected_task->end_time.isNull()==false)
        {
            editJob->ui->chkbox_have_ddl->setChecked(true);
            editJob->ui->datetime_ddl->setVisible(true);
            editJob->ui->datetime_ddl->setDateTime(selected_task->end_time);
        }
        else
        {
            editJob->ui->chkbox_have_ddl->setChecked(false);
            editJob->ui->datetime_ddl->setVisible(false);
            editJob->ui->datetime_ddl->setDateTime(QDateTime::currentDateTime());
        }
        if (selected_task->reminders.size()!=0)
        {
            editJob->ui->chkbox_have_reminder->setChecked(true);
            editJob->ui->datetime_reminder->setVisible(true);
            editJob->ui->datetime_reminder->setDateTime(selected_task->reminders.front().accurate_time);
        }
        else
        {
            editJob->ui->chkbox_have_reminder->setChecked(false);
            editJob->ui->datetime_reminder->setVisible(false);
            editJob->ui->datetime_reminder->setDateTime(QDateTime::currentDateTime());
        }
        editJob->setModal(true);
        editJob->exec();
    }

    data_manager.update_task(selected_task->uuid, new_task);
    this->redraw_left();
    this->redraw_middle();
    this->redraw_right();
}

void MainWindow::select_displayed_tasklist() {
    QObject* sender_obj = sender();
    for (TasklistLayoutItem &item : this->tasklist_layout_items) {
        if (item.btn == sender_obj) {
            this->selected_tasklist_layout_item = &item;
        }
    }
    this->selected_task_layout_item = nullptr;
    this->redraw_middle();
    this->redraw_right();
}

void MainWindow::select_displayed_task() {
    QObject* sender_obj = sender();
    for (TaskLayoutItem &item : this->task_layout_items) {
        if (item.btn == sender_obj) {
            this->selected_task_layout_item = &item;
        }
    }
    this->redraw_right();
}

// 重新绘制左边的区域
void MainWindow::redraw_left() {
    // 删除之前添加的按钮
    qDeleteAll(ui->layout_tasklists->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));

    for (TasklistLayoutItem& item : this->tasklist_layout_items) {
        // 因为我们之前使用 new 来生成 QPushButton，所以我们要手动将其 delete 掉
        // 否则就会发生内存泄漏
        // 虽然泄露这点内存大概率没啥事，但我认为我们需要养成良好的习惯
        // Re: 确实如此
        delete item.btn;
    }
    this->tasklist_layout_items.clear();

    auto process_new_tasklist = [&](TasklistLayoutItem item) {
        QPushButton* btn = new QPushButton(ui->scroll_tasklists);
        btn->setText(item.name);
        ui->layout_tasklists->addWidget(btn);
        ui->scroll_tasklists->setLayout(ui->layout_tasklists);
        item.btn = btn;
        this->tasklist_layout_items.push_back(item);
        QMetaObject::Connection connection = QObject::connect(btn, &QPushButton::clicked, this, &MainWindow::select_displayed_tasklist);
    };

    // 添加由全部任务构成的事务列表
    process_new_tasklist(TasklistLayoutItem {
        "全部事务", 
        nullptr,
        true,
        data_manager.generate_virtual_tasklist([](const Task &task) {
            return true;
        }),
        nullptr
    });

    // 添加由所有未完成的任务构成的事务列表
    process_new_tasklist(TasklistLayoutItem {
        "未完成事务", 
        nullptr,
        true,
        data_manager.generate_virtual_tasklist([](const Task &task) {
            return !task.is_finished;
        }),
        nullptr
    });

    // 添加所有用户创建的事务列表
    for (Tasklist &tasklist : data_manager.tasklists) {
        process_new_tasklist(TasklistLayoutItem {
            tasklist.name,
            nullptr,
            false,
            {},
            &tasklist
        });
    }
}

void MainWindow::redraw_middle() {
    qDeleteAll(ui->layout_tasks->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
    for (TaskLayoutItem &item : this->task_layout_items) {
        delete item.btn;
    }
    this->task_layout_items.clear();

    if (!this->selected_tasklist_layout_item) {
        // 当前没有选中任何任务列表
        ui->lab_tasklist_name->setText("请选择一个事务列表");
        ui->btn_add_job->setVisible(false);
        ui->btn_add_sche_task->setVisible(false);
        ui->btn_del_tasklist->setVisible(false);
    } else {
        if (!this->selected_tasklist_layout_item->is_virtual) {
            ui->btn_add_job->setVisible(true);
            ui->btn_add_sche_task->setVisible(true);
            ui->btn_del_tasklist->setVisible(true);
        } else {
            // 不允许向 virtual tasklist 中添加 task
            ui->btn_add_job->setVisible(false);
            ui->btn_add_sche_task->setVisible(false);
            // 不允许删除 virtual tasklist
            ui->btn_del_tasklist->setVisible(false);
        }

        ui->lab_tasklist_name->setText(this->selected_tasklist_layout_item->name);

        auto process_new_task = [&](Task *task) {
            QPushButton* btn = new QPushButton(ui->scroll_tasks);
            btn->setText(task->name);
            ui->layout_tasks->addWidget(btn);
            ui->scroll_tasks->setLayout(ui->layout_tasks);
            this->task_layout_items.push_back(TaskLayoutItem {
                task,
                btn 
            });
            QObject::connect(btn, &QPushButton::clicked, this, &MainWindow::select_displayed_task);
        };

        if (this->selected_tasklist_layout_item->is_virtual) {
            // 如果一个事务列表是 virtual 的，那么根据约定，我们从 QVector<Task*> tasks 中读取信息
            for (Task *task : this->selected_tasklist_layout_item->tasks) {
                process_new_task(task);
            }
        } else {
            // 否则，就直接从 Tasklist* tasklist 中读取信息
            for (Task &task : this->selected_tasklist_layout_item->tasklist->tasks) {
                process_new_task(&task);
            }
        }
    }
}

void MainWindow::redraw_right() {
    if (this->selected_task_layout_item == nullptr) {
        // 当前没有选中任务
        ui->label_task_name->setText("请选择一个事务");
        ui->widget_task_info->setVisible(false);
    } else {
        ui->label_task_name->setText(this->selected_task_layout_item->task->name);
        ui->widget_task_info->setVisible(true);
        Task* selected_task = this->selected_task_layout_item->task;
        if (selected_task->is_finished == false) {
            ui->btn_finish->setVisible(true);
            ui->label_is_finished->setVisible(true);
            ui->label_is_finished->setText("任务完成状态：未完成");
        } else {
            ui->btn_finish->setVisible(false);
            ui->label_is_finished->setVisible(true);
            ui->label_is_finished->setText("任务完成状态：已完成");
        }
        if (selected_task->type == TaskType::SCHEDULED_EVENT) {
            ui->widget_task_start_time->setVisible(true);
            ui->widget_task_end_time->setVisible(true);
            ui->label_task_start_time->setText(selected_task->start_time.toString("yyyy-MM-dd hh:mm:ss"));
            ui->label_task_end_time->setText(selected_task->end_time.toString("yyyy-MM-dd hh:mm:ss"));
        } else if (selected_task->type == TaskType::JOB) {
            ui->widget_task_start_time->setVisible(false);
            if (selected_task->end_time.isNull()) {
                ui->widget_task_end_time->setVisible(false);
            } else {
                ui->widget_task_end_time->setVisible(true);
                ui->label_task_end_time->setText(selected_task->end_time.toString("yyyy-MM-dd hh:mm:ss"));
            }
        }
        ui->label_task_comment->setText(selected_task->comment);
    }
}
