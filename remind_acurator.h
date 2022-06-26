#ifndef REMIND_ACURATOR_H
#define REMIND_ACURATOR_H

#include <QDialog>

#include "./src/classes/reminder.h"
#include "./src/classes/subtask.h"
#include "./src/classes/task.h"
#include "./src/classes/tasklist.h"
#include "./src/data/data.h"

namespace Ui {
class remind_acurator;
}

class remind_acurator : public QDialog
{
    Q_OBJECT

public:
    explicit remind_acurator(Task* task, Reminder* reminder, QWidget *parent = nullptr);
    ~remind_acurator();

private:
    Ui::remind_acurator *ui;
};

#endif // REMIND_ACURATOR_H
