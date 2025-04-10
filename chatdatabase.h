#ifndef CHATDATABASE_H
#define CHATDATABASE_H

#pragma once

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QString>
#include <QVariantMap>

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

    bool addMessage(const QString& chatId, const QString& name, const QString& text);
    bool createChat(const QString& chatId);
    bool chatExists(const QString& chatId) const;

private:
    const QString m_filePath = "C:/Users/whoami/Desktop/Projects/inSide/DB.json"; // C:/Users/whoami/Desktop/Projects/inSide/
    QJsonObject m_data;
};

#endif // CHATDATABASE_H
