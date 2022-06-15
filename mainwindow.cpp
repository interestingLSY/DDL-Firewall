#include <QDialog>
#include <QWidget>
#include <QMessageBox>
#include <QBoxLayout>
#include <QtGlobal>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addtasklist.h"
#include "errors.h"
#include "list_type.h"
#include "calendar_type.h"
#include "add_job.h"
#include "add_sche_task.h"

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
        // 这里需要 redraw_left，因为“全部事务”，“未完成事务”中的内容可能会出现变化
        // 以后需要改进一下
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
    // TODO
    // 我们需要在这里生成一个新的窗口，让用户能够修改 selected_task
    // 假设修改后的 task 的名字是 new_task
    Task new_task = *selected_task;
    data_manager.update_task(selected_task->uuid, new_task);
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

        qDeleteAll(ui->layout_tasks->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
        for (TaskLayoutItem &item : this->task_layout_items) {
            delete item.btn;
        }
        this->task_layout_items.clear();

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
        ui->btn_del_task->setVisible(false);
        ui->btn_edit_task->setVisible(false);
    } else {
        ui->btn_del_task->setVisible(true);
        ui->btn_edit_task->setVisible(true);
        ui->label_task_name->setText(this->selected_task_layout_item->task->name);
        // TODO
        // 我们需要在右侧那一栏中添加更多的关于事务的信息
        // （比如类型、起止时间、注释、子任务、是否完成...）
        // 详见 src/classes/task.h
        // 并且在这里更新界面中的相关信息
    }
}