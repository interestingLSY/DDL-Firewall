#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(ddlfirewall);

    QApplication app(argc, argv);

    MainWindow w;
    w.setWindowTitle(QObject::tr("DDL firewall"));
    w.show();
    
    return app.exec();
}
