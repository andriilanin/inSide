#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QFrame>
#include <QScrollArea>
#include <QLabel>
#include <QString>
#include <QDebug>
#include "chatitem.h"

QString currentChatId = "";



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *scrollContent = new QWidget;
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollContent);
    for (int i = 0; i < 4; ++i) {
        ChatItem* newItem = new ChatItem("dasd", "sqweeqw", "123");

        scrollLayout->addWidget(newItem);
        scrollLayout->setSpacing(5);
        connect(newItem, &ChatItem::clicked, this, &MainWindow::handleChatClicks);
    };
    scrollLayout->addStretch();

    scrollContent->setLayout(scrollLayout);
    ui->scrollArea->setWidget(scrollContent);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleChatClicks(QString chatId) {
    qDebug() << chatId;
};
