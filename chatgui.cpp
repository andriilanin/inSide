#include "chatgui.h"
#include "ui_chatgui.h"
#include "chatdatabase.h"
#include <QDebug>
#include <QKeySequence>
#include <QShortcut>
#include "messageitem.h"
#include <QSpacerItem>
#include <QScrollBar>
#include <QTimer>
ChatGUI::ChatGUI(const QString chatId, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatGUI)
{
    ui->setupUi(this);
    this->setChatId(chatId);
    this->DB = new ChatDatabase();
    loadGuiByChatId();
}

ChatGUI::~ChatGUI()
{
    delete ui;
}



void ChatGUI::setChatId(const QString chatId){
    this->chatId = chatId;
};



void ChatGUI::loadGuiByChatId() {
    DB->load();
    ui->labelName->setText(DB->getChatById(this->chatId).value("ChatName").toString());
    connectUsersKeySequences();
    loadMessagesFromDBToArea();
};



void ChatGUI::loadMessagesFromDBToArea() {

    QWidget *scrollContent = new QWidget;
    QVBoxLayout* scrollVLayout = new QVBoxLayout(scrollContent);
    scrollVLayout->setSpacing(5);

    if (DB->load()) {
        const QJsonArray* messagesArray = new QJsonArray(DB->getChatById(this->getChatId()).value("Messages").toArray());
        for (const QJsonValue& message : *messagesArray) {
            QJsonObject messageObj = message.toObject();
            bool* isOutGoing = new bool((messageObj.value("UserName").toString()=="self"));

            MessageItem* newChatItem = new MessageItem(this, messageObj.value("Text").toString(), messageObj.value("UserName").toString(), *isOutGoing);

            scrollVLayout->addWidget(newChatItem, 0, (*isOutGoing ? Qt::AlignRight : Qt::AlignLeft));
            delete isOutGoing;
        };
        delete messagesArray;
    }

    scrollVLayout->setContentsMargins(0,0,0,0);

    scrollVLayout->insertStretch(0);
    scrollContent->setLayout(scrollVLayout);
    ui->MessagesArea->setWidget(scrollContent);

    QTimer::singleShot(0, [this]() {
        QScrollBar* bar = ui->MessagesArea->verticalScrollBar();
        bar->setValue(bar->maximum());
    });
}

void ChatGUI::connectUsersKeySequences() {

    const QJsonArray usersArray = DB->getChatById(this->chatId).value("Users").toArray();
    for (const QJsonValue& user : usersArray) {
        QJsonObject userObj = user.toObject();

        QKeySequence* userKeySequence = new QKeySequence(userObj.value("KeySequence").toString());
        QShortcut* runtimeShortcut = new QShortcut(*userKeySequence, this);

        connect(runtimeShortcut, &QShortcut::activated, this, [=]() {
            QString inputText = this->ui->InputLineEdit->text();
            if (inputText != ""){
                ChatMessage msg = { DB->getUserNameByKeySequence(this->getChatId(), *userKeySequence), inputText, QDateTime::currentDateTime().toString(Qt::ISODate) };
                DB->addMessage(this->getChatId(), msg);
            }
            this->ui->InputLineEdit->clear();
            emit reloadChatsList();
        });
    }




}


QString ChatGUI::getChatId(){
    return this->chatId;
};

QString ChatGUI::getChatName(){
    return this->chatName;
};
