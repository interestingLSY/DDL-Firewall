#ifndef LIST_TYPE_H
#define LIST_TYPE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class list_type;
}
QT_END_NAMESPACE

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
