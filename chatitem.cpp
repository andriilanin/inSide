#include "chatitem.h"
#include "ui_chatitem.h"
#include <QJsonObject>

ChatItem::ChatItem(const QString &chatName, QJsonObject &lastMessageObj, const QString &chatId, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatItem)
{
    ui->setupUi(this);
    ui->ChatNameLabel->setText(chatName);
    ui->userNameLabel->setText( (lastMessageObj.value("name").toString() != ""? lastMessageObj.value("name").toString() : "No message yet") );
    ui->lastMessageLabel->setText(lastMessageObj.value("text").toString());
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
