#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVector>
#include <QMainWindow>
#include <QPushButton>
#include <QPair>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QCloseEvent>

#include "../backend/classes/reminder.h"
#include "../backend/classes/subtask.h"
#include "../backend/classes/task.h"
#include "../backend/classes/tasklist.h"
#include "../backend/data/data.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 与系统托盘有关的东西
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    // 与“提醒”相关的东西
    void scan_task_and_remind();    // 扫描所有事务，检查是否需要提醒。该函数每 30 秒运行一次。TODO 这种方法比较低效，可以优化。

    struct TasklistLayoutItem {
        QString name;
        QPushButton* btn;

        // 我们称一个 TasklistLayoutItem 是 virtual 的
        // 当且仅当其通过 data_manager.generate_virtual_tasklist 得到
        // 而不是一个“物理意义上的” Tasklist
        bool is_virtual = 0;

        // 如果这个 TasklistLayoutItem 是 virtual 的，
        // 那么我们就在 tasks 存放所有指向 task 的指针
        QVector<Task*> tasks;
        // 否则存放一个指向真正的 tasklist 的指针
        Tasklist* tasklist;
        // Rust is the best programming language
    };
    QVector<TasklistLayoutItem> tasklist_layout_items;
    // 当前选中的事务列表，nullptr 表示没有选中任何事务列表
    TasklistLayoutItem* selected_tasklist_layout_item;

    // 下一个提醒所属的 Task

    struct TaskLayoutItem {
        Task* task;
        QPushButton* btn;
    };
    QVector<TaskLayoutItem> task_layout_items;
    // 当前选中的事务，nullptr 表示没有选中任何事务
    TaskLayoutItem* selected_task_layout_item;

    struct ReminderLayoutItem {
        Reminder* reminder;
        QPushButton* btn;
    };
    QVector<ReminderLayoutItem> reminder_layout_items;
    // 标注当前选中的 Reminder，nullptr 代表目前未选中 Reminder
    ReminderLayoutItem* selected_reminder_layout_item;

    struct SubtaskLayoutItem {
        Subtask* subtask;
        QPushButton* btn;
    };
    QVector<SubtaskLayoutItem> subtask_layout_items;
    // 标注当前选中的子任务，nullptr 代表目前未选中子任务
    SubtaskLayoutItem* selected_subtask_layout_item;
    
    
    // 重新绘制左边（list of tasklist）的区域
    void redraw_left();
    // 重新绘制中间（tasklist）的区域
    void redraw_middle();
    // 重新绘制右边（task）的区域
    void redraw_right();

public:
    Ui::MainWindow *ui;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_btn_create_tasklist_clicked();
    void on_btn_add_job_clicked();
    void on_btn_add_sche_task_clicked();
    void on_btn_del_tasklist_clicked();
    void on_btn_del_task_clicked();
    void on_btn_edit_task_clicked();

    void on_btn_add_subtask_clicked();

    void on_btn_edit_subtask_clicked();

    void on_btn_add_reminder_clicked();

    void on_btn_edit_reminder_clicked();

    void on_btn_delete_reminder_clicked();

    void on_btn_finish_subtask_clicked();

    void on_btn_delete_subtask_clicked();

    void on_btn_finish_clicked();

    void exit_all();

public slots:
    void select_displayed_tasklist();
    void select_displayed_task();
    void select_subtask();
    void select_reminder();
signals :
    void save_all();
};

#endif // MAINWINDOW_H


