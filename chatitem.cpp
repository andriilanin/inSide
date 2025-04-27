#include "chatitem.h"
#include "ui_chatitem.h"
#include <QJsonObject>
#include <QResizeEvent>

#define HOVERED_STYLE "QFrame { border-bottom: solid black 2px;\n background-color: rgb(32,43,54);}"
#define DEFAULT_STYLE "QFrame { border-bottom: solid black 2px;\n background-color: rgb(23,33,43);}"


ChatItem::ChatItem( QWidget *parent, const QString &chatName, QJsonObject &lastMessageObj, int chatsListwidth, const QString &chatId )
    : QWidget(parent)
    , ui(new Ui::chatItem)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_Hover);

    this->chatId = chatId;
    this->fullTextToElide = lastMessageObj.value("Text").toString();

    ui->chatNameLabel->setText(chatName);
    QString userName = lastMessageObj.value("UserName").toString();
    ui->userNameLabel->setText(userName.isEmpty() ? "No message yet" : userName);

    elideTextByWidth(chatsListwidth);
}

ChatItem::~ChatItem()
{
    delete ui;
}

void ChatItem::elideTextByWidth(int width) {
    if (width - 40 <= 0) return;

    QFontMetrics fontMetric(ui->lastMessageLabel->font());
    QString elided = fontMetric.elidedText(this->fullTextToElide, Qt::ElideRight, width - 40);
    ui->lastMessageLabel->setText(elided);
};


void ChatItem::mousePressEvent(QMouseEvent* event) {
    emit clicked(this->chatId);
    QWidget::mousePressEvent(event);
};

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

