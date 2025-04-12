#ifndef CHATSLIST_H
#define CHATSLIST_H

#include <QWidget>
#include "chatdatabase.h"

class MainWindow;

namespace Ui {
class ChatsList;
}

class ChatsList : public QWidget
{
    Q_OBJECT

public:
    explicit ChatsList(MainWindow *parent = nullptr);
    ~ChatsList();
    void reloadChatsList();

protected:
    void handleChatClicks(QString chatId);


private slots:
    void addNewChatButtonPressed();

private:
    MainWindow* mainWindow;
    ChatDatabase* DB;
    Ui::ChatsList *ui;

};

#endif // CHATSLIST_H
