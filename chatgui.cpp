#include "chatgui.h"
#include "ui_chatgui.h"
#include "chatdatabase.h"
#include <QDebug>
#include <QKeySequence>
#include <QShortcut>
#include "messageitem.h"
#include "inputtextedit.h"
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
    this->inputTextEdit = new InputTextEdit(this);
    ui->inputTextEditLayout->addWidget(this->inputTextEdit);
    connectUsersKeySequences();
    loadMessagesFromDBToArea();
};

void ChatGUI::addNewMessageToArea(const ChatMessage& message) {
    bool isOutGoing = message.userName=="You";

    MessageItem* lastMessageItem = qobject_cast<MessageItem*>(messageLayout->itemAt(messageLayout->count() - 1)->widget());
    bool isSameUserName = false;
    if (lastMessageItem) {
        QString lastMessageUserName = lastMessageItem->getName();
        isSameUserName = message.userName == lastMessageUserName;
    }
    if (this->messageLayout) {
        this->messageLayout->addWidget(new MessageItem(this, message.text, message.userName, isOutGoing, isSameUserName), 0, isOutGoing ? Qt::AlignRight : Qt::AlignLeft);
    }


    QTimer::singleShot(0, this, [this]() {
        qApp->processEvents();
        ui->MessagesArea->widget()->adjustSize();
        QScrollBar* bar = ui->MessagesArea->verticalScrollBar();
        bar->setValue(bar->maximum());
    });
};

void ChatGUI::loadMessagesFromDBToArea() {

    QWidget *scrollContent = new QWidget;
    QVBoxLayout* scrollVLayout = new QVBoxLayout(scrollContent);
    scrollVLayout->setSpacing(4);

    scrollVLayout->setContentsMargins(10, 10, 10, 10);

    scrollVLayout->insertStretch(0);
    scrollContent->setLayout(scrollVLayout);
    ui->MessagesArea->setWidget(scrollContent);

    this->messageLayout = scrollVLayout;


    if (DB->load()) {
        const QJsonArray* messagesArray = new QJsonArray(DB->getChatById(this->getChatId()).value("Messages").toArray());
        for (const QJsonValue& message : *messagesArray) {
            QJsonObject messageObj = message.toObject();

            ChatMessage msg = {messageObj.value("UserName").toString(), messageObj.value("Text").toString(), messageObj.value("Time").toString() };
            addNewMessageToArea(msg);


        };
        delete messagesArray;
    }



}

void ChatGUI::connectUsersKeySequences() {

    const QJsonArray usersArray = DB->getChatById(this->chatId).value("Users").toArray();
    for (const QJsonValue& user : usersArray) {
        QJsonObject userObj = user.toObject();

        QKeySequence* userKeySequence = new QKeySequence(userObj.value("KeySequence").toString());
        QShortcut* runtimeShortcut = new QShortcut(*userKeySequence, this);

        connect(runtimeShortcut, &QShortcut::activated, this, [=]() {

            QString inputText = this->inputTextEdit->toPlainText();
            if (!inputText.trimmed().isEmpty()) {
                ChatMessage msg = { DB->getUserNameByKeySequence(this->getChatId(), *userKeySequence), inputText, QDateTime::currentDateTime().toString(Qt::ISODate) };
                addNewMessageToArea(msg);
                DB->addMessage(this->getChatId(), msg);
                this->inputTextEdit->clear();
                emit reloadChatsList();
            }
        });
    }
    connect(this->inputTextEdit, &InputTextEdit::enterPressed, this, [=]() {
        QString inputText = this->inputTextEdit->toPlainText();
        if (inputText != ""){
            ChatMessage msg = { "You", inputText, QDateTime::currentDateTime().toString(Qt::ISODate) };
            addNewMessageToArea(msg);
            DB->addMessage(this->getChatId(), msg);
            this->inputTextEdit->clear();
            emit reloadChatsList();
        }

    });
}





QString ChatGUI::getChatId(){
    return this->chatId;
};

QString ChatGUI::getChatName(){
    return this->chatName;
};
