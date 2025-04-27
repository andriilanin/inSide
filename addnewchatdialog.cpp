#include "addnewchatdialog.h"
#include "ui_addnewchatdialog.h"
#include <QRandomGenerator>
#include <QPushButton>
#include <QHBoxLayout>
#include <QKeySequenceEdit>
#include <QLabel>
#include <QLineEdit>
#include <vector>
#include <QMessageBox>
#define DEFAULT_COLOR "background: rgb(14,22,33);"


addNewChatDialog::addNewChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addNewChatDialog)
{
    ui->setupUi(this);
    setWindowTitle("Add new chat");
    this->DB = new ChatDatabase;
    this->DB->load();

    connect(ui->addNewUserAreaButton, &QPushButton::clicked, this, &addNewChatDialog::addNewUserArea);
    connect(ui->deleteNewUserAreaButton, &QPushButton::clicked, this, &addNewChatDialog::deleteNewUserArea);
    connect(ui->addChatButton, &QPushButton::clicked, this, &addNewChatDialog::addNewChatButtonPressed);

    addNewUserArea();

}

addNewChatDialog::~addNewChatDialog()
{
    delete this->DB;
    delete ui;
}

void addNewChatDialog::addNewUserArea() {
    int userCount = usersLayouts.size();
    this->usersLayouts.push_back(new QHBoxLayout(this));

    this->usersLayouts[userCount]->addWidget(new QLabel(QString::number(userCount+1)+".", this));

    QLineEdit* UserName = new QLineEdit(this);
    UserName->setPlaceholderText("Enter new user name");
    UserName->setStyleSheet(DEFAULT_COLOR);
    this->usersLayouts[userCount]->addWidget(UserName);

    QKeySequenceEdit* UserKeySequence = new QKeySequenceEdit(this);
    UserKeySequence->setStyleSheet(DEFAULT_COLOR);
    UserKeySequence->setMaximumSequenceLength(1);

    this->usersLayouts[userCount]->addWidget(UserKeySequence);

    ui->usersLayout->insertLayout(userCount, this->usersLayouts[userCount]);
};

void addNewChatDialog::deleteNewUserArea() {
    if (!this->usersLayouts.empty()) {
        QLayoutItem* item = ui->usersLayout->takeAt(ui->usersLayout->count()-3);
        QLayout* childLayout = item->layout();
        if (childLayout) {
            this->usersLayouts.pop_back();
            while (QLayoutItem* childItem = childLayout->takeAt(0)) {
                if (QWidget* widget = childItem->widget()) {
                    widget->setParent(nullptr);
                    widget->deleteLater();
                }
                delete childItem;
            }
            delete childLayout;
        }
    }
}

void addNewChatDialog::addNewChatButtonPressed() {
    if (!ui->newChatNameInput->text().isEmpty()) {
        QList<ChatUser> usersToAdd;

        for (QHBoxLayout* userLayout : usersLayouts) {
            QString userName = qobject_cast<QLineEdit*>(userLayout->itemAt(1)->widget())->text();
            if (!userName.isEmpty()) {
                QString userKeySequence = qobject_cast<QKeySequenceEdit*>(userLayout->itemAt(2)->widget())->keySequence().toString();
                usersToAdd.push_back({userName, userKeySequence});
            };
        }
        this->DB->createChat(QString::number(QRandomGenerator::global()->bounded(100000, 999999)), ui->newChatNameInput->text(), usersToAdd);
        emit accepted();
        close();
    } else {
        QMessageBox::warning(this, tr("Error"), tr("The \"Chat Name\" field cannot be empty."));
    };

}
