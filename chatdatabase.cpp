#include "chatdatabase.h"
#include <QDebug>

ChatDatabase::ChatDatabase(QObject* parent) : QObject(parent) {}

ChatDatabase::~ChatDatabase() {}

bool ChatDatabase::load() {
    QFile file(m_filePath);
    if (!file.exists()) {
        m_data = { { "chats", QJsonArray() } };
        return save();
    }

    if (!file.open(QIODevice::ReadOnly)) return false;

    QByteArray rawData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(rawData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        m_data = { { "chats", QJsonArray() } };
        return save();
    }

    m_data = doc.object();
    return true;
}

bool ChatDatabase::save() {
    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly)) return false;

    QJsonDocument doc(m_data);
    file.write(doc.toJson());
    file.close();
    return true;
}

QJsonArray ChatDatabase::getChats() const {
    return m_data.value("chats").toArray();
}

QJsonObject ChatDatabase::getChatById(const QString& chatId) const {
    for (const QJsonValue& val : getChats()) {
        QJsonObject obj = val.toObject();
        if (obj["ChatId"].toString() == chatId)
            return obj;
    }
    return QJsonObject();
}

bool ChatDatabase::chatExists(const QString& chatId) const {
    return !getChatById(chatId).isEmpty();
}

bool ChatDatabase::createChat(const QString& chatId, const QString& chatName, const QList<ChatUser>& users) {
    if (chatExists(chatId)) return false;

    QJsonArray usersArray;
    for (const ChatUser& user : users) {
        usersArray.append(QJsonObject{
            { "UserName", user.userName },
            { "KeySequence", user.keySequence }
        });
    }

    QJsonObject chat {
        { "ChatName", chatName },
        { "ChatId", chatId },
        { "Users", usersArray },
        { "Messages", QJsonArray() }
    };

    QJsonArray chats = getChats();
    chats.append(chat);
    m_data["chats"] = chats;
    return save();
}

bool ChatDatabase::addMessage(const QString& chatId, const ChatMessage& message) {
    QJsonArray chats = getChats();
    for (int i = 0; i < chats.size(); ++i) {
        QJsonObject chat = chats[i].toObject();
        if (chat["ChatId"].toString() == chatId) {
            QJsonArray messages = chat["Messages"].toArray();
            messages.append(QJsonObject{
                { "UserName", message.userName },
                { "Text", message.text },
                { "Time", message.time }
            });
            chat["Messages"] = messages;
            chats[i] = chat;
            m_data["chats"] = chats;
            return save();
        }
    }
    return false;
}
