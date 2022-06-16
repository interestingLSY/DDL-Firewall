#ifndef AddScheTask_H
#define AddScheTask_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class AddScheTask;
}
QT_END_NAMESPACE

class AddScheTask : public QDialog
{
    Q_OBJECT

public:
    explicit AddScheTask(QWidget *parent = nullptr);
    ~AddScheTask();
private slots:
    void on_chkbox_have_reminder_stateChanged(int is_checked);

    void on_btn_create_clicked();

    void on_datetime_start_dateTimeChanged(const QDateTime &datetime);


public:
    Ui::AddScheTask *ui;
};

#endif // AddScheTask_H
