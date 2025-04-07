#ifndef CHATITEM_H
#define CHATITEM_H

#include <QWidget>

namespace Ui {
class ChatItem;
}

class ChatItem : public QWidget
{
    Q_OBJECT

public:
    explicit ChatItem(const QString &name, const QString &lastMessage, const QString &chatId, QWidget *parent = nullptr);
    ~ChatItem();

protected:
    void mousePressEvent(QMouseEvent *event) override;


signals:
    void clicked(QString clickedChatId);


private:
    QString chatId;
    Ui::ChatItem *ui;
};

#endif // CHATITEM_H
