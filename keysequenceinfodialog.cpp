#include "keysequenceinfodialog.h"
#include "ui_keysequenceinfodialog.h"
#include <QJsonObject>
#include <QHBoxLayout>
#include <QLabel>

KeySequenceInfoDialog::KeySequenceInfoDialog(QWidget *parent, const QString chatId)
    : QDialog(parent)
    , ui(new Ui::KeySequenceInfoDialog)
{
    ui->setupUi(this);
    setWindowTitle("Users");
    this->DB = new ChatDatabase();
    DB->load();
    QJsonObject chatObj = DB->getChatById(chatId);
    const QJsonArray usersArray = chatObj.value("Users").toArray();
    for (const QJsonValue& user : usersArray) {
        QJsonObject userObj = user.toObject();

        QHBoxLayout* currentUserLayout = new QHBoxLayout();
        currentUserLayout->addWidget(new QLabel(userObj.value("UserName").toString()));
        currentUserLayout->insertSpacerItem(1, new QSpacerItem(5, 0, QSizePolicy::Fixed));
        currentUserLayout->addWidget(new QLabel(userObj.value("KeySequence").toString()));
        ui->usersLayout->addLayout(currentUserLayout);
        ui->usersLayout->addSpacerItem(new QSpacerItem(0, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));
    };
    adjustSize();

}

KeySequenceInfoDialog::~KeySequenceInfoDialog()
{
    delete ui;
}
