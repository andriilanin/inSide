#include "deletechatconfirm.h"
#include "ui_deletechatconfirm.h"
#include <QPushButton>

deleteChatConfirm::deleteChatConfirm(QWidget *parent, const QString chatId)
    : QDialog(parent)
    , ui(new Ui::deleteChatConfirm)
{
    ui->setupUi(this);
    this->DB = new ChatDatabase();
    DB->load();
    this->chatId = chatId;
    connect(ui->confirmButton, &QPushButton::clicked, this, &deleteChatConfirm::confirm);
    connect(ui->cancelButton, &QPushButton::clicked, this, &deleteChatConfirm::cancel);
}

deleteChatConfirm::~deleteChatConfirm()
{
    delete ui;
}

void deleteChatConfirm::confirm() {
    this->DB->deleteChatById(this->chatId);
    close();
    emit confirmSignal();
};

void deleteChatConfirm::cancel() {
    close();
};
