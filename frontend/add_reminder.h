#ifndef ADD_REMINDER_H
#define ADD_REMINDER_H

#include <QDialog>

namespace Ui {
class add_reminder;
}

class add_reminder : public QDialog
{
    Q_OBJECT

public:
    explicit add_reminder(QWidget *parent = nullptr);
    ~add_reminder();

private slots:
    void on_btn_create_clicked();

private:
    Ui::add_reminder *ui;
};

#endif // ADD_REMINDER_H
