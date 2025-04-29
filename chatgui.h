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
    explicit ChatGUI(QWidget *parent = nullptr, const QString chatId = "");
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

    Ui::ChatGUI *ui;
};

#endif // CHATGUI_H
