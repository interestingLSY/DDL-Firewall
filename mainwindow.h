#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

public:
    Ui::MainWindow *ui;

private slots:
    void on_btn_left_create_tasklist_clicked();
    void on_btn_mid_switch_clicked();
    void on_btn_mid_create_task_clicked();
};
#endif // MAINWINDOW_H
