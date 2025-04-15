#include "addnewchatdialog.h"
#include "ui_addnewchatdialog.h"
#include <QRandomGenerator>
#include <QPushButton>
#include <QHBoxLayout>
#include <QKeySequenceEdit>
#include <QLabel>
#include <QLineEdit>
#include <vector>
#define DEFAULT_STYLE "background: rgb(14,22,33);"


addNewChatDialog::addNewChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addNewChatDialog)
{
    ui->setupUi(this);
    setWindowTitle("Add new chat");
    this->DB = new ChatDatabase;
    this->DB->load();

    connect(ui->AddNewUserAreaButton, &QPushButton::clicked, this, &addNewChatDialog::addNewUserArea);
    connect(ui->addChatButton, &QPushButton::clicked, this, &addNewChatDialog::addNewChatButtonPressed);
    addNewUserArea();

}

addNewChatDialog::~addNewChatDialog()
{
    delete this->DB;
    delete ui;
}

void addNewChatDialog::addNewUserArea() {
    this->UsersLayouts.push_back(new QHBoxLayout);
    int userCount = UsersLayouts.size();

    this->UsersLayouts[userCount-1]->addWidget(new QLabel(QString::number(userCount)+".", this));

    QLineEdit* NUserName = new QLineEdit(this);
    NUserName->setPlaceholderText("Leave if dont want that one new user");
    NUserName->setStyleSheet(DEFAULT_STYLE);
    this->UsersLayouts[userCount-1]->addWidget(NUserName);

    QKeySequenceEdit* NUserKeySequence = new QKeySequenceEdit(this);
    NUserKeySequence->setStyleSheet(DEFAULT_STYLE);
    NUserKeySequence->setMaximumSequenceLength(1);
    this->UsersLayouts[userCount-1]->addWidget(NUserKeySequence);

    ui->UsersLayout->insertLayout(ui->UsersLayout->count()-2,this->UsersLayouts[userCount-1]);
};

void addNewChatDialog::addNewChatButtonPressed() {
    if (ui->NewChatNameInput->text() != "") {
        QList<ChatUser> usersToAdd;

        for (QHBoxLayout* UL : UsersLayouts) {
            QString UserName = qobject_cast<QLineEdit*>(UL->itemAt(1)->widget())->text();
            if (UserName != "") {
                QString UserKeySequence = qobject_cast<QKeySequenceEdit*>(UL->itemAt(2)->widget())->keySequence().toString();
                usersToAdd.push_back({UserName, UserKeySequence});
            };
        }
        DB->createChat(QString::number(QRandomGenerator::global()->bounded(100000, 999999)), ui->NewChatNameInput->text(), usersToAdd);
    };
    close();
}
