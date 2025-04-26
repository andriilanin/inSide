#ifndef CHATGUI_H
#define CHATGUI_H

#include <QWidget>
#include <chatdatabase.h>
#include <QScrollArea>
#include <QVBoxLayout>
#include <inputtextedit.h>

namespace Ui {
class chatGUI;
}

class ChatGUI : public QWidget
{
    Q_OBJECT

public:
    explicit ChatGUI(const QString chatId, QWidget *parent = nullptr);
    ~ChatGUI();

    void setChatId(const QString chatId);
    void addNewMessageToArea(const ChatMessage& message);
    QString getChatId();
    void loadGuiByChatId();
    void setupShortcuts();
    void reloadMessagesInChat();
    void loadMessagesFromDBToArea();
    void keySequenceInfoDialogShow();
    void deleteChatDialogExec();

signals:
    void reloadChatsList();
    void chatClosed();

protected:


private:
    ChatDatabase* DB;
    QString chatId;

    InputTextEdit* inputTextEdit = nullptr;
    QVBoxLayout* messageLayout = nullptr;

    Ui::chatGUI *ui;
};

#endif // CHATGUI_H
