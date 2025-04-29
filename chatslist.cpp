#include "chatslist.h"
#include "ui_chatslist.h"
#include "chatitem.h"
#include "chatdatabase.h"
#include "mainwindow.h"
#include "AddNewChatDialog.h"
#include <QPushButton>

ChatsList::ChatsList(MainWindow *parent)
    : QWidget(parent)
    , mainWindow(parent)
    , ui(new Ui::ChatsList)
{
    ui->setupUi(this);
    connect(ui->addNewChatButton, &QPushButton::clicked, this, &ChatsList::addNewChatButtonPressed);

    this->DB = new ChatDatabase(this);
    reloadChatsList();
}

ChatsList::~ChatsList()
{
    delete ui;
}

void ChatsList::resizeEvent(QResizeEvent* event) {
    emit resized(event);
}

void ChatsList::reloadChatsList() {
    QWidget *scrollContent = new QWidget;
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollContent);

    if (this->DB->load()) {
        const QJsonArray  chats = this->DB->getChats();
        for (const QJsonValue& chat : chats) {
            QJsonObject chatObj = chat.toObject();
            QJsonObject lastMessage = chatObj.value("Messages").toArray().last().toObject();

            ChatItem* newChatItem = new ChatItem(this, chatObj.value("ChatName").toString(), lastMessage, this->size().width(), chatObj.value("ChatId").toString() );
            connect(this, &ChatsList::resized, newChatItem, [newChatItem](QResizeEvent *event) {
                newChatItem->elideTextByWidth(event->size().width());
            });
            connect(newChatItem, &ChatItem::clicked, mainWindow, &MainWindow::setCurrentChatGUIObj);

            scrollLayout->addWidget(newChatItem);
        };
    }
    scrollLayout->setContentsMargins(0,0,0,0);
    scrollLayout->addStretch();

    scrollContent->setLayout(scrollLayout);
    ui->scrollArea->setWidget(scrollContent);

};

void ChatsList::addNewChatButtonPressed() {
    AddNewChatDialog* dialog = new AddNewChatDialog(this);
    connect(dialog, &AddNewChatDialog::accepted, this, &ChatsList::reloadChatsList);
    dialog->exec();
};
