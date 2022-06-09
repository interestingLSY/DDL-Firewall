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
    void switchpage();

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
    QVector<TasklistLayoutItem> tasklist_items;
    TasklistLayoutItem* selected_tasklist_item;

    struct TaskLayoutItem {
        Task* task;
        QPushButton* btn;
    };
    QVector<TaskLayoutItem> task_items;
    Task* selected_task_item;
    
    void redraw_left();
    void redraw_middle();
    void redraw_right();
    

public:
    Ui::MainWindow *ui;
    int current_vision_type, old_vision_type;

private slots:
    void on_btn_left_create_tasklist_clicked();
    void on_btn_mid_add_job_clicked();
    void on_btn_mid_add_sche_task_clicked();

public slots:
    void select_displayed_tasklist();

};
#endif // MAINWINDOW_H
