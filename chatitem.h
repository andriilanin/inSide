#ifndef CHATITEM_H
#define CHATITEM_H

#include <QWidget>
#include <QEvent>
#include <QResizeEvent>
#include <QJsonObject>

namespace Ui {
class chatItem;
}

class ChatItem : public QWidget
{
    Q_OBJECT

public:
    explicit ChatItem( QWidget *parent, const QString &chatName, QJsonObject &lastMessageObj, int chatsListwidth, const QString &chatId );
    ~ChatItem();
    void elideTextByWidth(QResizeEvent* event);

protected:

    void elideTextByWidth(int width);
    void mousePressEvent(QMouseEvent *event) override;
    bool eventFilter(QObject* obj, QEvent* event) override;

    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

    void applyElide(int width);

signals:
    void clicked(QString clickedChatId);

private:
    QString fullTextToElide;
    QString chatId;
    Ui::chatItem *ui;
};

#endif // CHATITEM_H
