#include <QDialog>
#include <QWidget>
#include <QMessageBox>
#include <QBoxLayout>
#include <QtGlobal>
#include <QDateTime>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "add_job.h"
#include "add_sche_task.h"
#include "add_tasklist.h"
#include "errors.h"
#include "calendar_type.h"
#include "add_job.h"
#include "add_sche_task.h"
#include "edit_sche_task.h"
#include "ui_edit_sche_task.h"
#include "edit_job.h"
#include "ui_edit_job.h"
#include "add_reminder.h"
#include "add_subtask.h"
#include "edit_subtask.h"
#include "ui_edit_subtask.h"
#include "edit_reminder.h"
#include "ui_edit_reminder.h"
#include "remind_acurator.h"

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

    this->selected_task_layout_item = nullptr;
    this->selected_tasklist_layout_item = nullptr;
    this->selected_subtask_layout_item = nullptr;
    this->selected_reminder_layout_item =nullptr;

    this->redraw_left();
    this->redraw_middle();
    this->redraw_right();

    // 右下角托盘
    this->trayIcon = new QSystemTrayIcon(this);
    this->trayIcon->setIcon(QIcon(":/ddlfirewall.ico"));
    this->trayIconMenu = new QMenu(this);
    QAction *action = trayIconMenu->addAction("显示主界面");
    connect(action, &QAction::triggered, this ,&MainWindow::show);
    action = trayIconMenu->addAction("退出应用");
    connect(action, &QAction::triggered, this ,&MainWindow::exit_all);
    trayIcon->setContextMenu(this->trayIconMenu);
    this->trayIcon->show();
    this->setWindowIcon(QIcon(":/ddlfirewall.ico"));

    // 提醒器
    QTimer *timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &MainWindow::scan_task_and_remind);
    timer->start(30*1000);  // 30 seconds
}

void MainWindow::closeEvent(QCloseEvent *event) {
#ifdef Q_OS_MACOS
    if (!event->spontaneous() || !isVisible()) {
        return;
    }
#endif
    trayIcon->showMessage("DDL FireWall", "应用程序将会继续在后台运行", QSystemTrayIcon::Information, 3000);
    this->hide();
    event->ignore();
}


void MainWindow::exit_all()
{
    qApp->quit();
}


