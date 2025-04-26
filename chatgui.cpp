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
    , ui(new Ui::chatGUI)
{
    ui->setupUi(this);
    this->setChatId(chatId);
    this->DB = new ChatDatabase(this);
    loadGuiByChatId();
    connect(ui->keySequenceInfo, &QPushButton::clicked, this, &ChatGUI::keySequenceInfoDialogShow);
    connect(ui->deleteChatButton, &QPushButton::clicked, this, &ChatGUI::deleteChatDialogExec);
}

ChatGUI::~ChatGUI() {
    emit chatClosed();
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

    setupShortcuts();
    loadMessagesFromDBToArea();
};

void ChatGUI::keySequenceInfoDialogShow() {
    auto* KSID = new KeySequenceInfoDialog(this, getChatId());
    KSID->show();
};

void ChatGUI::deleteChatDialogExec() {

    auto* DCC = new deleteChatConfirm(this, getChatId());
    connect(DCC, &deleteChatConfirm::confirmSignal, this, [this](){
        emit reloadChatsList();
        emit chatClosed();
        this->close();
    });
    DCC->exec();
}

void ChatGUI::setupShortcuts() {

    const QJsonArray usersArray = DB->getChatById(this->chatId).value("Users").toArray();
    for (const QJsonValue& user : usersArray) {
        auto userObj = user.toObject();

        QKeySequence userKeySequence(userObj.value("KeySequence").toString());
        QShortcut* runtimeShortcut = new QShortcut(userKeySequence, this);

        connect(runtimeShortcut, &QShortcut::activated, this, [=]() {
            auto inputText = this->inputTextEdit->toPlainText();
            if (!inputText.trimmed().isEmpty()) {
                auto userName = DB->getUserNameByKeySequence(this->getChatId(), userKeySequence);
                ChatMessage msg = { userName, inputText, QDateTime::currentDateTime().toString(Qt::ISODate) };

                DB->addMessage(this->getChatId(), msg);
                addNewMessageToArea(msg);

                this->inputTextEdit->clear();
                emit reloadChatsList();
            }
        });
    }

    connect(this->inputTextEdit, &InputTextEdit::enterPressed, this, [=]() {
        auto inputText = this->inputTextEdit->toPlainText();
        if (!inputText.trimmed().isEmpty()){
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
        auto lastMessageUserName = lastMessageItem->getName();
        isSameUserName = message.userName == lastMessageUserName;
    }
    if (this->messageLayout) {
        MessageItem* newMessageItem = new MessageItem(this, message.text, message.userName, isOutGoing, isSameUserName);
        this->messageLayout->addWidget(newMessageItem, 0, (isOutGoing ? Qt::AlignRight : Qt::AlignLeft));
    }

    QTimer::singleShot(0, this, [this]() {
        qApp->processEvents();
        ui->messagesArea->widget()->adjustSize();
        QScrollBar* bar = ui->messagesArea->verticalScrollBar();
        bar->setValue(bar->maximum());
    });
};

void ChatGUI::loadMessagesFromDBToArea() {
    auto* messagesScrollContent = new QWidget(this);
    this->messageLayout = new QVBoxLayout(messagesScrollContent);
    this->messageLayout->setSpacing(4);
    this->messageLayout->setContentsMargins(10, 10, 10, 10);
    this->messageLayout->insertStretch(0);

    messagesScrollContent->setLayout(this->messageLayout);
    ui->messagesArea->setWidget(messagesScrollContent);

    const QJsonArray messagesArray = DB->getChatById(this->getChatId()).value("Messages").toArray();
    for (const QJsonValue& message : messagesArray) {
        auto messageObj = message.toObject();

        ChatMessage msg = { messageObj.value("UserName").toString(), messageObj.value("Text").toString(), messageObj.value("Time").toString() };
        addNewMessageToArea(msg);
    };
};

QString ChatGUI::getChatId(){
    return this->chatId;
};
