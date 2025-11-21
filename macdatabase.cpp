#include "macdatabase.h"

macdatabase::macdatabase(QObject *parent)
    : QObject{parent}
{}

bool macdatabase::connectDatabase(QSettings* settings, QString password){
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(settings->value("db/host").toString());
    qDebug() << "Using host " << settings->value("db/host").toString();
    db.setDatabaseName(settings->value("db/name").toString());
    qDebug() << "Using database " << settings->value("db/name").toString();
    db.setUserName(settings->value("db/username").toString());
    qDebug() << "Using username " << settings->value("db/username").toString();
    db.setPassword(password); // password is NOT stored and needs to be entered every time program starts
    return db.open();
}

QSqlQuery macdatabase::dbquery(QString q){
    QSqlQuery query(q);
    return query;
}
