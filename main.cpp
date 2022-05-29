#include "mainwindow.h"
#include ".\src\classes\reminder.h"
#include ".\src\classes\subtask.h"
#include ".\src\classes\task.h"
#include ".\src\classes\tasklist.h"
#include "addtasklist.h"
#include <QApplication>
#include "errors.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle(QObject::tr("DDL firewall"));
    w.show();
    return a.exec();
}
