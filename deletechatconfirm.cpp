#include "DeleteChatConfirm.h"
#include "ui_DeleteChatConfirm.h"
#include <QPushButton>

DeleteChatConfirm::DeleteChatConfirm(QWidget *parent, const QString chatId)
    : QDialog(parent)
    , ui(new Ui::DeleteChatConfirm)
{
    ui->setupUi(this);
    this->DB = new ChatDatabase(this);
    this->DB->load();
    this->chatId = chatId;
    connect(ui->confirmButton, &QPushButton::clicked, this, &DeleteChatConfirm::confirm);
    connect(ui->cancelButton, &QPushButton::clicked, this, &DeleteChatConfirm::cancel);
}

DeleteChatConfirm::~DeleteChatConfirm()
{
    delete ui;
}

void DeleteChatConfirm::confirm() {
    this->DB->deleteChatById(this->chatId);
    close();
    emit confirmSignal();
};

void DeleteChatConfirm::cancel() {
    close();
};
