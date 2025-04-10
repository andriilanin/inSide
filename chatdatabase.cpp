#include "chatdatabase.h"


ChatDatabase::ChatDatabase(QObject* parent)
    : QObject(parent)
{
}

ChatDatabase::~ChatDatabase()
{
}

bool ChatDatabase::load()
{
    QFile file(m_filePath);

    if (!file.exists()) {
        qWarning() << "Файл не найден, создаём новый:" << m_filePath;

        // Создаём пустую структуру
        m_data = QJsonObject{
            { "chats", QJsonArray() }
        };

        return save(); // Сохраняем и возвращаем true
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Не удалось открыть файл:" << m_filePath;
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    if (data.isEmpty()) {
        qWarning() << "Файл пустой, инициализируем базу...";
        m_data = QJsonObject{
            { "chats", QJsonArray() }
        };
        return save();
    }

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "Ошибка парсинга:" << parseError.errorString();
        m_data = QJsonObject{
            { "chats", QJsonArray() }
        };
        return save(); // Перезаписываем повреждённый файл
    }

    m_data = doc.object();
    return true;
}

bool ChatDatabase::save()
{
    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    QJsonDocument doc(m_data);
    file.write(doc.toJson());
    file.close();
    return true;
}

QJsonArray ChatDatabase::getChats() const
{
    return m_data.value("chats").toArray();
}

QJsonObject ChatDatabase::getChatById(const QString& chatId) const
{
    QJsonArray chats = m_data.value("chats").toArray();
    for (const QJsonValue& val : chats) {
        if (!val.isObject()) continue;

        QJsonObject obj = val.toObject();
        QString currentId = obj.value("chatId").toString();

        if (currentId == chatId) {
            return obj;
        }
    }
    return QJsonObject(); // Пусто = не найден
}

bool ChatDatabase::chatExists(const QString& chatId) const
{
    return !getChatById(chatId).isEmpty();
}

bool ChatDatabase::createChat(const QString& chatId)
{
    if (chatExists(chatId))
        return false;

    QJsonObject newChat;
    newChat["chatId"] = chatId;
    newChat["messages"] = QJsonArray();

    QJsonArray chats = getChats();
    chats.append(newChat);
    m_data["chats"] = chats;

    return save();
}

bool ChatDatabase::addMessage(const QString& chatId, const QString& name, const QString& text)
{
    QJsonArray chats = getChats();
    for (int i = 0; i < chats.size(); ++i) {
        QJsonObject chat = chats[i].toObject();
        if (chat.value("chatId").toString() == chatId) {
            QJsonArray messages = chat["messages"].toArray();
            QJsonObject msg;
            msg["name"] = name;
            msg["text"] = text;
            messages.append(msg);
            chat["messages"] = messages;
            chats[i] = chat;
            m_data["chats"] = chats;
            return save();
        }
    }
    return false;
}
