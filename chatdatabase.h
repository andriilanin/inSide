
#ifndef CHATDATABASE_H
#define CHATDATABASE_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QString>
#include <QDateTime>
struct ChatUser {
    QString userName;
    QString keySequence;
};

struct ChatMessage {
    QString userName;
    QString text;
    QString time;
};

class ChatDatabase : public QObject
{
    Q_OBJECT

public:
    explicit ChatDatabase(QObject* parent = nullptr);
    virtual ~ChatDatabase();

    bool load();
    bool save();

    QJsonArray getChats() const;
    QJsonObject getChatById(const QString& chatId) const;
    bool chatExists(const QString& chatId) const;

    bool createChat(const QString& chatId, const QString& chatName, const QList<ChatUser>& users);
    QString getUserNameByKeySequence(const QString& chatId, const QKeySequence& key) const;
    bool addMessage(const QString& chatId, const ChatMessage& message);

private:
    QString m_filePath = "C:/Users/whoami/Desktop/Projects/inSide/DB.json";
    QJsonObject m_data;
};

#endif // CHATDATABASE_H

