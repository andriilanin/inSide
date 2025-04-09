#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QFrame>
#include <QScrollArea>
#include <QLabel>
#include <QString>
#include <QDebug>
#include "chatgui.h"
#include "chatslist.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ChatsListLayout->addWidget(new ChatsList(this));

    // ui->currentChatLayout->addWidget(new ChatGUI("chat1"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCurrentChatGUIObj(QString chatId) {
    ui->selectChatLabel->hide();
    if (this->currentChatGUIObj != nullptr) {
        delete currentChatGUIObj;
    };
    this->currentChatGUIObj = new ChatGUI(chatId);
    ui->currentChatLayout->addWidget(this->currentChatGUIObj);
};

