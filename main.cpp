#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.setWindowTitle(QObject::tr("DDL firewall"));
    w.show();
    
    return app.exec();
}
