#ifndef ERRORS_H
#define ERRORS_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class Errors;
}
QT_END_NAMESPACE

class Errors : public QDialog
{
    Q_OBJECT

public:
    explicit Errors(QWidget *parent = nullptr);
    ~Errors();

public:
    Ui::Errors *ui;

public slots:
        void change_text();
};

#endif // ERRORS_H
