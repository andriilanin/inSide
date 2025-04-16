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


    QString style = "color: rgb(228, 236, 242);\nborder-top-left-radius: 10px;\nborder-top-right-radius: 10px;\n";
    if (userName != "You") {
        style += "background: rgb(24,37,51);";
        ui->userName->setText(userName);
        ui->userName->setStyleSheet("color: rgb(179,140,208);\n");

    } else {
        style += "background: rgb(43, 82, 120);";
    };




    if (isOutGoing) {
        style += "border-bottom-left-radius: 10px;\n";
    } else {
        style += "border-bottom-right-radius: 10px;\n";
    };

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


