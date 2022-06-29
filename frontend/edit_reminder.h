#ifndef EDIT_REMINDER_H
#define EDIT_REMINDER_H

#include <QDialog>
#include "../backend/classes/reminder.h"

namespace Ui {
class edit_reminder;
}

class edit_reminder : public QDialog
{
    Q_OBJECT

public:
    explicit edit_reminder(QWidget *parent = nullptr);
    ~edit_reminder();
    Reminder *reminder;
    void putReminderAddress(Reminder* temp);

public:
    Ui::edit_reminder *ui;
private slots:
    void on_btn_confirm_clicked();
};

#endif // EDIT_REMINDER_H
