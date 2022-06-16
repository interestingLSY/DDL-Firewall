#ifndef JOB_EDIT_H
#define JOB_EDIT_H

#include <QDialog>

namespace Ui {
class job_edit;
}

class job_edit : public QDialog
{
    Q_OBJECT

public:
    explicit job_edit(QWidget *parent = nullptr);
    ~job_edit();

private:
    Ui::job_edit *ui;
};

#endif // JOB_EDIT_H
