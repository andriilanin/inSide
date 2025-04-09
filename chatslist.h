#ifndef CHATSLIST_H
#define CHATSLIST_H

#include <QWidget>
#include "chatdatabase.h"

namespace Ui {
class ChatsList;
}

class ChatsList : public QWidget
{
    Q_OBJECT

public:
    explicit ChatsList(QWidget *parent = nullptr);
    ~ChatsList();

protected:
    void handleChatClicks(QString chatId);
    void reloadChatsList();

private slots:
    void addNewChatButtonPressed();

private:
    ChatDatabase* DB;
    Ui::ChatsList *ui;

};

#endif // CHATSLIST_H
