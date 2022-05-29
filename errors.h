#ifndef ERRORS_H
#define ERRORS_H

#include <QDialog>

namespace Ui {
class Errors;
}

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
