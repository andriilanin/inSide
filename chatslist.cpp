#include "chatslist.h"
#include "ui_chatslist.h"
#include "chatitem.h"
#include "chatdatabase.h"
#include "mainwindow.h"
#include <QPushButton>

ChatsList::ChatsList(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatsList)
{
    ui->setupUi(this);
    connect(ui->addNewChatButton, &QPushButton::clicked, this, &ChatsList::addNewChatButtonPressed);

    this->DB = new ChatDatabase();
    reloadChatsList();
}

ChatsList::~ChatsList()
{
    delete ui;
}

void ChatsList::reloadChatsList() {
    QWidget *scrollContent = new QWidget;
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollContent);
    scrollLayout->setSpacing(5);

    if (DB->load()) {
        for (const QJsonValue& chat : DB->getChats()) {
            QJsonObject chatObj = chat.toObject();
            QJsonObject lastMessage = chatObj.value("messages").toArray().last().toObject();
            ChatItem* newChatItem= new ChatItem(chatObj.value("chatName").toString(), lastMessage, chatObj.value("chatId").toString());
            connect(newChatItem, &ChatItem::clicked, qobject_cast<MainWindow*>(this->parent()), &MainWindow::setCurrentChatGUIObj);
            scrollLayout->addWidget(newChatItem);
        };
    }
    scrollLayout->setContentsMargins(0,0,0,0);
    scrollLayout->addStretch();

    scrollContent->setLayout(scrollLayout);
    ui->scrollArea->setWidget(scrollContent);

};

void ChatsList::addNewChatButtonPressed() {
    qDebug() << "addNewChatButton pressed";
};
