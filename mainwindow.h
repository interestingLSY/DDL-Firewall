#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVector>
#include <QMainWindow>
#include <QPushButton>
#include <QPair>

#include "./src/classes/reminder.h"
#include "./src/classes/subtask.h"
#include "./src/classes/task.h"
#include "./src/classes/tasklist.h"
#include "./src/data/data.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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


    struct TaskLayoutItem {
        Task* task;
        QPushButton* btn;
    };
    QVector<TaskLayoutItem> task_layout_items;
    // 当前选中的事务，nullptr 表示没有选中任何事务
    TaskLayoutItem* selected_task_layout_item;
    
    
    // 重新绘制左边（list of tasklist）的区域
    void redraw_left();
    // 重新绘制中间（tasklist）的区域
    void redraw_middle();
    // 重新绘制右边（task）的区域
    void redraw_right();
    

public:
    Ui::MainWindow *ui;

private slots:
    void on_btn_create_tasklist_clicked();
    void on_btn_add_job_clicked();
    void on_btn_add_sche_task_clicked();
    void on_btn_del_tasklist_clicked();
    void on_btn_del_task_clicked();
    void on_btn_edit_task_clicked();

public slots:
    void select_displayed_tasklist();
    void select_displayed_task();
};
#endif // MAINWINDOW_H
