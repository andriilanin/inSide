#include "chatitem.h"
#include "ui_chatitem.h"
#include <QJsonObject>
#include <QResizeEvent>

#define HOVERED_STYLE "QFrame { border-bottom: solid black 2px;\n background-color: rgb(32,43,54);}"
#define DEFAULT_STYLE "QFrame { border-bottom: solid black 2px;\n background-color: rgb(23,33,43);}"


ChatItem::ChatItem( QWidget *parent, const QString &chatName, QJsonObject &lastMessageObj, int ChatsListwidth, const QString &chatId )
    : QWidget(parent)
    , ui(new Ui::ChatItem)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_Hover);

    this->chatId = chatId;
    this->fullTextToElide = lastMessageObj.value("Text").toString();

    ui->ChatNameLabel->setText(chatName);
    ui->userNameLabel->setText(lastMessageObj.value("UserName").toString() != "" ? lastMessageObj.value("UserName").toString() : "No message yet");
    elideTextByWidth(ChatsListwidth);
}

ChatItem::~ChatItem()
{
    delete ui;
}

void ChatItem::applyElide(int width) {
    if (width - 30 <= 0) return;

    QFontMetrics fontMetric(ui->lastMessageLabel->font());
    QString elided = fontMetric.elidedText(this->fullTextToElide, Qt::ElideRight, width - 30);
    ui->lastMessageLabel->setText(elided);
}

void ChatItem::elideTextByWidth(QResizeEvent* event) {
    applyElide(event->size().width());
};

void ChatItem::elideTextByWidth(int width) {
    applyElide(width);
};


void ChatItem::mousePressEvent(QMouseEvent* event) {
    emit clicked(this->chatId);
    // QWidget::mousePressEvent(event);
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