// 可以换行 防止超出显示范围
void Label_Adjust_Size(QLabel* label,bool flag_Hcenter)
{
    label->adjustSize();
    label->setWordWrap(true);
    label->setAlignment(Qt::AlignTop);
    label->setGeometry(QRect(328, 240, 329, 27*4));
    if(flag_Hcenter)
        label->setAlignment(Qt::AlignHCenter);
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
    reply = QMessageBox::question(this, "DDL FireWall", "确定要删除事务清单 "+selected_tasklist->name + "？\n这将会删除这个清单内的所有事务！",
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
    reply = QMessageBox::question(this, "DDL FireWall", "确定要删除事务 "+selected_task->name + "？",
                                QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        data_manager.del_task(selected_task->uuid);
        this->selected_task_layout_item = nullptr;
        // 之所以这里需要 redraw_left，是因为“全部事务”、“未完成事务”等 virtual tasklist 中的内容可能会出现变化
        // TODO 以后需要改进一下
        void check_reminders();
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
        EditScheTask *editTask = new EditScheTask (this);
        editTask->putTaskAddress(selected_task);
        editTask->ui->input_task_name->setText(selected_task->name);
        editTask->ui->input_comment->setText(selected_task->comment);
        editTask->ui->datetime_start->setDateTime(selected_task->start_time);
        editTask->ui->datetime_end->setDateTime(selected_task->end_time);
        editTask->ui->datetime_start->setDateTime(selected_task->start_time);
        editTask->ui->chkbox_have_reminder->setVisible(true);
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

        if(selected_task->is_finished==true)
        {
            editTask->ui->chkbox_have_reminder->setVisible(false);
            editTask->ui->datetime_reminder->setVisible(false);
        }

        editTask->setModal(true);
        editTask->exec();
        new_task=*(editTask->task);
    }
    else if(new_task.type==TaskType::JOB)
    {
        EditJob *editJob = new EditJob (this);
        editJob->putTaskAddress(selected_task);
        editJob->ui->input_task_name->setText(selected_task->name);
        editJob->ui->input_comment->setText(selected_task->comment);
        editJob->ui->chkbox_have_reminder->setVisible(true);
        editJob->ui->chkbox_have_ddl->setVisible(true);
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
        if(selected_task->is_finished==true)
        {
            editJob->ui->chkbox_have_reminder->setVisible(false);
            editJob->ui->datetime_reminder->setVisible(false);
            editJob->ui->chkbox_have_ddl->setVisible(false);
            editJob->ui->datetime_ddl->setVisible(false);
        }

        editJob->setModal(true);
        editJob->exec();
        new_task=*(editJob->task);
    }

    // qDebug() << new_task;
    data_manager.update_task(selected_task->uuid, new_task);
    void check_reminders();
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

void MainWindow::select_subtask()
{
    QObject* sender_btn = sender();
    for (SubtaskLayoutItem &item : this->subtask_layout_items)
        if (item.btn == sender_btn)
            this->selected_subtask_layout_item = &item;

    this->redraw_right();
}

void MainWindow::select_reminder()
{
    QObject* sender_btn = sender();
    for (ReminderLayoutItem &item : this->reminder_layout_items)
        if (item.btn == sender_btn)
            this->selected_reminder_layout_item = &item;

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
    int cnt_todos=0;
    for (Tasklist &tasklist : data_manager.tasklists)
        for (Task &task : tasklist.tasks)
            if(task.end_time.isNull()==false&&task.is_finished==false)
                if(task.end_time.date()==QDateTime::currentDateTime().date()&&
                        task.end_time>QDateTime::currentDateTime())
                            cnt_todos++;
    if(cnt_todos)
        ui->lab_ddlcounter->setText("今天还有 " + QString::number(cnt_todos) + " 个 ddl,加油！");
    else
        ui->lab_ddlcounter->setText("你已经完成了今天全部的 ddl，真棒！");

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
        Label_Adjust_Size(ui->lab_tasklist_name,true);
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
        ui->btn_del_task->setVisible(false);
        ui->btn_edit_task->setVisible(false);
    } else {
        ui->btn_del_task->setVisible(true);
        ui->btn_edit_task->setVisible(true);
        //由选择状态确定按钮的显示情况
        if (this->selected_subtask_layout_item!=nullptr&&this->selected_task_layout_item->task->is_finished==false)
        {
            ui->btn_delete_subtask->setVisible(true);
            ui->btn_edit_subtask->setVisible(true);
            // 选中已经完成了的子任务不需要完成按钮
            if(this->selected_subtask_layout_item->subtask->is_finished==false)
                ui->btn_finish_subtask->setVisible(true);
            else
                ui->btn_finish_subtask->setVisible(false);
        }
        else
        {
            ui->btn_delete_subtask->setVisible(false);
            ui->btn_edit_subtask->setVisible(false);
            ui->btn_finish_subtask->setVisible(false);
        }
        if (this->selected_reminder_layout_item!=nullptr&&this->selected_task_layout_item->task->is_finished==false)
        {
            ui->btn_delete_reminder->setVisible(true);
            ui->btn_edit_reminder->setVisible(true);
        }
        else
        {
            ui->btn_delete_reminder->setVisible(false);
            ui->btn_edit_reminder->setVisible(false);
        }
        if(this->selected_task_layout_item->task->is_finished==false)
        {
            ui->btn_add_reminder->setVisible(true);
            ui->btn_add_subtask->setVisible(true);
        }
        else
        {
            ui->btn_add_reminder->setVisible(false);
            ui->btn_add_subtask->setVisible(false);
        }
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
        ui->label_task_comment_str->setText(selected_task->comment);
        Label_Adjust_Size(ui->label_task_comment_str,false);
        Label_Adjust_Size(ui->label_task_name,true);
    }

    if (this->selected_task_layout_item != nullptr)
    {
        // 删除已存在的 subtask
        qDeleteAll(ui->layout_subtasks->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));

        for (SubtaskLayoutItem& item : this->subtask_layout_items)
            delete item.btn;

        this->subtask_layout_items.clear();

        auto process_new_subtask = [&](SubtaskLayoutItem item)
        {
            QPushButton* btn = new QPushButton(ui->scroll_subtasks);
            btn->setText(item.subtask->name);
            //已完成便添加删除线
            if(item.subtask->is_finished==true)
                btn->setStyleSheet("text-decoration: line-through;");
            else
                btn->setStyleSheet("text-decoration: none;");
            ui->layout_subtasks->addWidget(btn);
            ui->scroll_subtasks->setLayout(ui->layout_subtasks);
            item.btn = btn;
            this->subtask_layout_items.push_back(item);
            QMetaObject::Connection connection = QObject::connect(btn, &QPushButton::clicked, this, &MainWindow::select_subtask);
        };

        //添加子任务 后添加已经完成了的
        for (Subtask &subtask : MainWindow::selected_task_layout_item->task->subtasks)
            if(subtask.is_finished==false)
                process_new_subtask(SubtaskLayoutItem
                {
                    &subtask,
                    nullptr
                });
        for (Subtask &subtask : MainWindow::selected_task_layout_item->task->subtasks)
            if(subtask.is_finished==true)
                process_new_subtask(SubtaskLayoutItem
                {
                    &subtask,
                    nullptr
                });

        //删除已存在的提醒
        qDeleteAll(ui->layout_reminders->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));

        for (ReminderLayoutItem& item : this->reminder_layout_items)
            delete item.btn;

        this->reminder_layout_items.clear();

        auto process_new_reminder = [&](ReminderLayoutItem item)
        {
            QPushButton* btn = new QPushButton(ui->scroll_reminders);
            btn->setText(item.reminder->accurate_time.toString("yyyy-MM-dd hh:mm:ss"));
            //已过期便添加删除线
            if(item.reminder->accurate_time<QDateTime::currentDateTime())
                btn->setStyleSheet("text-decoration: line-through;");
            else
                btn->setStyleSheet("text-decoration: none;");
            ui->layout_reminders->addWidget(btn);
            ui->scroll_reminders->setLayout(ui->layout_reminders);
            item.btn = btn;
            this->reminder_layout_items.push_back(item);
            QMetaObject::Connection connection = QObject::connect(btn, &QPushButton::clicked, this, &MainWindow::select_reminder);
        };

        //初始化 添加提醒
        for (Reminder &reminder : MainWindow::selected_task_layout_item->task->reminders)
            if(reminder.accurate_time>QDateTime::currentDateTime())
                process_new_reminder(ReminderLayoutItem
                {
                    &reminder,
                    nullptr
                });
        for (Reminder &reminder : MainWindow::selected_task_layout_item->task->reminders)
            if(reminder.accurate_time<QDateTime::currentDateTime())
                process_new_reminder(ReminderLayoutItem
                {
                    &reminder,
                    nullptr
                });
    }
}

