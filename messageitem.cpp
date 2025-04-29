#include "messageitem.h"
#include "ui_messageitem.h"
#define outGoingBackground "background: rgb(43, 82, 120);\n"
#define inComingBackground "background: rgb(24,37,51);\n"
#define userNameStyle "color: rgb(179,140,208);\n"

QString wrapText(const QString& text, int maxLineLength) {
    QStringList lines;
    QString currentLine;

    for (const QChar& ch : text) {
        if (ch == '\n' || currentLine.length() >= maxLineLength) {
            lines.append(currentLine.trimmed());
            currentLine.clear();
        }
        if (ch != '\n') currentLine += ch;
    }

    if (!currentLine.isEmpty()) {
        lines.append(currentLine.trimmed());
    }
    return lines.join("\n");
}

MessageItem::MessageItem(QWidget *parent, QString text, QString userName, bool isOutGoing, bool isSameUserName)
    : QWidget(parent)
    , ui(new Ui::MessageItem)
{

    ui->setupUi(this);
    if (isSameUserName || userName == "You") {
        ui->userName->hide();
    };

    QString style = ui->messageWidget->styleSheet();

    if (userName != "You") {
        style += inComingBackground;
        ui->userName->setText(userName);
        ui->userName->setStyleSheet(userNameStyle);
    } else {
        style += outGoingBackground;
    };


    style += "border-bottom-";
    style += ( isOutGoing ? "left" : "right" );
    style += "-radius: 10px;\n";

    ui->messageText->setText(wrapText(text, 72));
    ui->messageWidget->setStyleSheet(style);
}

MessageItem::~MessageItem()
{
    delete ui;
}

QString MessageItem::getName() {
    return ui->userName->text();
};


