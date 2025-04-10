#include "addnewchatdialog.h"
#include "ui_addnewchatdialog.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QKeySequenceEdit>
#include <QLabel>
#include <QLineEdit>
#include <vector>

addNewChatDialog::addNewChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addNewChatDialog)
{
    ui->setupUi(this);
    this->DB = new ChatDatabase;
    DB->load();
    connect(ui->addChatButton, &QPushButton::clicked, this, &addNewChatDialog::addNewChatButtonPressed);
    for (int i = 0; i < 4; i++) {
        this->UsersLayouts.push_back(new QHBoxLayout);
        int userCount = UsersLayouts.size();

        this->UsersLayouts[userCount-1]->addWidget(new QLabel(QString::number(userCount)+".", this));

        QLineEdit* NUserName = new QLineEdit(this);
        NUserName->setPlaceholderText("Leave if dont want that one new user");
        this->UsersLayouts[userCount-1]->addWidget(NUserName);

        QKeySequenceEdit* NUserKeySequence = new QKeySequenceEdit(this);
        NUserKeySequence->setMaximumSequenceLength(1);
        this->UsersLayouts[userCount-1]->addWidget(NUserKeySequence);

        ui->UsersLayout->addLayout(this->UsersLayouts[userCount-1]);

    };
}

addNewChatDialog::~addNewChatDialog()
{
    qDebug() << "clsoed";
    delete this->DB;
    delete ui;
}

void addNewChatDialog::addNewChatButtonPressed() {
    if (ui->NewChatNameInput->text() != "") {
        // DB->createChat(chatId, chatName, users:shortcuts)
    };
    close();
}