void MainWindow::on_btn_add_subtask_clicked()
{
    add_subtask *adding = new add_subtask(this);
    adding->setModal(true);
    adding->exec();

    this->redraw_right();
}


void MainWindow::on_btn_edit_subtask_clicked()
{
    Subtask *selected_subtask = MainWindow::selected_subtask_layout_item->subtask;
    edit_subtask *edit =new edit_subtask(this);
    edit->putSubtaskAddress(selected_subtask_layout_item->subtask);
    edit->ui->input_subtask_name->setText(selected_subtask->name);

    edit->setModal(true);
    edit->exec();

    this->redraw_right();
}


void MainWindow::on_btn_add_reminder_clicked()
{
    add_reminder *adding = new add_reminder(this);
    adding->setModal(true);
    adding->exec();
    this->redraw_right();
}


void MainWindow::on_btn_edit_reminder_clicked()
{
    Reminder *selected_reminder = MainWindow::selected_reminder_layout_item->reminder;
    edit_reminder *edit =new edit_reminder(this);
    edit->putReminderAddress(selected_reminder_layout_item->reminder);
    edit->ui->reminder_datetime->setDateTime(selected_reminder->accurate_time);

    edit->setModal(true);
    edit->exec();
    this->redraw_right();
}


void MainWindow::on_btn_delete_reminder_clicked()
{
    Q_ASSERT(this->selected_task_layout_item);
    Q_ASSERT(this->selected_reminder_layout_item);
    Reminder* selected_reminder = this->selected_reminder_layout_item->reminder;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "DDL FireWall", "确定要删除在 "+selected_reminder->accurate_time.toString("yyyy-MM-dd hh:mm:ss")
                                  + "时的提醒？",
                                 QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        selected_task_layout_item->task->del_reminder(selected_reminder->uuid);
        this->selected_reminder_layout_item = nullptr;
        this->redraw_right();
    }

}


