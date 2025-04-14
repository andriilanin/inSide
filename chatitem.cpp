#include "chatitem.h"
#include "ui_chatitem.h"
#include <QJsonObject>
#define HOVERED_STYLE "QFrame { border-bottom: solid black 2px;\n background-color: rgb(32,43,54);}"
#define DEFAULT_STYLE "QFrame { border-bottom: solid black 2px;\n background-color: rgb(23,33,43);}"
#include <QResizeEvent>

ChatItem::ChatItem(const QString &chatName, QJsonObject &lastMessageObj, const QString &chatId, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatItem)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_Hover);

    ui->ChatNameLabel->setText(chatName);
    ui->userNameLabel->setText( (lastMessageObj.value("UserName").toString() != ""? lastMessageObj.value("UserName").toString() : "No message yet") );
    ui->lastMessageLabel->setText(lastMessageObj.value("Text").toString());



    this->chatId = chatId;
}

ChatItem::~ChatItem()
{
    delete ui;
}

void ChatItem::mousePressEvent(QMouseEvent *event) {
    emit clicked(this->chatId);
    QWidget::mousePressEvent(event);
};

bool ChatItem::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::Enter)
        setStyleSheet(HOVERED_STYLE);
    else if (event->type() == QEvent::Leave)
        setStyleSheet(DEFAULT_STYLE);

    return QWidget::eventFilter(obj, event);
}

void ChatItem::enterEvent(QEnterEvent* event)
{
    setStyleSheet(HOVERED_STYLE);
    QWidget::enterEvent(event);
}

void ChatItem::leaveEvent(QEvent* event)
{
    setStyleSheet(DEFAULT_STYLE);
    QWidget::leaveEvent(event);
}

