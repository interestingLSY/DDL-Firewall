#ifndef CALENDAR_TYPE_H
#define CALENDAR_TYPE_H

#include <QWidget>

namespace Ui {
class calendar_type;
}

class calendar_type : public QWidget
{
    Q_OBJECT

public:
    explicit calendar_type(QWidget *parent = nullptr);
    ~calendar_type();

private:
    Ui::calendar_type *ui;
};

#endif // CALENDAR_TYPE_H
