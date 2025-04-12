#include "messageitem.h"
#include "ui_messageitem.h"

MessageItem::MessageItem(QWidget *parent, QString text, QString userName, bool isOutGoing)
    : QWidget(parent)
    , ui(new Ui::MessageItem)
{

    ui->setupUi(this);
    ui->userName->setText(userName);
    ui->messageText->setText(text);
    QString style = "background: rgb(43, 82, 120);\ncolor: rgb(228, 236, 242);\nborder-top-left-radius: 20px;\nborder-top-right-radius: 20px;\n";
    if (isOutGoing) {
        style += "border-bottom-left-radius: 20px;\n";
    } else {
        style += "border-bottom-right-radius: 20px;\n";
    };
    ui->messageWidget->setStyleSheet(style);
    ui->messageWidget->adjustSize();
    ui->messageWidget->setFixedWidth(ui->messageWidget->width());
}

MessageItem::~MessageItem()
{
    delete ui;
}
