#ifndef CHATGUI_H
#define CHATGUI_H

#include <QWidget>
#include <chatdatabase.h>
#include <QScrollArea>

namespace Ui {
class ChatGUI;
}

class ChatGUI : public QWidget
{
    Q_OBJECT

public:
    explicit ChatGUI(const QString chatId, QWidget *parent = nullptr);
    ~ChatGUI();

    void setChatId(const QString chatId);
    ChatDatabase* DB;
    QString getChatId();
    QString getChatName();
    void loadGuiByChatId();
    void connectUsersKeySequences();
    void reloadMessagesInChat();
    void loadMessagesFromDBToArea();

signals:
    void reloadChatsList();

private:
    QString chatId;
    QString chatName;

    Ui::ChatGUI *ui;
};

#endif // CHATGUI_H
