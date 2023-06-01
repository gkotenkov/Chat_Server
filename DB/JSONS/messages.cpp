//
// Created by Admin on 5/24/2023.
//

#include "messages.h"

QJsonObject DBEntity::DBMessage::toJson() const {
    QJsonObject obj;
    obj["id"] = id.toString();
    obj["date_time"] = date_time.toString();
    obj["room_id"] = room_id;
    obj["login"] = login;
    obj["parent_id"] = parent_id.isNull()?"":parent_id->getId().toString();
    obj["text"] = text;
    obj["media"] = media.isNull()?"":media;
    obj["deleted"] = deleted;
    //TODO: likes
//    obj["likes"] = likes;
    return obj;
}


void DBEntity::DBMessage::setDeleted(bool flag) {
    DBMessage::deleted = flag;
}

void DBEntity::DBMessage::setLikes(const QHash<QUuid, bool> &likes) {
    DBMessage::likes = likes;
}

void DBEntity::DBMessage::writeMessage(const QString& file_name_,const DBEntity::DBMessage& message_) {

    QFile file(file_name_);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qCritical() << "File cannot be opened" << Qt::endl;
        return;
    }
    QByteArray content = file.readAll();
    file.resize(0);  // Clear the file content

    QJsonDocument doc = QJsonDocument::fromJson(content);
    QJsonArray messagesJson;
    if (!doc.isNull() && doc.isArray()) {
        messagesJson = doc.array();
    }


    messagesJson.append(message_.toJson());

    doc.setArray(messagesJson);
    file.write(doc.toJson());
    file.close();
}

const QDateTime &DBEntity::DBMessage::getDateTime() const {
    return date_time;
}

qint32 DBEntity::DBMessage::getRoomId() const {
    return room_id;
}

const QString &DBEntity::DBMessage::getLogin() const {
    return login;
}

QString DBEntity::DBMessage::getParentId() const {
    return parent_id.isNull()?"":parent_id->getId().toString();
}

const QString &DBEntity::DBMessage::getText() const {
    return text;
}

const QString &DBEntity::DBMessage::getMedia() const {
    return media;
}

bool DBEntity::DBMessage::isDeleted() const {
    return deleted;
}

const QHash<QUuid, bool> &DBEntity::DBMessage::getLikes() const {
    return likes;
}

const QUuid &DBEntity::DBMessage::getId() const {
    return id;
}

DBEntity::DBMessage::DBMessage( qint32 room_id_, const QString &login_, const QString &text_, const QString &media_) {

    id = QUuid::createUuid();
    date_time = QDateTime::currentDateTime();
    room_id = room_id_;
    login = login_;
    text = text_;
    media = media_;
}
