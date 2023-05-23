#ifndef ENTITIES_H
#define ENTITIES_H
#include <QVector>
#include <QTime>
#include <QSet>

struct Message
{
    QString nickname;
    QString text;
    QTime   time;
    QString id;
    bool    deleted;
    //
    //    void generateId() {
    //        id = QUuid::createUuid().toString();
    //    }
};

struct client
{
    QString userName = nullptr;
    QTime lastMessageTime;
    qint32 reiting;
};

struct room
{
    QString name;
    QVector<Message> messages;
    QSet<client> clients;
    // Другие необходимые поля
};

#endif // ENTITIES_H