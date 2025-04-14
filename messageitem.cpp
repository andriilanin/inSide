#include "messageitem.h"
#include "ui_messageitem.h"


QString splitLongWords(const QString& text, int maxLength = 50)
{
    QStringList words = text.split(" ");
    QStringList result;

    for (QString word : words) {
        while (word.length() > maxLength) {
            result << word.left(maxLength);
            word = word.mid(maxLength);
        }
        result << word;
    }

    return result.join(" ");
}


MessageItem::MessageItem(QWidget *parent, QString text, QString userName, bool isOutGoing, bool isSameUserName)
    : QWidget(parent)
    , ui(new Ui::MessageItem)
{

    ui->setupUi(this);
    ui->messageText->setMaximumWidth(400);

    QString style = "color: rgb(228, 236, 242);\nborder-top-left-radius: 10px;\nborder-top-right-radius: 10px;\n";

    if (isSameUserName || userName == "You") {
        ui->userName->hide();
    };

    if (userName != "You") {
        style += "background: rgb(24,37,51);";
        ui->userName->setText(userName);
        ui->userName->setStyleSheet("color: rgb(179,140,208);\n");

    }if (userName == "You") {
        style += "background: rgb(43, 82, 120);";
    };



    ui->messageText->setText(splitLongWords(text));

    if (isOutGoing) {
        style += "border-bottom-left-radius: 10px;\n";
    } else {
        style += "border-bottom-right-radius: 10px;\n";
    };
    ui->messageWidget->setStyleSheet(style);
    ui->messageWidget->adjustSize();
    ui->messageWidget->setFixedWidth(ui->messageWidget->width());
}

MessageItem::~MessageItem()
{
    delete ui;
}

QString MessageItem::getName() {
    return ui->userName->text();
};