void MainWindow::on_btn_finish_subtask_clicked()
{
    Q_ASSERT(this->selected_task_layout_item);
    Q_ASSERT(this->selected_subtask_layout_item);
    Subtask* selected_subtask = this->selected_subtask_layout_item->subtask;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "DDL FireWall", "恭喜你！确认完成子任务"+selected_subtask->name+ "?",
                                 QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        selected_subtask->is_finished=true;
        this->redraw_right();
    }
    else
    {
        QMessageBox::about(this, "DDL FireWall", "任务尚未完成，请再接再厉！          ");
    }

}


void MainWindow::on_btn_delete_subtask_clicked()
{
    Q_ASSERT(this->selected_task_layout_item);
    Q_ASSERT(this->selected_subtask_layout_item);
    Subtask* selected_subtask = this->selected_subtask_layout_item->subtask;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "DDL FireWall", "确定要删除子任务 "+selected_subtask->name + "？",
                                QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        selected_task_layout_item->task->del_subtask(selected_subtask->uuid);
        this->selected_subtask_layout_item = nullptr;
        this->redraw_right();
    }
}


void MainWindow::on_btn_finish_clicked()
{
    Q_ASSERT(this->selected_task_layout_item);
    Task* selected_task = this->selected_task_layout_item->task;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "DDL FireWall", "恭喜你！确认完成任务"+selected_task->name+ "?",
                                 QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        selected_task->is_finished=true;
        this->redraw_right();
    }
    else
    {
        QMessageBox::about(this, "DDL FireWall", "请再接再厉！");
    }
    this->redraw_right();
    this->redraw_middle();
}

void MainWindow::scan_task_and_remind() {
    // 找到 tasklist_layout_items 中那个装有所有“未完成事务”的列表
    QVector<Task*> *tasks = nullptr;
    for (TasklistLayoutItem& layout_item : this->tasklist_layout_items) {
        if (layout_item.is_virtual && layout_item.name == QString("未完成事务")) {
            tasks = &layout_item.tasks;
            break;
        }
    }
    assert(tasks != nullptr);

    // 从这里面筛选出需要提醒的 Reminder
    QVector<QPair<Task*, Reminder*>> chosen_reminders;
    QDateTime now = QDateTime::currentDateTime();
    for (Task* task : (*tasks)) {
        for (Reminder &reminder : task->reminders) {
            if (!reminder.is_reminded && reminder.accurate_time <= now) {
                chosen_reminders.push_back({task, &reminder});
            }
        }
    }

    // 依次进行提醒，并标注为“已提醒”
    for (auto [task, reminder] : chosen_reminders) {
        remind_acurator* acurator = new remind_acurator(task, reminder, this);
        acurator->exec();
        reminder->is_reminded = true;
    }

    // 对窗体的右侧部分进行更新
    this->redraw_right();
}