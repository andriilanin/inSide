#include "addnewchatdialog.h"
#include "ui_addnewchatdialog.h"

addNewChatDialog::addNewChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addNewChatDialog)
{
    ui->setupUi(this);
}

addNewChatDialog::~addNewChatDialog()
{
    delete ui;
}
