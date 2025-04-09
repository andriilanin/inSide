#include "chatgui.h"
#include "ui_chatgui.h"
#include "chatdatabase.h"
#include <QDebug>

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
    ui->labelName->setText(DB->getChatById(this->chatId).value("chatName").toString());

};

QString ChatGUI::getChatId(){
    return this->chatId;
};

QString ChatGUI::getChatName(){
    return this->chatName;
};
