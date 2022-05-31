#ifndef LIST_TYPE_H
#define LIST_TYPE_H

#include <QWidget>

namespace Ui {
class list_type;
}

class list_type : public QWidget
{
    Q_OBJECT

public:
    explicit list_type(QWidget *parent = nullptr);
    ~list_type();

private:
    Ui::list_type *ui;
};

#endif // LIST_TYPE_H
