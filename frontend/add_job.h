#ifndef AddJob_H
#define AddJob_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class AddJob;
}
QT_END_NAMESPACE

class AddJob : public QDialog
{
    Q_OBJECT

public:
    explicit AddJob(QWidget *parent = nullptr);
    ~AddJob();

private slots:
    void on_chkbox_have_ddl_stateChanged(int arg1);

    void on_chkbox_have_reminder_stateChanged(int arg1);

    void on_btn_create_clicked();

    void on_datetime_ddl_dateTimeChanged(const QDateTime &datetime);

private:
    Ui::AddJob *ui;
};

#endif // AddJob_H
