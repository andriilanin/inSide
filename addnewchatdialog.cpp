#include "addnewchatdialog.h"
#include "ui_addnewchatdialog.h"
#include <QPushButton>


addNewChatDialog::addNewChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addNewChatDialog)
{
    ui->setupUi(this);
    this->DB = new ChatDatabase;
    DB->load();
    connect(ui->addChatButton, &QPushButton::clicked, this, &addNewChatDialog::addNewChatButtonPressed);
}

addNewChatDialog::~addNewChatDialog()
{
    delete ui;
}

void addNewChatDialog::addNewChatButtonPressed() {
    if (ui->NewChatNameInput->text() != "") {
        // DB->createChat(chatId, chatName, users:shortcuts)
    };
    close();
}
