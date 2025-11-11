#include "macdatabase.h"

macdatabase::macdatabase(QObject *parent)
    : QObject{parent}
{}

bool macdatabase::connectDatabase(){
    db = QSqlDatabase::addDatabase("QPSQL"); // eventually they'll be a configuration menu for these values
    db.setHostName("prism.panda-mirach.ts.net");
    db.setDatabaseName("investigator");
    db.setUserName("testuser");
    db.setPassword("TheDayWeMet"); // production version will use offuscated password
    return db.open();
}

QSqlQuery macdatabase::dbquery(QString q){
    QSqlQuery query(q);
    return query;
}
