#include "chatitem.h"
#include "ui_chatitem.h"

ChatItem::ChatItem(const QString &name, const QString &lastMessage, const QString &chatId, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatItem)
{
    ui->setupUi(this);
    ui->labelName->setText(name);
    ui->labelMessage->setText(lastMessage);
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
