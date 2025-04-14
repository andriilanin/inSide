#ifndef CHATITEM_H
#define CHATITEM_H

#include <QWidget>
#include <QEvent>
#include <QResizeEvent>

namespace Ui {
class ChatItem;
}

class ChatItem : public QWidget
{
    Q_OBJECT

public:
    explicit ChatItem(const QString &chatName, QJsonObject &lastMessageObj, const QString &chatId, QWidget *parent = nullptr);
    ~ChatItem();

protected:

    void mousePressEvent(QMouseEvent *event) override;
    bool eventFilter(QObject* obj, QEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;


signals:
    void clicked(QString clickedChatId);


private:
    std::function<void()> callback;
    QString chatId;
    Ui::ChatItem *ui;
};

#endif // CHATITEM_H
