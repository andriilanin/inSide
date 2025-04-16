#ifndef MESSAGEITEM_H
#define MESSAGEITEM_H

#include <QWidget>

namespace Ui {
class MessageItem;
}

class MessageItem : public QWidget
{
    Q_OBJECT

public:
    explicit MessageItem(QWidget *parent = nullptr, QString text = "", QString userName = "None", bool isOutGoing = false, bool isSameUserName = false);
    ~MessageItem();
    QString getName();

protected:


private:
    Ui::MessageItem *ui;
};

#endif // MESSAGEITEM_H
