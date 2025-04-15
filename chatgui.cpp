#include "chatgui.h"
#include "ui_chatgui.h"
#include "chatdatabase.h"
#include <QDebug>
#include <QKeySequence>
#include <QShortcut>
#include "messageitem.h"
#include "inputtextedit.h"
#include "keysequenceinfodialog.h"
#include "deletechatconfirm.h"
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
    connect(ui->KeySequenceInfo, &QPushButton::clicked, this, &ChatGUI::KeySequenceInfoDialogShow);
    connect(ui->deleteChatButton, &QPushButton::clicked, this, &ChatGUI::deleteChatDialogExec);
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
    this->inputTextEdit->setPlaceholderText("Write a message...");
    ui->inputTextEditLayout->addWidget(this->inputTextEdit);

    connectUsersKeySequences();
    loadMessagesFromDBToArea();
};

void ChatGUI::KeySequenceInfoDialogShow() {
    KeySequenceInfoDialog* KSID = new KeySequenceInfoDialog(this, getChatId());
    KSID->show();
};

void ChatGUI::deleteChatDialogExec() {
    deleteChatConfirm* DCC = new deleteChatConfirm(this, getChatId());
    connect(DCC, &deleteChatConfirm::confirmSignal, this, [this](){
        this->close();
    });
    DCC->exec();
    emit reloadChatsList();
}

void ChatGUI::connectUsersKeySequences() {

    QJsonArray usersArray = DB->getChatById(this->chatId).value("Users").toArray();
    for (const QJsonValueRef& user : usersArray) {
        QJsonObject userObj = user.toObject();

        QKeySequence* userKeySequence = new QKeySequence(userObj.value("KeySequence").toString());
        QShortcut* runtimeShortcut = new QShortcut(*userKeySequence, this);

        connect(runtimeShortcut, &QShortcut::activated, this, [=]() {
            QString inputText = this->inputTextEdit->toPlainText();
            if (!inputText.trimmed().isEmpty()) {
                QString userName = DB->getUserNameByKeySequence(this->getChatId(), *userKeySequence);
                ChatMessage msg = { userName, inputText, QDateTime::currentDateTime().toString(Qt::ISODate) };

                DB->addMessage(this->getChatId(), msg);
                addNewMessageToArea(msg);

                this->inputTextEdit->clear();
                emit reloadChatsList();
            }
        });
    }

    connect(this->inputTextEdit, &InputTextEdit::enterPressed, this, [=]() {
        QString inputText = this->inputTextEdit->toPlainText();
        if (inputText != ""){
            ChatMessage msg = { "You", inputText, QDateTime::currentDateTime().toString(Qt::ISODate) };

            DB->addMessage(this->getChatId(), msg);
            addNewMessageToArea(msg);

            this->inputTextEdit->clear();
            emit reloadChatsList();
        }
    });
}

void ChatGUI::addNewMessageToArea(const ChatMessage& message) {
    bool isOutGoing(message.userName=="You");

    MessageItem* lastMessageItem = qobject_cast<MessageItem*>(messageLayout->itemAt(messageLayout->count() - 1)->widget());
    bool isSameUserName = false;

    if (lastMessageItem) {
        QString lastMessageUserName = lastMessageItem->getName();
        isSameUserName = message.userName == lastMessageUserName;
    }
    if (this->messageLayout) {
        MessageItem* newMessageItem = new MessageItem(this, message.text, message.userName, isOutGoing, isSameUserName);
        this->messageLayout->addWidget(newMessageItem, 0, (isOutGoing ? Qt::AlignRight : Qt::AlignLeft));
    }

    QTimer::singleShot(0, this, [this]() {
        qApp->processEvents();
        ui->MessagesArea->widget()->adjustSize();
        QScrollBar* bar = ui->MessagesArea->verticalScrollBar();
        bar->setValue(bar->maximum());
    });
};

void ChatGUI::loadMessagesFromDBToArea() {

    QWidget* messagesScrollContent = new QWidget();
    this->messageLayout = new QVBoxLayout(messagesScrollContent);
    this->messageLayout->setSpacing(4);
    this->messageLayout->setContentsMargins(10, 10, 10, 10);
    this->messageLayout->insertStretch(0);

    messagesScrollContent->setLayout(this->messageLayout);
    ui->MessagesArea->setWidget(messagesScrollContent);

    if (DB->load()) {
        QJsonArray messagesArray = DB->getChatById(this->getChatId()).value("Messages").toArray();
        for (const QJsonValueRef& message : messagesArray) {
            QJsonObject messageObj = message.toObject();

            ChatMessage msg = {messageObj.value("UserName").toString(), messageObj.value("Text").toString(), messageObj.value("Time").toString() };
            addNewMessageToArea(msg);
        };
    };
};

QString ChatGUI::getChatId(){
    return this->chatId;
};

QString ChatGUI::getChatName(){
    return this->chatName;
};
