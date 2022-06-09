#include <QDialog>
#include <QWidget>

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
    ui->btn_left_create_tasklist->setStyleSheet(BUTTON_STYLE);
    ui->btn_right_done->setStyleSheet(BUTTON_STYLE);
    ui->btn_right_edit_task->setStyleSheet(BUTTON_STYLE);
    ui->btn_right_del_task->setStyleSheet(BUTTON_STYLE);
    ui->btn_mid_add_job->setStyleSheet(BUTTON_STYLE);
    ui->btn_mid_add_sche_task->setStyleSheet(BUTTON_STYLE);
#undef BUTTON_STYLE

    ui->lab_ddlcounter->setText("今天还有 " + QString::number(1) + " 个ddl,加油！");

    this->selected_task_item = nullptr;
    this->selected_tasklist_item = nullptr;
    this->tasklist_items.resize(10000);
    this->tasklist_items.clear();

    this->redraw_left();
    this->redraw_middle();
    this->redraw_right();
}

MainWindow::~MainWindow() {
    delete ui;
}

// 创建一个新的事务列表
void MainWindow::on_btn_left_create_tasklist_clicked() {
    AddTaskList *querylists = new AddTaskList(this);
    querylists->setModal(true);
    querylists->exec();
    this->redraw_left();
}

// 创建一个新的任务
void MainWindow::on_btn_mid_add_job_clicked() {
    AddJob *querytask = new AddJob(this);
    querytask->setModal(true);
    querytask->exec();

    // 这里需要 redraw_left，因为“全部事务”，“未完成事务”中的内容可能会出现变化
    this->redraw_left();
    this->redraw_middle();
}

// 创建一个新的定时事务
void MainWindow::on_btn_mid_add_sche_task_clicked() {
    AddScheTask *querytask = new AddScheTask(this);
    querytask->setModal(true);
    querytask->exec();

    this->redraw_left();
    this->redraw_middle();
}

void MainWindow::select_displayed_tasklist() {
    QObject* sender_obj = sender();
    for (TasklistLayoutItem &item : this->tasklist_items) {
        if (item.btn == sender_obj) {
            this->selected_tasklist_item = &item;
        }
    }
    this->redraw_middle();
}

// 重新绘制左边的区域
void MainWindow::redraw_left() {
    qDeleteAll(ui->layout_tasklists->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));

    for (TasklistLayoutItem& item : this->tasklist_items) {
        delete item.btn;
    }
    this->tasklist_items.clear();

    auto process_new_tasklist = [&](TasklistLayoutItem item) {
        QPushButton* btn = new QPushButton(ui->scroll_tasklists);
        btn->setText(item.name);
        ui->layout_tasklists->addWidget(btn);
        ui->scroll_tasklists->setLayout(ui->layout_tasklists);
        item.btn = btn;
        this->tasklist_items.push_back(item);
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

    // 添加所有用户创建的事务清单
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
    if (!this->selected_tasklist_item) {
        // 当前没有选中任何任务列表
        ui->lab_tasklist_name->setText("请选择一个事务列表");
        ui->btn_mid_add_job->setVisible(false);
        ui->btn_mid_add_sche_task->setVisible(false);
    } else {
        if (!this->selected_tasklist_item->is_virtual) {
            // 不允许向 virtual tasklist 中添加 task
            ui->btn_mid_add_job->setVisible(true);
            ui->btn_mid_add_sche_task->setVisible(true);
        } else {
            ui->btn_mid_add_job->setVisible(false);
            ui->btn_mid_add_sche_task->setVisible(false);
        }

        qDeleteAll(ui->layout_tasks->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
        for (TaskLayoutItem &item : this->task_items) {
            delete item.btn;
        }
        this->task_items.clear();

        ui->lab_tasklist_name->setText(this->selected_tasklist_item->name);

        auto process_new_task = [&](Task *task) {
            QPushButton* btn = new QPushButton(ui->scroll_tasks);
            btn->setText(task->name);
            ui->layout_tasks->addWidget(btn);
            ui->scroll_tasks->setLayout(ui->layout_tasks);
            this->task_items.push_back(TaskLayoutItem {
                task,
                btn 
            });
        };

        if (this->selected_tasklist_item->is_virtual) {
            for (Task *task : this->selected_tasklist_item->tasks) {
                process_new_task(task);
            }
        } else {
            for (Task &task : this->selected_tasklist_item->tasklist->tasks) {
                process_new_task(&task);
            }
        }
    }
}

void MainWindow::redraw_right() {

}