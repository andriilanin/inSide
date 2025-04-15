#ifndef CHATGUI_H
#define CHATGUI_H

#include <QWidget>
#include <chatdatabase.h>
#include <QScrollArea>
#include <QVBoxLayout>
#include <inputtextedit.h>

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
    void addNewMessageToArea(const ChatMessage& message);

    void KeySequenceInfoDialogShow();
    void deleteChatDialogExec();

signals:
    void reloadChatsList();

private:
    InputTextEdit* inputTextEdit = nullptr;
    QString chatId;
    QString chatName;
    QVBoxLayout* messageLayout = nullptr;

    Ui::ChatGUI *ui;
};

#endif // CHATGUI_H
