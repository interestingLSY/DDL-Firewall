#ifndef LIST_TYPE2_H
#define LIST_TYPE2_H

#include <QWidget>

namespace Ui {
class list_type2;
}

class list_type2 : public QWidget
{
    Q_OBJECT

public:
    explicit list_type2(QWidget *parent = nullptr);
    ~list_type2();

private:
    Ui::list_type2 *ui;
};

#endif // LIST_TYPE2_H
